#pragma once
#include <time.h>
#include <iostream>
using namespace std;

namespace ReactorPattern {
	class AlarmEvent
	{
	public:
		AlarmEvent();
		AlarmEvent(char * alarmtext, char * prioritytext);
		static char * timeStamp();
		char * getAlarmText();
		char * getPriority();
		AlarmEvent charsToAlarmEvent(char * buffer);
	private:
		char* appendCharToCharArray(char* array, char a);
		char * alarmText;
		char * priority;
	};
}