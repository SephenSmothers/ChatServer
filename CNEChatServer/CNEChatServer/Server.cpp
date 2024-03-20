#include "Server.h"


Server::Server()
{
	timeOut.tv_sec = 5;
	FD_ZERO(&masterSet);
	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&exceptSet);
}

int Server::init(/*uint16_t port*/)
{
	WSADATA wsadata;
	if (WSAStartup(WINSOCK_VERSION, &wsadata))
		return STARTUP_ERROR;

	sListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sListenSocket == INVALID_SOCKET)
		return SETUP_ERROR;

	sAddr.sin_family = AF_INET;
	sAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	sAddr.sin_port = htons(port);

	if (bind(sListenSocket, (SOCKADDR*)&sAddr, sizeof(sAddr)) == SOCKET_ERROR)
		return BIND_ERROR;

	FD_SET(sListenSocket, &masterSet);

	char hostName[256];
	//	int len = 0;
	int num = gethostname(hostName, sizeof(hostName));
	std::cout << "Host Name: " << hostName << std::endl;
	std::cout << "Server is now listening for clients to connect... " << std::endl;

	if (listen(sListenSocket, 1) == SOCKET_ERROR)
		return SETUP_ERROR;

	//int len = sizeof(sAddr);
	//sComSocket = accept(sListenSocket, (SOCKADDR*)&sAddr, &len);

	//if (sComSocket == INVALID_SOCKET)
	//{
	//	int error = WSAGetLastError();
	//	if (error == WSAECONNABORTED || error == WSAECONNRESET || error == WSAESHUTDOWN)
	//		return SHUTDOWN;
	//	else
	//		return CONNECT_ERROR;
	//}

	return SUCCESS;
}

int Server::Run(ClientHandler _handel)
{
	//different promts
	char loginPrompt[] = "Hello please login using the \n *command char*login username password \n (Note: default command char is ~)";
	char helpPrompt[] = "[SERVER] Hello please login using the \n *command char*login username password \n (Note: default command char is ~)";
	char invalidPrompt[] = "[SERVER] INVALID COMMAND";
	char loginErrorPrompt[] = "[SERVER] Please login to send messages to other users.";
	char defaultPrompt[] = "[SERVER] There was an error with your maessage, please try again.";
	int errorCode = SUCCESS;

	readSet = masterSet;
	writeSet = masterSet;
	exceptSet = masterSet;

	select(0, &readSet, &writeSet, &exceptSet, NULL);

	if (FD_ISSET(sListenSocket, &readSet))
	{
		int len = sizeof(sAddr);
		sComSocket = accept(sListenSocket, (SOCKADDR*)&sAddr, &len);
		FD_SET(sComSocket, &masterSet);

		if (sComSocket == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			if (error == WSAECONNABORTED || error == WSAECONNRESET || error == WSAESHUTDOWN)
				return SHUTDOWN;
			else {
			shutdown(sComSocket, SD_BOTH);
			closesocket(sComSocket);
			}
		}
		else
		{
			std::cout << "New Client Has Joined The Chat" << std::endl;
			
			int promtError = sendMessage(loginPrompt, std::strlen(loginPrompt), sComSocket);
		}
	}

	for (int i = 0; i < readSet.fd_count; i++)
	{
		int readError = 0;
		int sendError = 0;

		if (readSet.fd_array[i] != sListenSocket)
		{
			int readError = readMessage(readBuffer, 256, readSet.fd_array[i]);

			if (readError == SUCCESS)
			{
				int result = _handel.ParseMessage(readBuffer);


				switch (result)
				{
				case SEND_ALL:

					for (int j = 0; j < writeSet.fd_count; j++)
					{
						if (writeSet.fd_array[j] != sListenSocket && writeSet.fd_array[j] != readSet.fd_array[i])
						{
							sendMessage(readBuffer, std::strlen(readBuffer), writeSet.fd_array[j]);
						}
					}

					break;
				case SEND_TO:
					//blank for now
					break;
				case HELP:

					sendError = sendMessage(helpPrompt, std::strlen(helpPrompt), readSet.fd_array[i]);
					//memset(readBuffer, 0, sizeof(readBuffer));

					break;
				case INVALID_COMMAND:
					
					sendError = sendMessage(invalidPrompt, std::strlen(invalidPrompt), readSet.fd_array[i]);
					//memset(readBuffer, 0, sizeof(readBuffer));

					break;
				case NOT_LOGGED_IN:
					
					sendError = sendMessage(loginErrorPrompt, std::strlen(loginErrorPrompt), readSet.fd_array[i]);
					//memset(readBuffer, 0, sizeof(readBuffer));

					break;
				default:
				
					sendError = sendMessage(defaultPrompt, std::strlen(defaultPrompt), readSet.fd_array[i]);
					//memset(readBuffer, 0, sizeof(readBuffer));

					break;
				}

				//std::cout << readBuffer << std::endl;

			}
		}
	}

	//ClearMasterSetBuffer();
	memset(readBuffer, '\0', sizeof(readBuffer));

	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&exceptSet);

	//delete users from master set if they dissconnect
	//for (int i = 0; i < length; i++)
	//{

	//}

	return errorCode;
}

