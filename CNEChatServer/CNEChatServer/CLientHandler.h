#pragma once
#include "Defines.h"


struct User
{
	//int socket_id;
	std::string username;
	std::string password;
	bool loggedIn;
};

class ClientHandler
{
public:

	ClientHandler();
	//void DisplayWelcomeMessage();
	//void DisplayPromtMessage();
	int GetClientCap();
	void SetClientCap(int _cap);
	int ParseMessage(char* message, int _id, char _commandChar);
	bool CheckIfRegistered(int _id);
	bool CheckIfLoggedIn(int _id);
	User* FindUser(int _id);
	void RegisterUser(int _socketId, const char* _username, const char* _password);
	int LoginUser(int _socketId, const char* _username, const char* _password);
	void ParseRegisterUser(const char* message, char* username, char* password);
	char* GetSocketName(int _id);
	bool CheckCLientCap();
	int GetClientToSend(std::string _name);
	bool LogOutUser(int _id);


private:
	int chatCapacity = 0;
	std::unordered_map<int, User> userTable;
	//Dictionary<int, User>* userTable = nullptr;
};

