#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "stdint.h"
#include <limits>

const uint8_t SUCCESS = 0, SHUTDOWN = 1, DISCONNECT = 2,
BIND_ERROR = 3, CONNECT_ERROR = 4, SETUP_ERROR = 5,
STARTUP_ERROR = 6, ADDRESS_ERROR = 7, PARAMETER_ERROR = 8, MESSAGE_ERROR = 9;

