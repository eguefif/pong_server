#include "tcpstream.hpp"

TCP_Stream::TCP_Stream(int asock, struct sockaddr_in *info) :
	sock(asock) 
{
	char temp_address[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, (struct sockaddr *) info, temp_address, INET_ADDRSTRLEN);
	peer_port = ntohs(info->sin_port);
	peer_add = temp_address;
	std::cout << "New client sock " << sock << " (" \
		<< peer_add << ":" << peer_port << ")" << std::endl;
}

int TCP_Stream::get_sock()
{
	return (sock);
}

size_t TCP_Stream::sendto(char *buffer, size_t len)
{
	size_t retval;
	retval = send(sock, buffer, len, 0);
	return (retval);
}

size_t TCP_Stream::receive(char *buffer, size_t len)
{
	size_t retval;
	retval = read(sock, buffer, len);
	return (retval);
}

void TCP_Stream::cleanup()
{
	close(sock);
}

std::string TCP_Stream::get_addr()
{
	return (peer_add);
}

int TCP_Stream::get_port()
{
	return (peer_port);
}
