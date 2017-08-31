#pragma once
#include <iostream>
using namespace std;

namespace ReactorPattern {
	class PatienEvent
	{
	public:
		PatienEvent();
		PatienEvent(char * type, char * value);
		char * getType();
		char * getValue();
		PatienEvent charsToAlarmEvent(char * buffer);
	private:
		char* appendCharToCharArray(char* array, char a);
		char * Type;
		char * Value;
	};
}