#include "ChatServer.h"

//ChatServer::ChatServer()
//{
//    cHandle;
//}

void ChatServer::Init()
{
	int errorCode = server.init(port);

	switch (errorCode)
	{

	case SUCCESS:

		WelcomeMessage();

		return;

		break;
	case SETUP_ERROR:

		break;
	case BIND_ERROR:

		break;
	case CONNECT_ERROR:

		break;
	case SHUTDOWN:

		break;
	default:

		server.stop();
		break;
	}
}

void ChatServer::WelcomeMessage()
{
   char test[100] = "Hello did you get this?";
   int num = server.sendMessage(test, sizeof(test));


    //int result = 0;
    //// The host and service we want to resolve
    //const char* host = "www.example.com";
    //const char* service = "http";

    //// Variables for getaddrinfo
    //struct addrinfo* resultAddr = NULL;
    //struct addrinfo hints;

    //ZeroMemory(&hints, sizeof(hints));
    //hints.ai_family = AF_INET;  // Allow IPv4 or IPv6
    //hints.ai_socktype = SOCK_STREAM;  // TCP socket
    //hints.ai_protocol = IPPROTO_TCP;
    //hints.ai_flags = AI_PASSIVE;

    //// Resolve the host name and service
    //result = getaddrinfo(NULL, NULL, &hints, &resultAddr);
    //if (result != 0) {
    //    std::cerr << "getaddrinfo failed with error: " << result << std::endl;
    //    WSACleanup();
    //}

    //// Print the IPv4 address
    //if (resultAddr != NULL) {
    //    struct sockaddr_in* ipv4 = (struct sockaddr_in*)resultAddr->ai_addr;
    //    char ipString[INET_ADDRSTRLEN];
    //    inet_ntop(AF_INET, &(ipv4->sin_addr), ipString, INET_ADDRSTRLEN);
    //    std::cout << "IPv4 Address: " << ipString << std::endl;
    //}

    //freeaddrinfo(resultAddr);
}

void ChatServer::PromtMessage()
{
	cHandle.DisplayPromtMessage();

   
}

void ChatServer::GetServerSettings()
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
    cHandle.SetClientCap(chatCapacity);
    std::cin.ignore();
    if (std::cin.fail()) {
        std::cin.clear();
        cHandle.SetClientCap(10);
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
