#pragma once
#include "Reactor_Interface.h"
#include "Event_Handler.h"
#include "Demux_Table.h"

namespace ReactorPattern {
	class Reactor_Implementation : public Reactor_Interface
	{
	public:
		void register_handler(Event_Handler *eh, Event_Type et);
		void remove_handler(Event_Handler *eh, Event_Type et);
		void handle_events(timeval *timeout = NULL);
	private:
		Demux_Table demux_table_;
	};
}