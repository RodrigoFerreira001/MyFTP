#include "Item.hpp"

Item::Item(string name, string type){
	this->name = new Label(name);
	this->icon = new Image;
	this->type = new string(type);

	string ext;
	int dot_pos;

	dot_pos = name.find_last_of('.');

	if(type == "file"){
		if(dot_pos != -1){
			ext = name.substr((dot_pos + 1), name.size() - (dot_pos + 1));
			if(ext == "jpg" || ext == "gif" || ext == "jpeg" || ext == "tiff" || ext == "bmp" || ext == "png"){
				this->icon->set_from_icon_name("image-x-generic", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "mp3" || ext == "wav" || ext == "flac" || ext == "midi" || ext == "wma" || ext == "ogg"){
				this->icon->set_from_icon_name("audio-x-generic", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "mkv" || ext == "avi" || ext == "mp4" || ext == "mpeg"){
				this->icon->set_from_icon_name("video-x-generic", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "jar" || ext == "java"){
				this->icon->set_from_icon_name("text-x-java", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "c" || ext == "cpp"){
				this->icon->set_from_icon_name("text-x-c", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "h" || ext == "hpp"){
				this->icon->set_from_icon_name("text-x-generic", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "py" || ext == "pyc"){
				this->icon->set_from_icon_name("text-x-python", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "zip" || ext == "rar" || ext == "gz" || ext == "7z" || ext == "rar5"){
				this->icon->set_from_icon_name("package-x-generic", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "iso"){
				this->icon->set_from_icon_name("application-x-cd-image", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "doc" || ext == "docx" || ext == "odt"){
				this->icon->set_from_icon_name("x-office-document", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "xls" || ext == "xlsx" || ext == "ods"){
				this->icon->set_from_icon_name("x-office-spreadsheet", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "ppt" || ext == "pptx" || ext == "odp"){
				this->icon->set_from_icon_name("x-office-presentation", IconSize(GTK_ICON_SIZE_BUTTON));
			}else
			if(ext == "pdf"){
				this->icon->set_from_icon_name("application-pdf", IconSize(GTK_ICON_SIZE_BUTTON));
			}else{
				this->icon->set_from_icon_name("text-x-generic", IconSize(GTK_ICON_SIZE_BUTTON));
			}
		}else{
			this->icon->set_from_icon_name("text-x-preview", IconSize(GTK_ICON_SIZE_BUTTON));
		}
	}else
	if(type == "folder"){
		this->icon->set_from_icon_name("inode-directory", IconSize(GTK_ICON_SIZE_BUTTON));
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
