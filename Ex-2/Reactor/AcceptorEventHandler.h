#pragma once
#include "Event_Handler.h"
#include "../../Ex-1/WrapperFacade/INET_Addr.h"
#include "../../Ex-1/WrapperFacade/SOCK_Stream.h"
#include "../../Ex-1/WrapperFacade/SOCK_Acceptor.h"
#include "../Reactor/AlarmEventHandler.h"
#include "../Reactor/PatientEventHandler.h"
#include "../Reactor/LogEventHandler.h"
#include "Reactor.h"
#include <iostream>
using namespace std;
using namespace WrapperFacade;
namespace ReactorPattern 
{
	class AcceptorEventHandler : public Event_Handler 
	{
	public:
		AcceptorEventHandler(const INET_Addr &addr, Reactor *reactor);
		void handle_event(SOCKET s, Event_Type event_type);
		SOCKET get_handle() const;
	private:
		SOCK_Acceptor acceptor_;
		Reactor *reactor_;
	};
}