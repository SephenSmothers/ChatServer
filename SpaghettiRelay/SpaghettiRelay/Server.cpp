#include "Server.h"

int Server::init(uint16_t port)
{
	sListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sListenSocket == INVALID_SOCKET)
		return SETUP_ERROR;

	sAddr.sin_family = AF_INET;
	sAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	sAddr.sin_port = htons(port);

	if (bind(sListenSocket, (SOCKADDR*)&sAddr, sizeof(sAddr)) == SOCKET_ERROR)
		return BIND_ERROR;

	if (listen(sListenSocket, 1) == SOCKET_ERROR)
		return SETUP_ERROR;

	int len = sizeof(sAddr);
	sComSocket = accept(sListenSocket, (SOCKADDR*)&sAddr, &len);

	if (sComSocket == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		if (error == WSAECONNABORTED || error == WSAECONNRESET || error == WSAESHUTDOWN)
			return SHUTDOWN;
		else
			return CONNECT_ERROR;
	}

	return SUCCESS;
}

int Server::readMessage(char* buffer, int32_t size)
{
	uint8_t msgSize = 0;

	if (tcp_recv_whole(sComSocket, (char*)&msgSize, 1) == SOCKET_ERROR)
		return DISCONNECT;

	if (msgSize > size)
		return PARAMETER_ERROR;

	int read = tcp_recv_whole(sComSocket, buffer, msgSize);

	if (read == SOCKET_ERROR)
		return DISCONNECT;
	else if (read == 0)
		return SHUTDOWN;

	return SUCCESS;
}

int Server::sendMessage(char* data, int32_t length)
{
	if (length < 0 || length > 255)
		return PARAMETER_ERROR;

	if (tcp_send_whole(sComSocket, (char*)&length, 1) == SOCKET_ERROR)
		return DISCONNECT;

	if (tcp_send_whole(sComSocket, data, length) == SOCKET_ERROR)
		return DISCONNECT;

	return SUCCESS;
}

int Server::tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length)
{
	int result;
	int bytesSent = 0;

	while (bytesSent < length)
	{
		result = send(skSocket, (const char*)data + bytesSent, length - bytesSent, 0);

		if (result <= 0)
			return result;

		bytesSent += result;
	}

	return bytesSent;
}

int Server::tcp_recv_whole(SOCKET s, char* buf, int len)
{
	int total = 0;

	do
	{
		int ret = recv(s, buf + total, len - total, 0);
		if (ret < 1)
			return ret;
		else
			total += ret;

	} while (total < len);

	return total;
}

void Server::stop()
{
	shutdown(sListenSocket, SD_BOTH);
	closesocket(sListenSocket);

	shutdown(sComSocket, SD_BOTH);
	closesocket(sComSocket);
}