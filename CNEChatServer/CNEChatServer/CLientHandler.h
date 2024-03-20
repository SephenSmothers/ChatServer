#pragma once
#include "Defines.h"

class ClientHandler
{
public:
	//CLientHandler();
	//CLientHandler(Server& _serverRef);
	void DisplayWelcomeMessage();
	void DisplayPromtMessage();
	int GetClientCap();
	void SetClientCap(int _cap);
	int ParseMessage(char* message);


private:

	int chatCapacity = 0;

};

