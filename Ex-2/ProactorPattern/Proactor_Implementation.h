#pragma once
#include<WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
class Proactor_Implementation
{
public:
	void virtual register_handle(SOCKET handle) = 0;
	void virtual handle_events(timeval *timeout = 0) = 0;
};