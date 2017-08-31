#include "AlarmEventHandler.h"
namespace ReactorPattern {
	AlarmEventHandler::AlarmEventHandler(Event_Type et, const WrapperFacade::SOCK_Stream &stream, Reactor *reactor) : peer_stream_(stream)
	{
		reactor->register_handler(this, et);
	}
	void AlarmEventHandler::handle_event(SOCKET s, Event_Type et)
	{
		if (et == READ_EVENT) {
			char buffer[80];
			peer_stream_.recv(buffer, sizeof(buffer) - 1, 0);
			AlarmEvent ae = AlarmEvent();
			AlarmEvent aLe = ae.charsToAlarmEvent(buffer);
			cout <<"Priority: "<< aLe.getPriority() << "\t" <<"Alarm text: " << aLe.getAlarmText() << endl;
		}
		if (et == WRITE_EVENT) {
			char buffer[80];
			cout << "Write an ALARM event in this format priority;alarm text\t";
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

	SOCKET AlarmEventHandler::get_handle() const
	{
		return peer_stream_.get_handle();
	}
}