#include "CLientHandler.h"

//CLientHandler::CLientHandler()
//{
//	serverPtr = nullptr;
//}
//
//CLientHandler::CLientHandler(Server& _serverRef)
//{
//	serverPtr = &_serverRef;
//}

void CLientHandler::DisplayWelcomeMessage()
{
	std::cout << "Chat Server is now initalized waiting for clients to connect..." << std::endl;


}

void CLientHandler::DisplayPromtMessage()
{
	std::cout << "**********Welcome to the Chat Server!**********" << std::endl;
	std::cout << "Here you can connect with other clients and broadcast or Direct Message any other user." << std::endl;
	std::cout << "Here is some useful information to get you stared:" << std::endl;
	std::cout << "Temp Useful Info" << std::endl;




	system("PAUSE");


}

int CLientHandler::GetClientCap()
{
	return chatCapacity;
}

void CLientHandler::SetClientCap(int _cap)
{
	chatCapacity = _cap;
}
