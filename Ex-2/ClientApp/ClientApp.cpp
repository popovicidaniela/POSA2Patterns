// ClientApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../AcceptorConnectorPattern/Connector.h"
#include "../AcceptorConnectorPattern/Service_Handler.h"
#include <iostream>
#include "../Reactor/Reactor.h"
#include "../Reactor/AlarmEventHandler.h"
#include "../Reactor/PatientEventHandler.h"
#include "../Reactor/LogEventHandler.h"
#include "../Reactor/Reactor_Implementation.h"
#include "../../Ex-1/WrapperFacade/INET_Addr.h"
#include "../../Ex-1/WrapperFacade/SOCK_Connector.h"
#include "../../Ex-1/WrapperFacade/SOCK_Stream.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace WrapperFacade;
using namespace ReactorPattern;
using namespace std;
typedef Service_Handler <SOCK_Stream> Peer_Router;
class Get_Patient_Info : public Peer_Router {
public:
	virtual void open()
	{
		for (;;)
		{
			char buffer[80];
			cout << "Write a CPR number \t";
			cin >> buffer;
			char c = '$';
			strncat_s(buffer, &c, 1);
			peer().send(buffer, sizeof(buffer) - 1, 0);
			char buff[80];
			peer().recv(buff, sizeof(buff) - 1, 0);
			int i = 0;
			cout << "Patient Info received from server:\n";
			while (buff[i] != '$')
			{
				cout << buff[i];
				i++;
			}
			cout << endl;
		}
	}
};
typedef Connector<Get_Patient_Info, SOCK_Connector> Peer_Connector;
int main()
{
	SetConsoleTitle(TEXT("TCP Socket communication - Client Application"));
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	INET_Addr address = INET_Addr(20, "127.0.0.1");
	Peer_Connector peer_connector(Reactor::instance(), address);
	Get_Patient_Info *patientInfo = new Get_Patient_Info();
	Connection_Mode mode = ASYNC;
	peer_connector.connect(patientInfo, mode);
	if (mode==ASYNC)
	{
		Reactor::instance()->handle_events();
	}
	return 0;
}