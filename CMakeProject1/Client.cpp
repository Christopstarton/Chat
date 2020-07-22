#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include "Client.h"
#include <iostream>
#include <string> 
#pragma comment(lib, "ws2_32.lib") 
struct sockaddr_in sin_client;
SOCKET listensocket;
Client::Client() {
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(sockVersion, &wsadata) != 0) //通过一个进程初始化ws2_32.dll
	{
		std::cout << "Initialize WSA failed" << std::endl;
		return;
	}
}
void Client::ConnectSerever() {
	bool ret = false;
	sin_client.sin_family = AF_INET; //设置地址家族	
	sin_client.sin_port = htons(8888); //设置端口号
	sin_client.sin_addr.S_un.S_addr = htonl("127.0.0.1");
	listensocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(listensocket, (sockaddr*)&sin_client, sizeof(sin_client)) == 0)
	{
		std::cout << "Connect!" << std::endl;
	}		
	while (true) {
		send(listensocket, SendBuff, strlen(SendBuff), 0);
		char buffer[1025];
		int num = 0;
		num = recv(listensocket, buffer, 1024, 0);//阻塞 		
		if (num > 0)
		{
			buffer[num] = '\0';
			std::cout << buffer << std::endl;
		}
		closesocket(listensocket); //关闭监听套接字
	}
}
Client::~Client()
{	
	closesocket(listensocket); //关闭监听套接字	
	WSACleanup(); //终止Ws2_32.dll的使用
}
		