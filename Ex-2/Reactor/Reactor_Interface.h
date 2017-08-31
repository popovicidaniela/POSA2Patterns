#pragma once
#include "Event_Handler.h"

namespace ReactorPattern {
	class Reactor_Interface
	{
	public:
		void virtual register_handler(Event_Handler *eh, Event_Type et) = 0;
		void virtual remove_handler(Event_Handler *eh, Event_Type et) = 0;
		void virtual handle_events(timeval *timeout = NULL) = 0;
	};
}