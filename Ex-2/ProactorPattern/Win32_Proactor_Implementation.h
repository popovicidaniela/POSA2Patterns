#pragma once
#include "Proactor_Implementation.h"
#include "Async_Result.h"
class Win32_Proactor_Implementation : public Proactor_Implementation
{
public:
	Win32_Proactor_Implementation();
	void register_handle(SOCKET h);
	void handle_events(timeval *wait_time = 0);
private:
	HANDLE completion_port_;// Store a HANDLE to a Windows NT completion port.
};