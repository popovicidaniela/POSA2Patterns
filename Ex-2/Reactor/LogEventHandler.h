#pragma once
#include "Event_Handler.h"
#include "../../Ex-1/WrapperFacade/SOCK_Stream.h"
#include "Reactor.h"
#include "LogEvent.h"
#include <iostream>
using namespace std;
namespace ReactorPattern {
	class LogEventHandler : public Event_Handler
	{
	public:
		LogEventHandler(Event_Type et, const WrapperFacade::SOCK_Stream &stream, Reactor *reactor);
		void handle_event(SOCKET s, Event_Type et);
		SOCKET get_handle() const;
	private:
		WrapperFacade::SOCK_Stream peer_stream_;
	};
}