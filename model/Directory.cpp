#include "Directory.hpp"

Directory::Directory(string cur_dir){
    this->dir_content = new vector<string>();
    this->dir = opendir(cur_dir.c_str());
    this->cur_dir = new string;

    char* wd = new char[1024];
    *(this->cur_dir) = string(getcwd(wd, 1024));
    delete wd;
}

Directory::~Directory(){
    delete dir_content;
    delete cur_dir;
    closedir(dir);
}

bool Directory::dir_sort(string i,string j){
	if(i.back() == '/' && j.back() != '/'){
		return true;
	}else
	if(i.back() == '/' && j.back() == '/'){
		return(i < j);
	}else
	if(i.back() != '/' && j.back() == '/'){
		return false;
	}else
	if(i.back() != '/' && j.back() != '/'){
		return (i < j);
	}
}

int Directory::read_dir(){
    if(dir != NULL){
        return 1;
    }else{
        return 0;
    }
}

int Directory::change_dir(string dir){
    if(chdir(dir.c_str()) == 0){
        char* wd = new char[1024];
        *cur_dir = string(getcwd(wd, 1024));
        delete wd;
        return 1;
    }else{
        return 0;
    }
}

string Directory::get_working_dir(){
    return *cur_dir;
}

vector<string>* Directory::get_dir_list(){
    dir = opendir(cur_dir->c_str());
    dir_content->clear();

    while(dir_util = readdir(dir)){
        if(dir_util->d_type == DT_REG){
            dir_content->push_back(string(dir_util->d_name));
        }else
        if(dir_util->d_type == DT_DIR && string(dir_util->d_name) != "."){
            dir_content->push_back(string(dir_util->d_name) + "/");
        }
    }

    sort(dir_content->begin(), dir_content->end(), dir_sort);

    return dir_content;
}
