#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include "stdafx.h"
#include "Comms.h"

using namespace std;

// defining client class variables and functions 

class Client : public Comms {
public:
	Client() {};
	int Run();
private:
	static DWORD WINAPI ClientThreadSender(void* param);
	int Connect(SOCKET clientSocket, sockaddr_in clientService);
	struct SERVICEPARAMS {
		LPVOID socket;
		Client* instance;
		int size;
		string name;
	};
};