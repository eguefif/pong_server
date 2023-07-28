#include "client.hpp"

Client::Client(int fd, struct sockaddr_in *info) :
	stream(fd, info)
{}

int Client::get_sock()
{
	return (stream.get_sock());
}

void Client::read_all()
{
	read_protoheader();
}

void Client::read_protoheader()
{
	char temp[MAX_SIZE];

	memset(temp, 0, MAX_SIZE);
	if (protoheader_read_size < PROTOHEADER_SIZE)
	{
		protoheader_read_size += stream.receive(temp, 2);
		protoheader += temp;
		if (protoheader_read_size == 2)
		{
			size = atoi(protoheader.c_str());
		}
	}
	else
	{
		if (message_read_size < size)
		{
			message_read_size += stream.receive(temp, size);
			message += temp;
			if (message_read_size == size)
			{
				protoheader_read_size = 0;
				message_read_size = 0;
				Message new_message(message);
				inbound_messages.push_back(new_message);
				message = "";
				protoheader = "";
			}
		}
	}
}

void Client::send_all()
{
	int retval;

	if (outbound_messages.empty())
		return;
	while (!outbound_messages.empty())
	{
		char temp[MAX_SIZE];

		memset(temp, 0, sizeof(temp));
		Message message = outbound_messages.front();
		sprintf(temp, "%02d%s", (int) message.get_size(), message.get_message_tosend());
		retval = stream.sendto(temp, strlen(temp));
		outbound_messages.pop();
	}
}

void Client::cleanup()
{
	close(get_sock());
	inbound_messages.clear();
}

std::string Client::get_name()
{
	return (name);
}

bool Client::check_and_set_name()
{
	for (auto message = inbound_messages.begin();
			message != inbound_messages.end();
			++message)
	{
		if (message->get_command() == "name")
		{
			name = message->get_content();
			inbound_messages.erase(message);
			return (true);
		}
	}
	return (false);
}

bool Client::is_ready()
{
	for (auto message = inbound_messages.begin();
			message != inbound_messages.end();
			++message)
	{
		if (message->get_command() == "ready")
		{
			inbound_messages.erase(message);
			return (true);
		}
	}
	return (false);
}
