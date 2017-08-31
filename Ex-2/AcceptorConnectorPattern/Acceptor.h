#pragma once
#include<WinSock2.h>
#include "../Reactor/Reactor.h"
#include "../Reactor/LogEventHandler.h"
#include "../Reactor/Event_Handler.h"
#include "../../Ex-1/WrapperFacade/INET_Addr.h"
using namespace ReactorPattern;
using namespace WrapperFacade;
template <class SERVICE_HANDLER, class IPC_ACCEPTOR>
class Acceptor : public Event_Handler {
public:
	Acceptor(const INET_Addr &local_addr, Reactor *r) : reactor_(r), peer_acceptor_(local_addr)
	{
		reactor_->register_handler(this, ACCEPT_EVENT);
	}
	virtual void accept()
	{
		SERVICE_HANDLER *service_handler = new SERVICE_HANDLER();
		accept_service_handler(service_handler);
		activate_service_handler(service_handler);
	}
protected:
	virtual void accept_service_handler(SERVICE_HANDLER * sh)
	{
		peer_acceptor_.accept(sh->peer());
	}
	virtual void activate_service_handler(SERVICE_HANDLER * sh)
	{
		sh->open();
	}
	virtual SOCKET get_handle() const
	{
		return peer_acceptor_.get_handle();
	}
	virtual void handle_event(SOCKET s, Event_Type et)
	{
		if (et == ACCEPT_EVENT) {
			accept();
		}
	}
private:
	IPC_ACCEPTOR peer_acceptor_;
	Reactor *reactor_;
};