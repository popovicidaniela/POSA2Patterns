#include "PatientEventHandler.h"

ReactorPattern::PatientEventHandler::PatientEventHandler(Event_Type et, const WrapperFacade::SOCK_Stream & stream, Reactor * reactor) : peer_stream_(stream)
{
	reactor->register_handler(this, et);
}

void ReactorPattern::PatientEventHandler::handle_event(SOCKET s, Event_Type et)
{
	if (et == READ_EVENT) {
		char buffer[80];
		peer_stream_.recv(buffer, sizeof(buffer) - 1, 0);
		PatienEvent ae = PatienEvent();
		PatienEvent aLe = ae.charsToAlarmEvent(buffer);
		cout << aLe.getType() << "\t" << aLe.getValue() << endl;
	}
	if (et == WRITE_EVENT) {
		char buffer[80];
		cout << "Send Patient event in this format patient type;patient value\t";
		cin >> buffer;
		char c = '$';
		strncat_s(buffer, &c, 1);
		peer_stream_.send(buffer, sizeof(buffer) - 1, 0);
	}
	else if (et == CLOSE_EVENT) {
		peer_stream_.~SOCK_Stream();
		delete this;
	}
}

SOCKET ReactorPattern::PatientEventHandler::get_handle() const
{
	return peer_stream_.get_handle();
}
