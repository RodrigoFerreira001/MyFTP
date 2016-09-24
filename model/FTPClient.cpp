#include "FTPClient.hpp"

FTPClient::FTPClient(string ip, int port, int buffer_size){
    client_socket = new Socket(ip, port);
    client_socket->connect();
    directory = new Directory(".");
    this->buffer_size = new int(buffer_size);
}

FTPClient::~FTPClient(){
    client_socket->close(0);
    delete client_socket;
    delete directory;
    delete buffer_size;
}

int FTPClient::login(string user, string passwd){
    string msg;
    char* buffer = new char[*buffer_size];

    //Copia o nome do usuário para o buffer e envia
    memset(buffer, '\0', *buffer_size);
    user.copy(buffer, user.size(), 0);
    client_socket->send(0, buffer, *buffer_size);

    //Copia a senha para o buffer e envia
    memset(buffer, '\0', *buffer_size);
    passwd.copy(buffer, passwd.size(), 0);
    client_socket->send(0, buffer, *buffer_size);

    memset(buffer, '\0', *buffer_size);
    client_socket->recv(0, buffer, *buffer_size);
    msg = string(buffer);

    if(msg == "OK"){
		delete buffer;
        return 1;
    }else{
		delete buffer;
        return 0;
    }
}

int FTPClient::get(string file_name){

	cout << "get: " << file_name << endl;

    string msg;
    char* buffer = new char[*buffer_size];
    FileBuffer* file;
    int file_size;
    stringstream* ss;

    //Envia comando get
    memset(buffer, '\0', *buffer_size);
    msg = "get";
    msg.copy(buffer, msg.size(), 0);
    client_socket->send(0, buffer, *buffer_size);

    //Envia argumento
    memset(buffer, '\0', *buffer_size);
    file_name.copy(buffer, file_name.size(), 0);
    client_socket->send(0, buffer, *buffer_size);

    //Recebe mensagem de confirmação
    memset(buffer, '\0', *buffer_size);
    client_socket->recv(0, buffer, *buffer_size);
    msg = string(buffer);

    if(msg == "OK"){
        //Recebe o tamanho do arquivo
        memset(buffer, '\0', *buffer_size);
        client_socket->recv(0, buffer, *buffer_size);
        ss = new stringstream(buffer);
        *(ss) >> file_size;
        delete ss;

		cout << "Arquivo: " << file_name << ", Tamanho: " << file_size << endl;
        //Recebe os pacotes inteiros
        file = new FileBuffer(file_name, *buffer_size, file_size);

		for(int i = 0; i < file->packages_number(); i++){
	    	memset(buffer, '\0', *buffer_size);
	    	client_socket->recv(0, buffer, *buffer_size);

	    	for(int j = 0; j < *buffer_size; j++){
	        	file->append_byte(buffer[j]);
	        }
			file->write_to_file();
	   	}

        //Recebe os bytes restantes
        memset(buffer, '\0', *buffer_size);
        client_socket->recv(0, buffer, file->remaining_bytes());
        for(int i = 0; i < file->remaining_bytes(); i++){
            file->append_byte(buffer[i]);
        }

        //Escreve arquivo para arquivo
        file->write_to_file();
		file->finish_write();
		cout << "Operação concluída com sucesso!" << endl;

		delete file;
		delete buffer;
        return 1;
    }else{
		cout << "Algum erro ocorreu, verifique o arquivo e tente novamente\n";
		delete buffer;
        return 0;
    }

}

