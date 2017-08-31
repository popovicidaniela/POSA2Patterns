#pragma once
#include "Event_Handler.h"
#include "Reactor_Interface.h"
#include "Reactor_Implementation.h"

namespace ReactorPattern {
	class Reactor
	{
	public:
		void register_handler(Event_Handler *eh, Event_Type et);
		void remove_handler(Event_Handler *eh, Event_Type et);
		void handle_events(timeval *timeout = 0);
		static Reactor* instance();
		void setReactorInterface(Reactor_Interface* reactorInterface);
	private:
		Reactor_Interface* reactor_interface;
	};
}