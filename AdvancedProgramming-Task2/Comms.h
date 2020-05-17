#pragma once
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "stdafx.h"
#include "Exceptions.h";

using namespace std;

// defining comms class variables and methods

class Comms {
public:
	string message;
	const string QUIT = "QUIT";
	template<typename T>

	void ReceiveSocket(T instance, SOCKET socket, int byteCount);
	virtual int WinsockSetup();
	virtual int SocketSetup();
	virtual sockaddr_in ServiceSetup();
	virtual int CloseSession();
	static void ViewException(string msg) {
		cout << "ERROR --> " << msg << endl;
	}
};

template <typename T>
inline void Comms::ReceiveSocket(T params, SOCKET socket, int byteCount) {
	try {
		if (socket != INVALID_SOCKET) {
			byteCount = recv(socket, (char*)params.instance, params.size, 0);
			if (byteCount == SOCKET_ERROR) {
				throw ExceptionSocketError();
			}
			else {
				if (params.instance->message != "") {
					cout << params.name << ": " << params.instance->message << endl;
				}
			}
		}
		else {
			throw ExceptionInvalidSocket();
		}
	}
	catch (ExceptionInvalidSocket& e) {
		ViewException(e.what());
	}
	catch (ExceptionSocketError& e) {
		ViewException(e.what());
		closesocket(socket);
		exit(0);
	}
}