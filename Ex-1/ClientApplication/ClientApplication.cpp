// ClientApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../WrapperFacade/INET_Addr.h"
#include "../WrapperFacade/SOCK_Connector.h"
#include "../WrapperFacade/SOCK_Stream.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace WrapperFacade;
using namespace std;

int main()
{
	SetConsoleTitle(TEXT("TCP Socket communication - Client Application"));
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	INET_Addr address = INET_Addr(20, "127.0.0.1");
	SOCK_Stream s = SOCK_Stream();
	SOCK_Connector connector = SOCK_Connector(address, s);
	cout << "Connected to server" << endl;
	char array1[20];
	cout << "Write the message you want to send: ";
	cin >> array1;
	char c = '$';
	strncat_s(array1, &c, 1);
	s.send(array1, sizeof(array1), 0);
	s.~SOCK_Stream();
	system("pause");
	return 0;
}