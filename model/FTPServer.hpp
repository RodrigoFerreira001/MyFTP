#include "Socket.hpp"
#include "FileBuffer.hpp"
#include "Directory.hpp"
#include <vector>
#include <sstream>
#include <map>
using namespace std;

class FTPServer{
private:
    Socket* server_socket;
    Directory* directory;
    int* buffer_size;
    map<string, string>* db;

    void get(string file_name);
    void put(string file_name);

    void cd(string dir_name);
    void ls(string dir_name);

public:
    FTPServer(string ip, int port, int buffer_size);
    ~FTPServer();
    void start();
};
