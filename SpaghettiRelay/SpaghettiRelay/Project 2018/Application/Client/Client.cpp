#include "Client.h"

int Client::init(uint16_t port, char* address)
{
	cSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (cSocket == INVALID_SOCKET)
		return SETUP_ERROR;

	if (inet_addr(address) == INADDR_NONE)
		return ADDRESS_ERROR;

	cAddr.sin_family = AF_INET;
	cAddr.sin_addr.S_un.S_addr = inet_addr(address);
	cAddr.sin_port = htons(port);

	if (connect(cSocket, (SOCKADDR*)&cAddr, sizeof(cAddr)) == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if (error == WSAECONNABORTED || error == WSAECONNRESET || error == WSAESHUTDOWN)
			return SHUTDOWN;
		else
			return CONNECT_ERROR;
	}

	return SUCCESS;
}

int Client::readMessage(char* buffer, int32_t size)
{
	uint8_t msgSize = 0;

	if (tcp_recv_whole(cSocket, (char*)&msgSize, 1) == SOCKET_ERROR)
		return DISCONNECT;

	if (msgSize > size)
		return PARAMETER_ERROR;

	int read = tcp_recv_whole(cSocket, buffer, msgSize);

	if (read == SOCKET_ERROR)
		return DISCONNECT;
	else if (read == 0)
		return SHUTDOWN;

	return SUCCESS;
}

int Client::sendMessage(char* data, int32_t length)
{
	if (length < 0 || length > 255)
		return PARAMETER_ERROR;

	if (tcp_send_whole(cSocket, (char*)&length, 1) == SOCKET_ERROR)
		return DISCONNECT;

	if (tcp_send_whole(cSocket, data, length) == SOCKET_ERROR)
		return DISCONNECT;

	return SUCCESS;
}

void Client::stop()
{
	shutdown(cSocket, SD_BOTH);
	closesocket(cSocket);
}

int Client::tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length)
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

int Client::tcp_recv_whole(SOCKET s, char* buf, int len)
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
