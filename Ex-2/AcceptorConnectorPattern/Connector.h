#pragma once
#include<WinSock2.h>
#include "../Reactor/Reactor.h"
#include "../../Ex-1/WrapperFacade/INET_Addr.h"
#include "../Reactor/Event_Handler.h"
#include <map>
using namespace ReactorPattern;
using namespace WrapperFacade;
enum Connection_Mode {
	SYNC,
	ASYNC
};
template <class SERVICE_HANDLER, class IPC_CONNECTOR>
class Connector : public Event_Handler {
public:
	Connector(Reactor * reactor, const INET_Addr & addr) : reactor_(reactor), addr_(addr) { }
	void connect(SERVICE_HANDLER * sh, Connection_Mode mode)
	{
		connect_service_handler(sh, mode);
	}
protected:
	virtual void connect_service_handler(SERVICE_HANDLER * sh, Connection_Mode mode)
	{
		connector_.connectt(sh->peer(), addr_);// Concrete IPC_CONNECTOR establishes connection.
		if (mode==SYNC)
		{
			activate_service_handler(sh);// Activate if we connect synchronously.
		}
		else if (mode==ASYNC)
		{
			reactor_->register_handler(this, WRITE_EVENT);// Connection did not complete immediately, so register with <reactor_>, which notifies <Connector> when the connection completes.
			connection_map_[connector_.get_handle()] = sh;// Store <SERVICE_HANDLER *> in map.
		}
	}
	int register_handler(SERVICE_HANDLER *sh, Connection_Mode mode)
	{
		return 0;
	}
	virtual void activate_service_handler(SERVICE_HANDLER *sh)
	{
		sh->open();
	}
	virtual void complete(SOCKET handle)
	{
		Connection_Map::iterator i = connection_map_.find(handle);// Find <service_handler> associated with <handle> in the map of pending connections.
		if (i == connection_map_.end()) throw /* ...some type of error... */;
		SERVICE_HANDLER *svc_handler = (*i).second;// We just want the value part of the <key,value> pair in the map
		svc_handler->set_handle(handle);// Transfer I/O handle to <service_handler>.
		reactor_->remove_handler(this, WRITE_EVENT);// Remove handle from <Reactor> and . from the pending connection map.
		connection_map_.erase(i);
		activate_service_handler(svc_handler);// Connection is complete, so activate handler.
	}
private:
	IPC_CONNECTOR connector_;
	typedef std::map<SOCKET, SERVICE_HANDLER*> Connection_Map;
	Connection_Map connection_map_; 
	const INET_Addr & addr_= INET_Addr(0, "");
	Reactor *reactor_;
	virtual void handle_event(SOCKET s, Event_Type et)
	{
		if (et == WRITE_EVENT)
		{
			complete(s);
		}
	}
	virtual SOCKET get_handle() const
	{
		return connector_.get_handle();
	}
};