#include "server.h"

//clinet may need a unique identifier sent to them when they first connect
void server::Setup() {

	//start winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOK = WSAStartup(version, &data);
	if (wsOK != 0) {
		std::cout << "Cant Start Winsock" << wsOK;
	}
	

	//SETUP RECEIVING DATA
	inSocket = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in serverHint;
	serverHint.sin_family = AF_INET;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_port = htons(54001); // Receive PORT     Convert from little to big endian

	if (bind(inSocket, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
		std::cout << "Cant bind socket" << WSAGetLastError() << std::endl;
		return;
	}

	//SETUP SENDING DATA
	server.sin_family = AF_INET;
	server.sin_port = htons(54000); // Send PORT
	inet_pton(AF_INET, "192.168.1.84", &server.sin_addr);
	//Socket creation
	outSocket = socket(AF_INET, SOCK_DGRAM, 0);

}

void server::Send_Data() {

	//write out to socket

		std::string s = "La Test";

		int sendOk = sendto(outSocket, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR) {
			std::cout << "Sending failed: " << WSAGetLastError << std::endl;
		}
		else {
			std::cout << "Sent: " << s << std::endl;
		}
		while (true) {}
}

void server::Receive_Data(){
	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);

	char buf[1024]; // where message is recived into

	ZeroMemory(buf, 1024);
	int bytesIn = recvfrom(inSocket, buf, 1024, 0, (sockaddr*)&client, &clientLength);
	if (bytesIn == SOCKET_ERROR) {
		std::cout << "Error Reveving from client" << std::endl;
	}
	//display data
	char clientIp[256];
	ZeroMemory(clientIp, 256);

	inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

	std::cout << "Message from " << clientIp << ":" << buf << std::endl;
}


void server::closeConnection() {
	//close socket
	closesocket(inSocket);
	closesocket(outSocket);
	//shutdown winsock
	WSACleanup();
}
