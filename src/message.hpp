#pragma once
#include "def.hpp"

class Message
{
public:
	Message(std::string amessage);
	Message(std::string acommand, std::string acontent);
	std::string get_message();
	std::string get_command();
	std::string get_content();
	size_t get_size();
	const char *get_message_str();

private:
	std::string command;
	std::string content;
	std::string message;
};
