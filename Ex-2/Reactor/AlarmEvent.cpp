#include "AlarmEvent.h"

ReactorPattern::AlarmEvent::AlarmEvent()
{
	alarmText = "";
	priority = "";
}

ReactorPattern::AlarmEvent::AlarmEvent(char * alarmtext, char * prioritytext)
{
	alarmText = alarmtext;
	priority = prioritytext;
}

char * ReactorPattern::AlarmEvent::timeStamp()
{
	return nullptr;
}

char * ReactorPattern::AlarmEvent::getAlarmText()
{
	return alarmText;
}

char * ReactorPattern::AlarmEvent::getPriority()
{
	return priority;
}

char* ReactorPattern::AlarmEvent::appendCharToCharArray(char* array, char a)
{
	size_t len = strlen(array);
	char* ret = new char[len + 2];
	strcpy_s(ret, len + 2, array);
	ret[len] = a;
	ret[len + 1] = '\0';
	return ret;
}

ReactorPattern::AlarmEvent ReactorPattern::AlarmEvent::charsToAlarmEvent(char * buffer)
{
	int i = 0;
	int n = strlen(buffer);
	for (i ; i < n; i++)
	{
		if (buffer[i] != ';') 
		{
			char * c = appendCharToCharArray(priority, buffer[i]);
			priority = c;
		}
		else break;
	}
	for (i=i+1; i < n; i++)
	{
		if (buffer[i] != '$')
		{
			char * c = appendCharToCharArray(alarmText, buffer[i]);
			alarmText = c;
		}
		else break;
	}
	return AlarmEvent(alarmText, priority);
}
