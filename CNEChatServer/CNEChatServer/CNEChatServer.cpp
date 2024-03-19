#include <iostream>
#include <string>
#include "ChatServer.h"


int main()
{
    ChatServer chat;
    std::string serverInput = " ";

    chat.PromtMessage();
    chat.GetServerSettings();
    chat.Init();

    while (true)
    {
        std::getline(std::cin, serverInput);
        if (std::strcmp(serverInput.c_str(), "~exit") == 0)
        {
            break;
        }

    }
    return 0;
}
