#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdafx.h"
#include "pch.h"
#include "Server.h"
#include "Client.h"

#define SERVER false // needs to be set to true or false

using namespace std;

// prints some information and then proceeds to run either client or server

int main()
{
	cout << "Welcome to Kavita's Chat Room!" << endl;
	cout << "Type 'QUIT' if you want to leave."<< endl << endl;
	cout << "But winners never quit." << endl << endl;

	if (SERVER) {
		Server server;
		server.Run();
	}
	else {
		Client client;
		client.Run();
	}
}