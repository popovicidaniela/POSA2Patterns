#include "AcceptorEventHandler.h"

ReactorPattern::AcceptorEventHandler::AcceptorEventHandler(const INET_Addr & addr, Reactor * reactor) : acceptor_(addr), reactor_(reactor)
{
	reactor_->register_handler(this, ACCEPT_EVENT);
}

void ReactorPattern::AcceptorEventHandler::handle_event(SOCKET s, Event_Type event_type)
{
	if (event_type == ACCEPT_EVENT) {
		SOCK_Stream client_connection = SOCK_Stream();
		acceptor_.accept(client_connection);
		LogEventHandler *leh = new LogEventHandler(READ_EVENT, client_connection, reactor_);
	}
}

SOCKET ReactorPattern::AcceptorEventHandler::get_handle() const
{
	return acceptor_.get_handle();
}
