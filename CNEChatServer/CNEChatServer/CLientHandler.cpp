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
//	int code = INVALID_COMMAND;

	//std::cout << "message: " << message << std::endl;
	//std::cout << "_commandChar: " << _commandChar << std::endl;
	//std::string concatenated = (std::string("getlist").insert(0,1,_commandChar));
	//std::cout << "concatenated: " << concatenated << std::endl;
	//size_t size = strlen(std::string("getlist").insert(0, 1, _commandChar).c_str());
	//std::cout << "Size: " << size << std::endl;

	if (CheckCLientCap() == false)
		return CLIENTCAP;

	if (strncmp(message, _commandChar + "help", strlen(_commandChar + "help")) == 0)
		return HELP;

	if (CheckIfRegistered(_id) == false)
		return NEW_USER;

	if (CheckIfLoggedIn(_id) == false)
		return NOT_LOGGED_IN;

	if (message[0] == _commandChar)
	{
		if (strncmp(message, std::string("register").insert(0, 1, _commandChar).c_str(), strlen(std::string("register").insert(0, 1, _commandChar).c_str())) == 0)
		{
			if (CheckIfRegistered(_id) == true)
				return OLD_USER;


			return NEW_USER;
			//code = NEW_USER;
		}
		else if (strncmp(message, std::string("login").insert(0, 1, _commandChar).c_str(), strlen(std::string("login").insert(0, 1, _commandChar).c_str())) == 0)
		{
			return LOGGED_IN;
			//code = LOGGED_IN;
		}
		else if (strncmp(message, std::string("logout").insert(0, 1, _commandChar).c_str(), strlen(std::string("logout").insert(0, 1, _commandChar).c_str())) == 0)
		{
			return LOG_OUT;
			//code = LOGGED_IN;
		}
		else if (strncmp(message, std::string("send").insert(0, 1, _commandChar).c_str(), strlen(std::string("send").insert(0, 1, _commandChar).c_str())) == 0)
		{
			return SEND_TO;
			//code = LOGGED_IN;
		}
		else if (strncmp(message, std::string("getlist").insert(0, 1, _commandChar).c_str(), strlen(std::string("getlist").insert(0, 1, _commandChar).c_str())) == 0)
		{
			return GET_LIST;
			//code = LOGGED_IN;
		}
	}

	return SEND_ALL;
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
		newUser.loggedIn = false;
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

	if (FindUser(_socketId)->loggedIn == true)
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

void ClientHandler::ParseRegisterUser(const char* message, char* username, char* password)
{

	char tempMessage[256];
	strncpy(tempMessage, message, sizeof(tempMessage));

	char* token = strtok(tempMessage, " ");

	token = strtok(NULL, " ");

	if (token != NULL)
	{
		strncpy(username, token, sizeof(username));
		username[sizeof(username) - 1] = '\0'; // Ensure null-termination
	}

	// Next token should be the password
	token = strtok(NULL, " ");

	if (token != NULL)
	{
		strncpy(password, token, sizeof(password));
		password[sizeof(password) - 1] = '\0'; // Ensure null-termination
	}
}

char* ClientHandler::GetSocketName(int _id)
{
	std::string name = "error";
	char* userName = new char();

	User* user = FindUser(_id);
	if (user != nullptr)
	{
		name = user->username;
	}



	strcpy(userName, name.c_str());
	return userName;
}

bool ClientHandler::CheckCLientCap()
{
	bool atCap = false;

	if (userTable.bucket_count() < CLIENTCAP)
	{
		atCap = true;
	}

	return atCap;
}