void Server::ClearMasterSetBuffer()
{
	for (int i = 0; i < masterSet.fd_count; i++)
	{
		ClearSocketDataHelper(masterSet.fd_array[i]);
	}
}

void Server::ClearSocketDataHelper(SOCKET socket) {
	constexpr int bufferSize = 256;
	char buffer[bufferSize];

	// Keep reading until there's no more data
	int bytesRead;
	do {
		bytesRead = recv(socket, buffer, bufferSize, 0);
		if (bytesRead < 0) {
			break;
		}
	} while (bytesRead > 0);
}


int Server::readMessage(char* buffer, int32_t size, SOCKET& socket)
{
	uint8_t msgSize = 0;

	if (tcp_recv_whole(socket, (char*)&msgSize, 1) == SOCKET_ERROR)
		return DISCONNECT;

	if (msgSize > size)
		return PARAMETER_ERROR;

	int read = tcp_recv_whole(socket, buffer, msgSize);

	if (read == SOCKET_ERROR)
		return DISCONNECT;
	else if (read == 0)
		return SHUTDOWN;

	return SUCCESS;
}

int Server::sendMessage(char* data, int32_t length, SOCKET& socket)
{
	if (length < 0 || length > 255)
		return PARAMETER_ERROR;

	if (tcp_send_whole(socket, (char*)&length, 1) == SOCKET_ERROR)
		return DISCONNECT;

	if (tcp_send_whole(socket, data, length) == SOCKET_ERROR)
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

void Server::SetServerSettings(ClientHandler& _handle)
{
	int chatCapacity;

	// Prompt for TCP Port number
	std::cout << "Enter TCP Port number (default is 31337): ";
	std::cin >> port;
	std::cin.ignore();
	if (std::cin.fail()) {
		std::cin.clear();
		port = 31337;
	}

	// Prompt for chat capacity
	std::cout << "Enter chat capacity: ";
	std::cin >> chatCapacity;
	_handle.SetClientCap(chatCapacity);
	std::cin.ignore();
	if (std::cin.fail()) {
		std::cin.clear();
		_handle.SetClientCap(10);
	}

	// Prompt for command character
	std::cout << "Enter command character (default is '~'): ";
	std::cin >> commandChar;
	std::cin.ignore();
	if (std::cin.fail()) {
		std::cin.clear();
		commandChar = '~';
	}

}

void Server::stop()
{
	shutdown(sListenSocket, SD_BOTH);
	closesocket(sListenSocket);

	shutdown(sComSocket, SD_BOTH);
	closesocket(sComSocket);
}