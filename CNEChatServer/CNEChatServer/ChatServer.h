#pragma once

#include "CLientHandler.h"

class ChatServer
{
public:

	//ChatServer();
	void Init();
	void WelcomeMessage();
	void PromtMessage();
	void GetServerSettings();

private:
	Server server; 
	CLientHandler cHandle;
	uint16_t port = 0;
	char commandChar = '~';
};

