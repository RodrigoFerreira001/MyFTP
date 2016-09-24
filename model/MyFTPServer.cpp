#include "FTPServer.hpp"
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char** argv){

    stringstream* ss;
    string ip;
    int port;
    int buffer_size = 1024;

    ip = string(argv[1]);

    ss = new stringstream(argv[2]);
    *ss >> port;
    delete ss;

    FTPServer* server = new FTPServer(ip, port, buffer_size);
    server->start();

    return 0;
}
