#pragma once 
#include <winsock2.h> 
class Server
{
	public:	
		Server();	
		void Message();	
		~Server();
	private:	
		SOCKET listensocket; //´´½¨¼àÌıÌ×½Ó×Ö
};
