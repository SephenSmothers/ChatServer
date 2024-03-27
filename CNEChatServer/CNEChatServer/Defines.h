#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "stdint.h"
#include <string>
#include <limits>
#include <unordered_map>

#define MAX_USERNAME_LEN 32
#define MAX_PASSWORD_LEN 32

const uint8_t SUCCESS = 0, SHUTDOWN = 1, DISCONNECT = 2,
BIND_ERROR = 3, CONNECT_ERROR = 4, SETUP_ERROR = 5,
STARTUP_ERROR = 6, ADDRESS_ERROR = 7, PARAMETER_ERROR = 8, MESSAGE_ERROR = 9,
INVALID_COMMAND = 10, NOT_LOGGED_IN = 11, SEND_ALL = 12, SEND_TO = 13, HELP = 14,
NEW_USER = 15, LOGGED_IN = 16, OLD_USER = 17, LOG_OUT = 18, GET_LIST = 20,
CLIENTCAP = 21;

