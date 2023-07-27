#include "message.hpp"

Message::Message(std::string amessage) :
	message(amessage)
{
	if (message.size() >= COMMAND_SIZE)
	{
		command = message.substr(0, COMMAND_SIZE);
		content = message.substr(4);
	}
}

Message::Message(std::string acommand, std::string acontent) :
	command(acommand), content(acontent)
{
	message = command + content;
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

const char *Message::get_message_str()
{
	return (message.c_str());
}
size_t Message::get_size()
{
	return (message.size());
}
