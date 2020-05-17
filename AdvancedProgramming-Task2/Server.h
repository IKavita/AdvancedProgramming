#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include "stdafx.h"
#include "Comms.h"

using namespace std;

// defining sever class variables and methods

class Server : public Comms {
public:
	Server() {};
	int Run();
	int ServiceBinder(SOCKET serverSocket);
	void ClientListener(SOCKET serverSocket);
	int AcceptConnection(SOCKET serverSocket);
private:
	static DWORD WINAPI ServerThreadSender(void* param);
	struct SERVICEPARAMS {
		LPVOID socket;
		Server* instance;
		int size;
		string name;
	};
};