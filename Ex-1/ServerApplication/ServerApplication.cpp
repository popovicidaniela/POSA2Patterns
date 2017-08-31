// ServerApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../WrapperFacade/INET_Addr.h"
#include "../WrapperFacade/SOCK_Acceptor.h"
#include "../WrapperFacade/SOCK_Stream.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace WrapperFacade;
using namespace std;

int main()
{
	SetConsoleTitle(TEXT("TCP Socket communication - Server Application"));
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	INET_Addr address = INET_Addr(20, "127.0.0.1");
	SOCK_Acceptor acceptor = SOCK_Acceptor(address);
	cout << "Waiting for clients to connect" << endl;
	SOCK_Stream s = SOCK_Stream();
	acceptor.accept(s);
	cout << "Client connected" << endl;
	SOCKET socket = s.get_handle();
	cout << "Hello from Client ";
	INET_Addr::get_ip_address(socket);
	cout << endl;
	char buffer[80];
	s.recv(buffer, sizeof(buffer) - 1, 0);
	cout << "Message from Client: ";
	for(int i = 0; i < sizeof(buffer) - 1; i++)
	{
		if (buffer[i]=='$')
		{
			break;
		}
		cout << buffer[i];
	}
	cout << endl;
	s.~SOCK_Stream();
	system("pause");
	return 0;
}