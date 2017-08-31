#pragma once
#include <iostream>
using namespace std;

namespace ReactorPattern {
	class LogEvent
	{
	public:
		LogEvent();
		LogEvent(char * logtext);
		char * getLogText();
		LogEvent charsToLogEvent(char * buffer);
	private:
		char * appendCharToCharArray(char* array, char a);
		char * logText;
	};
}