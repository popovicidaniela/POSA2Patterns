#include "Reactor_Implementation.h"
namespace ReactorPattern {
	void Reactor_Implementation::register_handler(Event_Handler * eh, Event_Type et)
	{
		SOCKET s = eh->get_handle();
		demux_table_.AddTuple(s, Demux_Table::Tuple(eh, et));
	}

	void Reactor_Implementation::remove_handler(Event_Handler * eh, Event_Type et)
	{
		SOCKET s = eh->get_handle();
		demux_table_.RemoveTupe(s, et);
	}

	void Reactor_Implementation::handle_events(timeval *timeout)
	{
		fd_set read_fds, write_fds, except_fds;
		FD_ZERO(&read_fds);
		FD_ZERO(&write_fds);
		FD_ZERO(&except_fds);
		Demux_Table demux_table = demux_table_;
		demux_table.convert_to_fd_sets(read_fds, write_fds, except_fds);
		int maxfd = demux_table.GetMaxfd();
		int nResult = select(maxfd, &read_fds, &write_fds, &except_fds, timeout);
		if (nResult <= 0) { wprintf(L"error %ld\n", WSAGetLastError()); }
		for (SOCKET s = static_cast<unsigned int>(demux_table.GetMinfd()); s <= static_cast<int>(maxfd); ++s)
		{
			if (FD_ISSET(s, &read_fds))
			{
				Demux_Table::Tuple* pTuple = demux_table.GetTuple(s);
				if (pTuple)
				{
					if ((pTuple->event_Type & READ_EVENT) == READ_EVENT)
					{
						pTuple->event_handler->handle_event(pTuple->event_handler->get_handle(), READ_EVENT);
					}
				}
			}
			if (FD_ISSET(s, &write_fds))
			{
				Demux_Table::Tuple* pTuple = demux_table.GetTuple(s);
				if (pTuple)
				{
					if ((pTuple->event_Type & WRITE_EVENT) == WRITE_EVENT)
					{
						pTuple->event_handler->handle_event(pTuple->event_handler->get_handle(), WRITE_EVENT);
					}
				}
			}

			if (FD_ISSET(s, &except_fds))
			{
				Demux_Table::Tuple* pTuple = demux_table.GetTuple(s);
				if (pTuple)
				{
					if ((pTuple->event_Type & CLOSE_EVENT) == CLOSE_EVENT)
					{
						pTuple->event_handler->handle_event(pTuple->event_handler->get_handle(), CLOSE_EVENT);
					}
				}
			}
		}
	}
}
