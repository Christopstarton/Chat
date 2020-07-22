#pragma once
#include <winsock2.h> 
class Client {
public:
	Client();
	void ConnectSerever();
	~Client();
private:
	SOCKET m_cSocket;
};