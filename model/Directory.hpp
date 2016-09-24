#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
using namespace std;

class Directory{
private:
    DIR* dir;
    struct dirent* dir_util;
    string* cur_dir;
    vector<string>* dir_content;
    static bool dir_sort(string i,string j);

public:
    Directory(string cur_dir);
    ~Directory();
    int read_dir();
    int change_dir(string dir);
    string get_working_dir();
    vector<string>* get_dir_list();
};
