#pragma comment(lib, "ws2_32.lib")
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>

using namespace std;
//TCP SERVER PRACTICE
//@Author Mr Smithy x
//Learning C++ TCP Socket Server, accepting and sending information to the client
int main()
{
	long res;
	WSADATA wsaData;
	res = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (res == 0)
		cout << "WSAStartup()\t\t successful" << endl;
	else
		cout << "error WSAStartup(): " << WSAGetLastError() << endl;

	SOCKET slisten, client;
	//ADDRESS FAMILY AF_INET
	//SOCK_DGRAM for udp
	//SOCK_STREAM for tcp
	slisten = socket(AF_INET, SOCK_STREAM, 0);
	if (slisten != INVALID_SOCKET)
		cout << "socket()\t\t successful" << endl;
	else
		cout << "error socket(): " << WSAGetLastError() << endl;

	//sock address
	sockaddr_in info; //sockaddr 
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_family = AF_INET;
	info.sin_port = htons(7331);
	int infolen = sizeof(info);


	res = bind(slisten, (struct sockaddr*)&info, infolen);
	if (res != SOCKET_ERROR)
		cout << "bind()\t\t successful" << endl;
	else
		cout << "error bind(): " << WSAGetLastError() << endl;

	//Queue incomming connections
	res = listen(slisten, SOMAXCONN);

	if (res != SOCKET_ERROR)
		cout << "listen()\t\t successful" << endl;
	else
		cout << "error listen(): " << WSAGetLastError() << endl;

	sockaddr_in clientinfo;
	int clientinfolen = sizeof(clientinfo);

	while (1)
	{
		client = accept(slisten,(struct sockaddr*)&clientinfo, &clientinfolen);
		if (client != SOCKET_ERROR){
			cout << "client accepted: " << inet_ntoa(clientinfo.sin_addr) << ":"
				<< htons(clientinfo.sin_port) << endl;
		}
		res = send(client, "server message recieved", strlen("server message recieved"), 0);
		if (res == SOCKET_ERROR){
			cout << "error send()" << endl;
		}
	}

	closesocket(client);
	closesocket(slisten);
	WSACleanup();
	return 0;
}