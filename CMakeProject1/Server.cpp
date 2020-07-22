#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include <iostream>
#include <string>
SOCKET listensocket; //���������׽���
#pragma comment(lib, "ws2_32.lib")
Server::Server() {
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(sockVersion, &wsadata) != 0) //ͨ��һ�����̳�ʼ��ws2_32.dll
	{
		std::cout << "Initialize WSA failed" << std::endl;
		return;
	}
	listensocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	std::cout << "Creat successfully!" << std::endl;
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8888); // host to network�������ֽ���ת���������ֽ���
	if (bind(listensocket, (LPSOCKADDR)&saddr, sizeof(saddr)) == SOCKET_ERROR) 
		std::cout << "Error!" << std::endl;
	std::cout << "Bound successfully!" << std::endl;
	if (listen(listensocket, 20) == SOCKET_ERROR)  //�׽���, Ϊ���׽����Ŷӵ����������		//��ʱ�� slisten ��Ϊ�����׽���									   
												  
	{		
		std::cout << "Listen Error!" << std::endl;
		closesocket(listensocket); //�رռ����׽���		
		WSACleanup(); //��ֹWs2_32.dll��ʹ��		
		return;	
	} 
	std::cout << "Listen successfully!" << std::endl;
}

void Server::Message() {
	sockaddr_in remoteAddr;
	int len = sizeof(remoteAddr);
	SOCKET sClient = accept(listensocket, (SOCKADDR*)&remoteAddr, &len);
	if (sClient == SOCKET_ERROR)
	{ 
		std::cout << "Connect Error!" << std::endl;
		WSACleanup();  
		return; 
	}  
	std::cout << "Connect!" << std::endl;
	while (true) {
		char revData[1025];
		int recv_len = recv(sClient,revData, 100, 0);
		if (recv_len < 0)
		{
			std::cout << "Exit!" << std::endl;
			break;
		}
		else
		{
			std::cout << revData << std::endl;
		}
		std::cin >> revData;
		int  send_len = send(sClient, revData,100, 0);
		if (send_len < 0)
		{
			std::cout << "Exit!" << std::endl;
			break;
		}
	}
}

Server::~Server() {
	std::cout << "Over" << std::endl;
	closesocket(listensocket); //�رռ����׽���	
	WSACleanup(); //��ֹWs2_32.dll��ʹ��
}
	