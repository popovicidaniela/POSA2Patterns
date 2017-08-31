#pragma once
#include<WinSock2.h>
namespace ReactorPattern {
	typedef unsigned int Event_Type;
	enum {
		READ_EVENT = 01,
		ACCEPT_EVENT = 01,
		WRITE_EVENT = 02,
		TIMEOUT_EVENT = 04,
		SIGNAL_EVENT = 010,
		CLOSE_EVENT = 020
	};
	class Event_Handler
	{
	public:
		virtual void handle_event(SOCKET s, Event_Type et) = 0;
		virtual SOCKET get_handle() const = 0;
		virtual ~Event_Handler();
	};
}