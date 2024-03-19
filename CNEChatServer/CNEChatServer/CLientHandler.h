#pragma once
#include "MessageHandler.h"

class CLientHandler
{
public:
	//CLientHandler();
	//CLientHandler(Server& _serverRef);
	void DisplayWelcomeMessage();
	void DisplayPromtMessage();
	int GetClientCap();
	void SetClientCap(int _cap);

private:
	MessageHandler mHandle;
//	Server* serverPtr;
	int chatCapacity = 0;

};

