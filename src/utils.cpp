#include "server.hpp"

void to_non_blocking(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | SOCK_NONBLOCK);
}
