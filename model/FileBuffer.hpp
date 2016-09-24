#pragma once

#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

class FileBuffer{
private:
    FILE* file;
	FILE* file_out;
    string* file_name;
    int* file_s;
    int* size;
    int* packages;
    int* r_bytes;
    vector<char>* file_buffer;

public:
    FileBuffer(string file_name, int buffer_size, int file_size);
    ~FileBuffer();
    int open_file();
    void read_file(char* buffer, int buffer_size);
    int file_size();
    int packages_number();
    int remaining_bytes();
    void append_byte(char byte);
    void write_to_file();
	void finish_write();
};
