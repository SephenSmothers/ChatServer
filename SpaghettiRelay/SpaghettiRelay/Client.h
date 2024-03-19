#pragma once
#include "../platform.h"
#include "../definitions.h"

class Client
{
	public:

	int init(uint16_t port, char* address);
	int readMessage(char* buffer, int32_t size);
	int sendMessage(char* data, int32_t length);
	int tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length);
	int tcp_recv_whole(SOCKET s, char* buf, int len);
	void stop();

private:
	SOCKET cSocket;
	sockaddr_in cAddr;
};