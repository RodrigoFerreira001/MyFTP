#pragma once

#include "Directory.hpp"
#include "FileBuffer.hpp"
#include "Socket.hpp"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class FTPClient{
private:
    Socket* client_socket;
    Directory* directory;
	string* ip;
	int* port;
    int* buffer_size;
	bool* is_connected;

public:
    FTPClient(string ip, int port, int buffer_size);
    ~FTPClient();

	bool get_status();
	int connect();
	int disconnect();
    int login(string user, string passwd);
    int get(string file_name);
    int put(string file_name);

    vector<string>* ls(string dir_name);
    vector<string>* lls(string dir_name);

    int cd(string dir_name);
    int lcd(string dir_name);

    void exit();
};
