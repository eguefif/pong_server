#include "server.hpp"

void to_non_blocking(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | SOCK_NONBLOCK);
}

void signal_handler(int sig)
{
	if (sig == SIGTERM || sig == SIGINT)
		running = false;
}
