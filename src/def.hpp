#pragma once
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <vector>
#include <errno.h>
#include <queue>
#include <string.h>
#include <fcntl.h>
#include <ctime>
#include <signal.h>

const int MAX_CONNEXION = 100;
const int MAX_SIZE = 50;
const int PROTOHEADER_SIZE = 2;

extern bool running;

void to_non_blocking(int fd);
void signal_handler(int sig);
