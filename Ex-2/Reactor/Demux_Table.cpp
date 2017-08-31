#include "Demux_Table.h"
namespace ReactorPattern {
	void Demux_Table::convert_to_fd_sets(fd_set & read_fds, fd_set & write_fds, fd_set & except_fds)
	{
		TupleMap::iterator it = m_TupeTable.begin();
		for (; it != m_TupeTable.end(); ++it)
		{
			if ((it->second.event_Type & READ_EVENT) == READ_EVENT)
			{
				FD_SET(it->first, &read_fds);
			};

			if ((it->second.event_Type & WRITE_EVENT) == WRITE_EVENT)
			{
				FD_SET(it->first, &write_fds);
			};

			if ((it->second.event_Type & TIMEOUT_EVENT) == TIMEOUT_EVENT)
			{
				FD_SET(it->first, &except_fds);
			};
		}
	}
}