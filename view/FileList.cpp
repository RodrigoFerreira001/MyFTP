#include "FileList.hpp"
#include <iostream>
using namespace std;

void FileList::insert(vector<string>* dir_content){
	for(int i = 0; i < dir_content->size(); i++){
		string name = dir_content->at(i);
		Item* item;

		if(name.back() == '/'){
			name.pop_back();
			item = new Item(name, "folder");
		}else{
			item = new Item(name, "file");
		}
		append(*item);
	}
	show_all_children();
}

void FileList::clear(){
	vector<Widget*> children = get_children();
	for(int i = 0; i < children.size(); i++){
		remove(*(children.at(i)));
		delete children.at(i);
	}
}
