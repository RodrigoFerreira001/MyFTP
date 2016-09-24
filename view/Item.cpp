#include "Item.hpp"

Item::Item(string name, string type){
	this->name = new Label(name);
	this->icon = new Image;
	this->type = new string(type);

	if(type == "folder"){
		this->icon->set_from_icon_name("inode-directory", IconSize(GTK_ICON_SIZE_BUTTON));
	}else
	if(type == "file"){
		this->icon->set_from_icon_name("gtk-file", IconSize(GTK_ICON_SIZE_BUTTON));
	}

	pack_start(*(this->icon), false, false, 8);
	pack_start(*(this->name), false, false, 8);
}

Item::~Item(){
	delete this->name;
	delete this->icon;
	delete this->type;
}

void Item::set_name(string name){
	this->name->set_label(name);
}

Label* Item::get_name(){
	return this->name;
}

Image* Item::get_icon(){
	return this->icon;
}

void Item::set_type(string type){
	*(this->type) = type;

	if(type == "folder"){
		this->icon->set_from_icon_name("inode-directory", IconSize(GTK_ICON_SIZE_BUTTON));
	}else
	if(type == "file"){
		this->icon->set_from_icon_name("gtk-file", IconSize(GTK_ICON_SIZE_BUTTON));
	}
}

string Item::get_type(){
	return *(this->type);
}
