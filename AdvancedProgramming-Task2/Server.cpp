#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "stdafx.h"
#include "Server.h"

int Server::Run() {
	SOCKET serverSocket;
	Server server;
	SERVICEPARAMS serviceParams;

	this->WinsockSetup();
	serverSocket = this->SocketSetup();
	this->ServiceBinder(serverSocket);
	this->ClientListener(serverSocket);
	SOCKET acceptSocket = this->AcceptConnection(serverSocket);

	DWORD threadID;
	cout << "Client Connected! WOO!" << endl;
	serviceParams.socket = (LPVOID)acceptSocket;
	serviceParams.instance = this;
	serviceParams.size = sizeof(Server);
	serviceParams.name = "Server";

	CreateThread(NULL, 0, this->ServerThreadSender, &serviceParams, 0, &threadID); // creating a thread

	cout << "YOUR SERVER IS RUNNING! YEAH BOII!!!" << endl << endl; // printing message when server is running and how to send message
	cout << "Type your messages and press ENTER to send it:" << endl << endl;

	int byteCount = 0;
	while (true) {
		this->ReceiveSocket<SERVICEPARAMS>(serviceParams, (SOCKET)acceptSocket, byteCount);  // receiving messages while true, otherwise it moves on to end session
	}
	closesocket(acceptSocket); // ends session
	return this->CloseSession();
}

int Server::ServiceBinder(SOCKET serverSocket) { // function for binding service 
	try {
		sockaddr_in service = this->ServiceSetup();
		if (bind(serverSocket, (SOCKADDR*)&service, sizeof(Server)) == SOCKET_ERROR) {
			throw ExceptionBindingServer();
		}
		return 1; // returns 1 if binded ok
	}
	catch (ExceptionBindingServer& e) {
		ViewException(e.what());
		closesocket(serverSocket);
		WSACleanup();
	}
}

void Server::ClientListener(SOCKET serverSocket) { // function that listens to client for socket connection
	try {
		if (listen(serverSocket, 1) == SOCKET_ERROR) {
			throw ExceptionListenSocketServer();
		}
		else {
			cout << "_______Waiting for client to connect________" << endl; // printing message while waiting
		}
	}
	catch (ExceptionListenSocketServer& e) {
		ViewException(e.what());
	}
}

int Server::AcceptConnection(SOCKET socket) { // function that accepts connection from client
	try {
		SOCKET acceptSocket = accept(socket, NULL, NULL); // accepts socket connection
		if (acceptSocket == INVALID_SOCKET) {
			throw ExceptionAcceptServerConnection();
		}
		return acceptSocket; // returns accept to client - then they know connection is successful
	}
	catch (ExceptionAcceptServerConnection& e) {
		ViewException(e.what());
		return -1;
	}
}

DWORD WINAPI Server::ServerThreadSender(void* param) { // function that send messages to server
	SERVICEPARAMS* params = (SERVICEPARAMS*)param;
	SOCKET socket = (SOCKET)params->socket;
	Server server;
	int byteCount;
	bool shouldRun = true;

	try {
		while (shouldRun) {
			Sleep(500);
			if (socket != INVALID_SOCKET) {
				byteCount = send(socket, (char*)&server, sizeof(Server), 0); // keeps sending messages to client when theres no error
				if (byteCount == SOCKET_ERROR) {
					throw ExceptionSendServer();
				}
				else {
					cin >> server.message;
					if (server.message == server.QUIT) { // quits session when server types quit
						shouldRun = false;
						exit(0);
					};
				}
			}
			else {
				throw ExceptionInvalidSocket();
			}
		}
		closesocket(socket);
		return 0;
	}
	catch (ExceptionInvalidSocket& e) {
		ViewException(e.what());
	}
	catch (ExceptionSendServer& e) {
		ViewException(e.what());
		closesocket(socket);
		return -1;
	}
}