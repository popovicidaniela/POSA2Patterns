#include "LogEventHandler.h"

ReactorPattern::LogEventHandler::LogEventHandler(Event_Type et, const WrapperFacade::SOCK_Stream & stream, Reactor * reactor) : peer_stream_(stream)
{
	reactor->register_handler(this, et);
}

void ReactorPattern::LogEventHandler::handle_event(SOCKET s, Event_Type et)
{
	if (et == READ_EVENT) {
		char buffer[80];
		peer_stream_.recv(buffer, sizeof(buffer) - 1, 0);
		LogEvent ae = LogEvent();
		LogEvent aLe = ae.charsToLogEvent(buffer);
		cout << "Log text: " << aLe.getLogText() << endl;
	}
	if (et == WRITE_EVENT) {
		char buffer[80];
		cout << "Write a Log event text \t";
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

SOCKET ReactorPattern::LogEventHandler::get_handle() const
{
	return peer_stream_.get_handle();
}
