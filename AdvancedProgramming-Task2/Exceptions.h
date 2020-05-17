#pragma once
#include <exception>
#include <string>

using namespace std;

// Holds all exceptions that are called from other classes, each of them return some error text relating to the specific error.

class ExceptionAcceptServerConnection : public exception {
public:
	virtual const char* what() const throw() {
		return "Server Error - Won't accept socket connection!";
	}
};

class ExceptionSendServer : public exception {
public:
	virtual const char* what() const throw() {
		return "Server Error - Failed to send!";
	}
};

class ExceptionDLLNotFound : public exception {
public:
	virtual const char* what() const throw() {
		return "Winsock DLL NOT FOUND! It's Lost! £1 Reward if found.";
	}
};

class ExceptionClientFailedToConnect : public exception {
public:
	virtual const char* what() const throw() {
		return "Connection Error - Client failed to connect. Check if server is running.";
	}
};

class ExceptionClientSend : public exception {
public:
	virtual const char* what() const throw() {
		return "Client Error - Client failed to send.";
	}
};

class ExceptionBindingServer : public exception {
public:
	virtual const char* what() const throw() {
		return "Server Error - Server failed to bind.";
	}
};

class ExceptionSocketError : public exception {
public:
	virtual const char* what() const throw() {
		return "Socket Error.";
	}
};

class ExceptionInvalidSocket : public exception {
public:
	virtual const char* what() const throw() {
		return "Socket is Invalid.";
	}
};

class ExceptionListenSocketServer : public exception {
public:
	virtual const char* what() const throw() {
		return "Server Error - Error when listening on socket!";
	}
};
