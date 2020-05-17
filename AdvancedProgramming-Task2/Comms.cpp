#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "stdafx.h"
#include "Comms.h";
#include "Exceptions.h";

// contains code that is common to both the client and server

int Comms::WinsockSetup() { // function to setup winsock
	try {
		WSADATA wsaData;
		WORD wVersionRequested = MAKEWORD(2, 2);
		int wsaerr = WSAStartup(wVersionRequested, &wsaData);

		if (wsaerr != 0) {
			throw ExceptionDLLNotFound();
		}
		else {
			cout << "Winsock Setup OK. Status: " << wsaData.szSystemStatus << endl; // prints the status
			return 1;
		};
	}
	catch (ExceptionDLLNotFound& e) {
		ViewException(e.what());
	}
};

int Comms::SocketSetup() { // function to setup socket
	try {
		SOCKET instanceSocket = INVALID_SOCKET;
		instanceSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (instanceSocket == INVALID_SOCKET) {
			int errorCode = WSAGetLastError();
			throw ExceptionInvalidSocket();
			WSACleanup();
		}
		else {
			cout << "Socket Setup OK." << endl; // prints setup was okay if it works
			return instanceSocket; // returns socket instance
		}
	}
	catch (ExceptionInvalidSocket& e) {
		ViewException(e.what());
	}
}

sockaddr_in Comms::ServiceSetup() { // function to setup service + returns the service
	int port = 55555;
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	return service;
}

int Comms::CloseSession() { // funtion that closes the session
	system("pause");
	WSACleanup();
	return 0;
};