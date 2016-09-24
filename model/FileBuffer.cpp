#include "FileBuffer.hpp"

FileBuffer::FileBuffer(string file_name, int buffer_size, int file_size = 0){
    this->file_name = new string;
    this->file_s = new int;
    this->size = new int;
    this->packages = new int;
    this->r_bytes = new int;
    this->file_buffer = new vector<char>();
	this->file_out = NULL;
	this->file = NULL;

    *(this->file_name) = file_name;
    *size = buffer_size;

    if(file_size == 0){
        file = fopen(file_name.c_str(), "rb");


        if(file != NULL){
            fseek(file, 0, SEEK_END);
            *file_s = ftell(file);
            fseek(file, 0, SEEK_SET);

            *packages = (*file_s / buffer_size);
            *r_bytes = *file_s - (*packages * buffer_size);
        }
    }else{
        *file_s = file_size;
        *packages = (*file_s / buffer_size);
        *r_bytes = *file_s - (*packages * buffer_size);
    }
}

FileBuffer::~FileBuffer(){
    delete file_s;
    delete size;
    delete packages;
    delete r_bytes;
    delete file_buffer;

	if(file != NULL){
		fclose(file);
	}

	if(file_out != NULL){
		fclose(file_out);
	}

}

int FileBuffer::open_file(){
    if(file != NULL){
        return 1;
    }else{
        return 0;
    }
}

void FileBuffer::read_file(char* buffer, int buffer_size){
    if(file != NULL && buffer_size <= *size){
        memset(buffer, '\0', *size);
        for(int i = 0; i < buffer_size; i++){
            fscanf(file, "%c", &(buffer[i]));
        }
    }
}

int FileBuffer::file_size(){
    return *file_s;
}

int FileBuffer::packages_number(){
    return *packages;
}

int FileBuffer::remaining_bytes(){
    return *r_bytes;
}

void FileBuffer::append_byte(char byte){
    file_buffer->push_back(byte);
}

void FileBuffer::write_to_file(){


	if(file_out == NULL){
		file_out = fopen(file_name->c_str(),"wb");

		for(int i = 0; i < file_buffer->size(); i++){
	        fprintf(file_out,"%c",file_buffer->at(i));
	    }

		file_buffer->clear();
	}else{
		for(int i = 0; i < file_buffer->size(); i++){
	        fprintf(file_out,"%c",file_buffer->at(i));
	    }

		file_buffer->clear();
	}
}

void FileBuffer::finish_write(){
	if(file_out != NULL){
		fclose(file_out);
		file_out = NULL;
	}
}
