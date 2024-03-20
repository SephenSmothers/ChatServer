#pragma once

#include "Server.h"

class ChatServer
{
public:

	//ChatServer();
	void Init();
	void WelcomeMessage();
	void PromtMessage();
	void GetServerSettings();
	bool Run();
	void Stop();


private:

	Server server; 
	ClientHandler cHandle;
	
};