int FTPClient::put(string file_name){
    char* buffer = new char[*buffer_size];
    stringstream* ss;
    string msg;

	Directory* tmp_dir = new Directory(".");
	vector<string>* tmp_dir_c = tmp_dir->get_dir_list();
	string file_name_tmp;
	bool is_folder = false;

	if(file_name.back() != '/'){
		file_name_tmp = file_name + "/";
	}else{
		file_name_tmp = file_name;
	}

	for(int i = 0; i < tmp_dir_c->size(); i++){
		if(tmp_dir_c->at(i) == file_name_tmp){
			is_folder = true;
			break;
		}
	}

	cout << "put: " << file_name << endl;
    //Envia comando put
    memset(buffer, '\0', *buffer_size);
    msg = "put";
    msg.copy(buffer, msg.size(), 0);
    client_socket->send(0, buffer, *buffer_size);

    //Envia argumento
    memset(buffer, '\0', *buffer_size);
    file_name.copy(buffer, file_name.size(), 0);
    client_socket->send(0, buffer, *buffer_size);

    FileBuffer* file = new FileBuffer(file_name.c_str(), *buffer_size, 0);
    if(file->open_file() && !is_folder){
        memset(buffer, '\0', *buffer_size);
        msg = "OK";
        msg.copy(buffer, msg.size(), 0);

		client_socket->send(0, buffer, *buffer_size);
        //Envia o tamanho do arquivo
        memset(buffer, '\0', *buffer_size);
        ss = new stringstream();
        *(ss) << file->file_size();
        *(ss) >> buffer;
        delete ss;
        client_socket->send(0, buffer, *buffer_size);


		for(int i = 0; i < file->packages_number(); i++){
	    	file->read_file(buffer, *buffer_size);
	        client_socket->send(0, buffer, *buffer_size);
	   	}

        file->read_file(buffer, file->remaining_bytes());
        client_socket->send(0, buffer, file->remaining_bytes());

		cout << "Transferência concluída!" << endl;

		delete file;
		delete tmp_dir;
		delete buffer;

        return 1;
    }else{
		cout << "Arquivo inexistente, tente novamente!" << endl;
        memset(buffer, '\0', *buffer_size);
        msg = "NOT_OK";
        msg.copy(buffer, msg.size(), 0);
        client_socket->send(0, buffer, *buffer_size);

		delete file;
		delete tmp_dir;
		delete buffer;

        return 0;
    }
}

int FTPClient::cd(string dir_name){
	char* buffer = new char[*buffer_size];
	string msg;

	memset(buffer, '\0', *buffer_size);
	msg = "cd";
	msg.copy(buffer, msg.size(), 0);
	client_socket->send(0, buffer, *buffer_size);

	memset(buffer, '\0', *buffer_size);
	dir_name.copy(buffer, dir_name.size(), 0);
	client_socket->send(0, buffer, *buffer_size);

	memset(buffer, '\0', *buffer_size);
	client_socket->recv(0, buffer, *buffer_size);
	msg = string(buffer);

	if(msg == "OK"){
		return 1;
	}else{
		return 0;
	}

	delete buffer;
}

int FTPClient::lcd(string dir_name){
	if(directory->change_dir(dir_name)){
		return 1;
	}else{
		return 0;
	}
}

vector<string>* FTPClient::ls(string dir_name){
	char* buffer = new char[*buffer_size];
	vector<string>* dir_content = new vector<string>;
	int dir_size;
	string msg;
	stringstream* ss;

	//Envia o comando ls
	memset(buffer, '\0', *buffer_size);
	msg = "ls";
	msg.copy(buffer, msg.size(), 0);
	client_socket->send(0, buffer, *buffer_size);

	//Envia o argumento
	memset(buffer, '\0', *buffer_size);
	dir_name.copy(buffer, dir_name.size(), 0);
	client_socket->send(0, buffer, *buffer_size);

	//Recebe mensagem de confirmação
	memset(buffer, '\0', *buffer_size);
	client_socket->recv(0, buffer, *buffer_size);
	msg = string(buffer);

	if(msg == "OK"){
		//Recebe o tamanho do arquivo
		memset(buffer, '\0', *buffer_size);
		client_socket->recv(0, buffer, *buffer_size);
		ss = new stringstream(buffer);
		*(ss) >> dir_size;
		delete ss;

		//Recebe os diretórios
		for(int i = 0; i < dir_size; i++){
			memset(buffer, '\0', *buffer_size);
			client_socket->recv(0, buffer, *buffer_size);
			msg = string(buffer);
			dir_content->push_back(msg);
		}
	}

	delete buffer;
	return dir_content;
}

vector<string>* FTPClient::lls(string dir_name){
	string cur_dir = directory->get_working_dir();
	vector<string>* dir_content;

	if(dir_name.size() != 0){
		if(directory->change_dir(dir_name)){
			return directory->get_dir_list();
			directory->change_dir(cur_dir);
		}else{
			dir_content = new vector<string>;
			return dir_content;
		}
	}else{
		return directory->get_dir_list();
	}
}

void FTPClient::exit(){
	char* buffer = new char[*buffer_size];
	string msg;

	memset(buffer, '\0', *buffer_size);
	msg = "exit";
	msg.copy(buffer, msg.size(), 0);
	client_socket->send(0, buffer, *buffer_size);

	client_socket->close(0);
	delete buffer;
}
