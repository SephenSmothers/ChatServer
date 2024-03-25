#include "ChatServer.h"

void ChatServer::Init()
{
	int errorCode = server.init();

	switch (errorCode)
	{

	case SUCCESS:

		//WelcomeMessage();

		return;

		break;
	case SETUP_ERROR:

        server.stop();

		break;
	case BIND_ERROR:

        server.stop();

		break;
	case CONNECT_ERROR:

        server.stop();

		break;
	case SHUTDOWN:

        server.stop();

		break;
	default:

		server.stop();

		break;
	}
}

bool ChatServer::Run()
{
    if (server.Run(cHandle) != SUCCESS)
        return false;
    
    return true; 
}

void ChatServer::Stop()
{
    server.stop();
}

void ChatServer::WelcomeMessage()
{
    std::cout << "**********Welcome to the Chat Server!**********" << std::endl;
    std::cout << "Here you can connect with other clients and broadcast or Direct Message any other user." << std::endl;
    std::cout << "Here is some useful information to get you stared:" << std::endl;
    std::cout << "Temp Useful Info" << std::endl;
    system("PAUSE");

/*
   char test[100] = "Hello did you get this?";
   int num = server.sendMessage(test, std::strlen(test));
    int result = 0;
     The host and service we want to resolve
    const char* host = "www.example.com";
    const char* service = "http";
     Variables for getaddrinfo
    struct addrinfo* resultAddr = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;  // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;  // TCP socket
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
     Resolve the host name and service
    result = getaddrinfo(NULL, NULL, &hints, &resultAddr);
    if (result != 0) {
        std::cerr << "getaddrinfo failed with error: " << result << std::endl;
        WSACleanup();
    }
     Print the IPv4 address
    if (resultAddr != NULL) {
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)resultAddr->ai_addr;
        char ipString[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ipv4->sin_addr), ipString, INET_ADDRSTRLEN);
        std::cout << "IPv4 Address: " << ipString << std::endl;
    }
    freeaddrinfo(resultAddr);
    */
}

void ChatServer::PromtMessage()
{
   
}

void ChatServer::GetServerSettings()
{
    server.SetServerSettings(cHandle);
}
