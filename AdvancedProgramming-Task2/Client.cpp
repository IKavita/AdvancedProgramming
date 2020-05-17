#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "stdafx.h"
#include "Client.h"
#include "Exceptions.h";

int Client::Run() { 
	SOCKET clientSocket;
	Client client;
	SERVICEPARAMS serviceParams;

	// services being set up

	this->WinsockSetup();
	clientSocket = this->SocketSetup();
	sockaddr_in clientService = this->ServiceSetup();
	this->Connect(clientSocket, clientService);
	DWORD threadId;

	cout << "_______Client is connecting to a GHOST - oOooooOOooOOOoo_______" << endl; // printing that client is connecting to host

	serviceParams.socket = (LPVOID)clientSocket;
	serviceParams.instance = this;
	serviceParams.size = sizeof(Client);
	serviceParams.name = "Client";

	CreateThread(NULL, 0, this->ClientThreadSender, &serviceParams, 0, &threadId); // creating a thread

	cout << "YOUR CLIENT IS RUNNING! OH YEAH!!!" << endl << endl; // printing when client is running and how to send a message
	cout << "Type your messages and press ENTER to send it:" << endl << endl;

	int byteCount = 0;
	while (true) {
		this->ReceiveSocket<SERVICEPARAMS>(serviceParams, (SOCKET)clientSocket, byteCount); // receiving messages while true, otherwise it moves on to end session
	}
	closesocket(clientSocket);
	return this->CloseSession(); // ends the session
}

int Client::Connect(SOCKET clientSocket, sockaddr_in clientService) {
	try {
		if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(Client)) == SOCKET_ERROR) { // tries to connect to server
			throw ExceptionClientFailedToConnect();
		}
		return 1; // returns 1 if it connects
	}
	catch (ExceptionClientFailedToConnect& e) {
		ViewException(e.what());
		WSACleanup();
		exit(0);
	}
}

DWORD WINAPI Client::ClientThreadSender(void* param) { // function that send messages to server
	SERVICEPARAMS* params = (SERVICEPARAMS*)param;
	SOCKET socket = (SOCKET)params->socket;
	Client client;
	int byteCount;
	bool shouldRun = true;

	try {
		while (shouldRun) {
			Sleep(500);
			if (socket != INVALID_SOCKET) {
				byteCount = send(socket, (char*)&client, sizeof(Client), 0); // keeps sending messages to server when theres no error
				if (byteCount == SOCKET_ERROR) {
					throw ExceptionClientSend();
				}
				else {
					cin >> client.message;
					if (client.message == client.QUIT) { // quits session when client types quit
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
	catch (ExceptionClientSend& e) {
		ViewException(e.what());
		closesocket(socket);
		return -1;
	}
}