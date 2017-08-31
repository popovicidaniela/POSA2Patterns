// ServerApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <fstream>
#include <string>
#include "../AcceptorConnectorPattern/Acceptor.h"
#include "../AcceptorConnectorPattern/Service_Handler.h"
#include "../Reactor/Reactor.h"
#include "../Reactor/AlarmEventHandler.h"
#include "../Reactor/AcceptorEventHandler.h"
#include "../Reactor/PatientEventHandler.h"
#include "../Reactor/LogEventHandler.h"
#include "../ProactorPattern/Proactor.h"
#include "../ProactorPattern/Concrete_Completion_Handler.h"
#include "../../Ex-1/WrapperFacade/INET_Addr.h"
#include "../../Ex-1/WrapperFacade/SOCK_Stream.h"
#include "../../Ex-1/WrapperFacade/SOCK_Acceptor.h"
#include <iostream>

using namespace WrapperFacade;
using namespace ReactorPattern;
using namespace std;
typedef Service_Handler<SOCK_Stream> Peer_Handler;
class Patient_System : public Peer_Handler
{
public:
	char * appendCharToCharArray(char * array, char a)
	{
		size_t len = strlen(array);
		char* ret = new char[len + 2];
		strcpy_s(ret, len + 2, array);
		ret[len] = a;
		ret[len + 1] = '\0';
		return ret;
	}
	virtual void open()
	{
		for (;;)
		{
			char buffer[80];
			char * cprNumber = "";
			peer().recv(buffer, sizeof(buffer) - 1, 0);
			int i = 0;
			cout << "CPR received from client:" << "\t";
			while (buffer[i] != '$')
			{
				cprNumber = appendCharToCharArray(cprNumber, buffer[i]);
				i++;
			}
			cout << cprNumber << endl;
			string patient = GetPatientInfo(cprNumber);
			cout << "Patient info found:\n" << patient << endl;
			char c = '$';
			patient += c;
			char buff[80];
			i = 0;
			const char * patientInfoToSend = patient.c_str();
			while (i != strlen(patientInfoToSend))
			{
				buff[i] = patientInfoToSend[i];
				i++;
			}
			peer().send(buff, sizeof(buff) - 1, 0);
		}
	}
	string GetPatientInfo(char * cprNumber)
	{
		ifstream file;
		string search(cprNumber);
		string line;
		file.open("People.txt");
		unsigned int curLine = 0;
		while (getline(file, line))
		{
			curLine++;
			if (line.find(search, 0) != string::npos) break;
		}
		file.close();
		return line;
	}
};
typedef Acceptor<Patient_System, SOCK_Acceptor> Patient_System_Acceptor;
typedef Acceptor<Concrete_Completion_Handler, SOCK_Acceptor> Proactor_Acceptor;
int main()
{
	SetConsoleTitle(TEXT("TCP Socket communication - Server Application"));
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	INET_Addr address = INET_Addr(20, "127.0.0.1");
	Proactor_Acceptor s_acceptor(address, Reactor::instance());
	Reactor::instance()->handle_events();
	Proactor::instance()->handle_events();
	return 0;
}