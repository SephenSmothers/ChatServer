#include "ClientHandler.h"

ClientHandler::ClientHandler()
{

}


//void ClientHandler::DisplayWelcomeMessage()
//{
//	std::cout << "Chat Server is now initalized waiting for clients to connect..." << std::endl;
//}
//
//void ClientHandler::DisplayPromtMessage()
//{
//	
//}

int ClientHandler::GetClientCap()
{
	return chatCapacity;
}

void ClientHandler::SetClientCap(int _cap)
{
	chatCapacity = _cap;
}

int ClientHandler::ParseMessage(char* message, int _id, char _commandChar)
{
	int code = INVALID_COMMAND;

	if (CheckIfRegistered(_id) == false)
		return NEW_USER;
	//else
	//	return OLD_USER;

	if (CheckIfLoggedIn(_id) == false)
		return NOT_LOGGED_IN;
	//else
	//	return LOGGED_IN;

	if (message[0] == _commandChar)
	{
		if (strcmp(message, _commandChar + "register") == 0)
		{
			if (CheckIfRegistered(_id) == true)
				return OLD_USER;

			code = NEW_USER;
		}
		else if (strcmp(message, _commandChar + "help") == 0)
		{
			code = HELP;
		}
		else if (strcmp(message, _commandChar + "login") == 0)
		{

			code = LOGGED_IN;
		}
	}
	else
	{
		code == SEND_ALL;
	}

	return code;
}

bool ClientHandler::CheckIfRegistered(int _id)
{
	if (FindUser(_id) == nullptr)
		return false;
	else
		return true;
}

bool ClientHandler::CheckIfLoggedIn(int _id)
{
	if (FindUser(_id)->loggedIn == false)
		return false;
	else
		return true;
}

User* ClientHandler::FindUser(int _id)
{
	auto foundUser = userTable.find(_id);

	if (foundUser == userTable.end())
		return nullptr;

	return &foundUser->second;
}

void ClientHandler::RegisterUser(int _socketId, const char* _username, const char* _password)
{
	if (FindUser(_socketId) == nullptr)
	{
		User newUser;
		newUser.username = _username;
		newUser.password = _password;
		userTable[_socketId] = newUser;
	}
	else
	{
		return;
	}
}

int ClientHandler::LoginUser(int _socketId, const char* _username, const char* _password)
{
	int code = NOT_LOGGED_IN;

	if (FindUser(_socketId) != nullptr)
	{
		code = LOGGED_IN;
	}
	else
	{
		User* user = FindUser(_socketId);
		if (user->username == userTable[_socketId].username && user->password == userTable[_socketId].password)
		{
			userTable[_socketId].loggedIn = true;
		}
		else
		{
			code = NOT_LOGGED_IN;
		}
	}

	return code;
}
