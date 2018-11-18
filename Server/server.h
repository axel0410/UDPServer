#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

class server
{
public:

	void Setup();
	void Receive_Data();
	void Send_Data();
	void closeConnection();
	

private:
	SOCKET inSocket;
	SOCKET outSocket;
	sockaddr_in server;
};

