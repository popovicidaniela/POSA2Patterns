#include "Reactor.h"

namespace ReactorPattern {
	void Reactor::register_handler(Event_Handler * eh, Event_Type et)
	{
		reactor_interface->register_handler(eh, et);
	}
	void Reactor::remove_handler(Event_Handler * eh, Event_Type et)
	{
		reactor_interface->remove_handler(eh, et);
	}
	void Reactor::handle_events(timeval * timeout)
	{
		reactor_interface->handle_events(timeout);
	}
	static Reactor* pointerInstance;
	Reactor* Reactor::instance()
	{
		if (!pointerInstance)
		{
			pointerInstance = new Reactor;
			pointerInstance->setReactorInterface(new Reactor_Implementation);
		}
		return pointerInstance;
	}
	void Reactor::setReactorInterface(Reactor_Interface * reactorInterface)
	{
		reactor_interface = reactorInterface;
	}
}