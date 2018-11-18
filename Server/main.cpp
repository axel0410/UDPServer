#pragma once
#include <iostream>
#include "server.h"

int main() {

	server serv;

	serv.Setup();
	//serv.Receive_Data();
	serv.Send_Data();

	return 0;
}