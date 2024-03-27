#pragma once
#include "ClientHandler.h"

class Server
{
public:
	Server();
	int init(/*uint16_t port*/);
	int Run(ClientHandler& _handel);
	int readMessage(char* buffer, int32_t size, SOCKET& socket);
	int sendMessage(char* data, int32_t length, SOCKET& socket);
	int tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length);
	int tcp_recv_whole(SOCKET s, char* buf, int len);
	void SetServerSettings(ClientHandler& _handle);
	void ClearMasterSetBuffer();
	void ClearSocketDataHelper(SOCKET socket);
	void SendList(SOCKET& socket, fd_set& _masterSet, ClientHandler& _handle);
	void stop();


private:
	SOCKET sListenSocket;
	//std::vector<SOCKET> sComSocket;
	SOCKET sComSocket;
	sockaddr_in sAddr;
	fd_set masterSet, readSet, writeSet, exceptSet;
	timeval timeOut;
	char readBuffer[256];
	uint16_t port = 0;
	char commandChar = '~';
};

