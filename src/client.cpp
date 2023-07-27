#include "client.hpp"

Client::Client(int fd, struct sockaddr_in *info):
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
			size = atoi(protoheader.c_str());
	}
	else
	{
		if (message_read_size < size)
		{
			message_read_size += stream.receive(temp, size);
			message += temp;
			std::cout << "Size read " << message << std::endl;
			if (message_read_size == size)
			{
				protoheader_read_size = 0;
				message_read_size = 0;
				inbound_messages.push(message);
				message = "";
			}
		}
	}
}

void Client::send_all()
{
}

void Client::cleanup()
{
	std::cout << "Removing client (" << stream.get_addr() << " : " << stream.get_port() << ")" << std::endl;
	close(get_sock());
	while (!inbound_messages.empty())
		inbound_messages.pop();
}
