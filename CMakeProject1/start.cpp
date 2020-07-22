
#pragma comment(lib, "shlwapi")
#include<iostream>
#include <string>
#include "Server.h"
#include "Client.h"

using namespace std;
using std::cout;
using std::endl;
using std::stoi;

int main(int argc, char* argv)
{
	if (strcmp(argv, "server") == 0) {
		Server server;
		server.Message();
	}
	if (strcmp(argv, "client") == 0) {
		Client client;
		client.ConnectSerever();
	}
	else
		cout << "Error!" << endl;
	return 0;
}
