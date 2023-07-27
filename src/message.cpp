#include "message.hpp"

Message::Message(std::string amessage) :
	message(amessage)
{
	size_t pos;

	pos = message.find(":");
	if (pos != std::string::npos)
	{
		command = message.substr(0, pos);
		content = message.substr(pos + 1);
	}
	else
		command = message;
}

Message::Message(std::string acommand, std::string acontent) :
	command(acommand), content(acontent)
{
	message = command + ":" + content;
}

std::string Message::get_message()
{
	return (message);
}

std::string Message::get_content()
{
	return (content);
}

std::string Message::get_command()
{
	return (command);
}

const char *Message::get_message_tosend()
{
	std::string retval;

	retval = message.substr(sent);
	return (retval.c_str());
}

size_t Message::get_size()
{
	return (message.size());
}

bool Message::is_message_sent()
{
	if (message.size() == sent)
		return (true);
	return (false);
}

void Message::update_sent(size_t size)
{
	sent += size;
}

std::string Message::trim(std::string str)
{
	size_t end;

	end = str.find_last_not_of("\n\t\r ");
	return str.substr(0, end);
}

void Message::set_command(std::string acommand)
{
	command = acommand;
}

void Message::set_content(std::string acontent)
{
	content = acontent;
}
