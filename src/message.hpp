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
	void update_sent(size_t size);
	const char *get_message_tosend();
	bool is_message_sent();

private:
	std::string command;
	std::string content;
	std::string message;
	size_t sent = 0;

	std::string trim(std::string str);
};
