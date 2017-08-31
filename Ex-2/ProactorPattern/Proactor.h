#pragma once
#include "Proactor_Implementation.h"
#include "Win32_Proactor_Implementation.h"
class Proactor {
public:
	void register_handle(SOCKET handle);// Associate <handle> with the <Proactor>'s completion event queue.
	void handle_events(timeval *wait_time = 0);// Entry point into the proactive event loop. The <timeout> can bound time waiting for events.
	static Proactor *instance();// Define a singleton access point.
	void setProactorImplementation(Proactor_Implementation* proactor_impl);
	static Proactor* pointerInstance;
private:
	Proactor_Implementation *proactor_impl_;// Use the Bridge pattern to hold a pointer to the <Proactor_Implementation>.
};