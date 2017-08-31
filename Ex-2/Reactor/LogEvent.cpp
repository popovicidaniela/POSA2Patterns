#include "LogEvent.h"

ReactorPattern::LogEvent::LogEvent()
{
	logText = "";
}

ReactorPattern::LogEvent::LogEvent(char * logtext)
{
	logText = logtext;
}

char * ReactorPattern::LogEvent::getLogText()
{
	return logText;
}

ReactorPattern::LogEvent ReactorPattern::LogEvent::charsToLogEvent(char * buffer)
{
	int n = strlen(buffer);
	for (int i = 0; i < n; i++)
	{
		if (buffer[i] != '$')
		{
			char * c = appendCharToCharArray(logText, buffer[i]);
			logText = c;
		}
		else break;
	}
	return LogEvent(logText);
}

char * ReactorPattern::LogEvent::appendCharToCharArray(char * array, char a)
{
	size_t len = strlen(array);
	char* ret = new char[len + 2];
	strcpy_s(ret, len + 2, array);
	ret[len] = a;
	ret[len + 1] = '\0';
	return ret;
}
