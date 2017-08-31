#include "PatientEvent.h"

ReactorPattern::PatienEvent::PatienEvent()
{
	Type = "";
	Value = "";
}

ReactorPattern::PatienEvent::PatienEvent(char * type, char * value)
{
	Type = type;
	Value = value;
}

char * ReactorPattern::PatienEvent::getType()
{
	return Type;
}

char * ReactorPattern::PatienEvent::getValue()
{
	return Value;
}

ReactorPattern::PatienEvent ReactorPattern::PatienEvent::charsToAlarmEvent(char * buffer)
{
	int i = 0;
	int n = strlen(buffer);
	for (i; i < n; i++)
	{
		if (buffer[i] != ';')
		{
			char * c = appendCharToCharArray(Type, buffer[i]);
			Type = c;
		}
		else break;
	}
	for (i = i + 1; i < n; i++)
	{
		if (buffer[i] != '$')
		{
			char * c = appendCharToCharArray(Value, buffer[i]);
			Value = c;
		}
		else break;
	}
	return PatienEvent(Type, Value);
}

char * ReactorPattern::PatienEvent::appendCharToCharArray(char * array, char a)
{
	size_t len = strlen(array);
	char* ret = new char[len + 2];
	strcpy_s(ret, len + 2, array);
	ret[len] = a;
	ret[len + 1] = '\0';
	return ret;
}
