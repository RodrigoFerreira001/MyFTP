#include "FTPServer.hpp"

FTPServer::FTPServer(string ip, int port, int buffer_size){
    server_socket = new Socket(ip, port);
    directory = new Directory(".");
    this->buffer_size = new int(buffer_size);
    db = new map<string, string>;
    db->insert(pair<string, string>("Rodrigo","root"));
}

FTPServer::~FTPServer(){
    server_socket->close(0);
    server_socket->close(1);
    delete server_socket;
    delete directory;
    delete buffer_size;
    delete db;
}

void FTPServer::get(string file_name){
    char* buffer = new char[*buffer_size];
    stringstream* ss;
    string msg;

	cout << "get: " << endl;

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

    FileBuffer* file = new FileBuffer(file_name.c_str(), *buffer_size, 0);
    if(file->open_file() && !is_folder){

        memset(buffer, '\0', *buffer_size);
        msg = "OK";
        msg.copy(buffer, msg.size(), 0);
        server_socket->send(1, buffer, *buffer_size);

        //Envia o tamanho do arquivo
        memset(buffer, '\0', *buffer_size);
        ss = new stringstream();
        *(ss) << file->file_size();
        *(ss) >> buffer;
        delete ss;
        server_socket->send(1, buffer, *buffer_size);

		cout << "Arquivo: " << file_name << ", Tamanho: " << file->file_size() << endl;

		//Envia os n pacotes inteiros
	    for(int i = 0; i < file->packages_number(); i++){
	    	file->read_file(buffer, *buffer_size);
	    	server_socket->send(1, buffer, *buffer_size);
	   	}

        file->read_file(buffer, file->remaining_bytes());
        server_socket->send(1, buffer, file->remaining_bytes());
		cout << "Transferência concluída!" << endl << endl;

    }else{
		cout << "Erro ao abrir o arquivo!" << endl << endl;
        memset(buffer, '\0', *buffer_size);
        msg = "NOT_OK";
        msg.copy(buffer, msg.size(), 0);
        server_socket->send(1, buffer, *buffer_size);
    }

	delete file;
	delete tmp_dir;
	delete buffer;
}

void FTPServer::put(string file_name){
    string msg;
    char* buffer = new char[*buffer_size];
    FileBuffer* file;
    int file_size;
    stringstream* ss;

	cout << "put: " << file_name << endl;
    //Recebe mensagem de confirmação
    memset(buffer, '\0', *buffer_size);
    server_socket->recv(1, buffer, *buffer_size);
    msg = string(buffer);

    if(msg == "OK"){
        //Recebe o tamanho do arquivo
        memset(buffer, '\0', *buffer_size);
        server_socket->recv(1, buffer, *buffer_size);
        ss = new stringstream;
        *(ss) << buffer;
        *(ss) >> file_size;
        delete ss;
		cout << "Arquivo: " << file_name << ", Tamanho: " << file_size << endl;

        //Recebe os pacotes inteiros
        file = new FileBuffer(file_name, *buffer_size, file_size);

		for(int i = 0; i < file->packages_number(); i++){
	    	memset(buffer, '\0', *buffer_size);
	    	server_socket->recv(1, buffer, *buffer_size);

	        for(int j = 0; j < *buffer_size; j++){
	        	file->append_byte(buffer[j]);
	    	}
			file->write_to_file();
	    }

        //Recebe os bytes restantes
        memset(buffer, '\0', *buffer_size);
        server_socket->recv(1, buffer, file->remaining_bytes());
        for(int i = 0; i < file->remaining_bytes(); i++){
            file->append_byte(buffer[i]);
        }

        //Escreve arquivo para arquivo
        file->write_to_file();
		file->finish_write();
		delete file;
		cout << "Transferência concluída!" << endl << endl;
    }

	delete buffer;
}

void FTPServer::cd(string dir_name){
	char* buffer = new char[*buffer_size];
	string msg;
	cout << "cd: " << dir_name << endl << endl;
	if(directory->change_dir(dir_name)){
		memset(buffer, '\0', *buffer_size);
        msg = "OK";
        msg.copy(buffer, msg.size(), 0);
        server_socket->send(1, buffer, *buffer_size);
	}else{
		memset(buffer, '\0', *buffer_size);
        msg = "NOT_OK";
        msg.copy(buffer, msg.size(), 0);
        server_socket->send(1, buffer, *buffer_size);
	}

	delete buffer;
}

void FTPServer::ls(string dir_name){
	char* buffer = new char[*buffer_size];
	string msg, cur_dir;
	stringstream* ss;
	vector<string>* dir_content;
	cout << "ls: " << dir_name << endl << endl;
	cur_dir = directory->get_working_dir();

	if(dir_name.size() != 0){
		if(directory->change_dir(dir_name)){
			memset(buffer, '\0', *buffer_size);
	        msg = "OK";
	        msg.copy(buffer, msg.size(), 0);
	        server_socket->send(1, buffer, *buffer_size);

			dir_content = directory->get_dir_list();

			//Envia o tamanho do diretório
			memset(buffer, '\0', *buffer_size);
			ss = new stringstream;
			*(ss) << dir_content->size();
			*(ss) >> buffer;
			delete ss;
			server_socket->send(1, buffer, *buffer_size);

			for(int i = 0; i < dir_content->size(); i++){
				memset(buffer, '\0', *buffer_size);
				dir_content->at(i).copy(buffer, dir_content->at(i).size(), 0);
				server_socket->send(1, buffer, *buffer_size);
			}

			directory->change_dir(cur_dir);

		}else{
			memset(buffer, '\0', *buffer_size);
	        msg = "NOT_OK";
	        msg.copy(buffer, msg.size(), 0);
	        server_socket->send(1, buffer, *buffer_size);
		}

	}else{
		memset(buffer, '\0', *buffer_size);
        msg = "OK";
        msg.copy(buffer, msg.size(), 0);
        server_socket->send(1, buffer, *buffer_size);


		dir_content = directory->get_dir_list();

		//Envia o tamanho do diretório
		memset(buffer, '\0', *buffer_size);
		ss = new stringstream;
		*(ss) << dir_content->size();
		*(ss) >> buffer;
		delete ss;
		server_socket->send(1, buffer, *buffer_size);

		for(int i = 0; i < dir_content->size(); i++){
			memset(buffer, '\0', *buffer_size);
			dir_content->at(i).copy(buffer, dir_content->at(i).size(), 0);
			server_socket->send(1, buffer, *buffer_size);
		}
	}

	delete buffer;
}

void FTPServer::start(){
    char* buffer = new char[*buffer_size];
    string msg;
    string user, passwd;
    string command, argument;
    map<string, string>::iterator it;

    while(true){
		user = "";
		passwd = "";
		cout << "Aguardando conexão..." << endl;

        server_socket->bind();
        server_socket->listen(5);
        server_socket->accept();

		cout << "Conexão estabelecida, aguardando usuário e senha..." << endl;

        //Recebe o nome do usuário para o buffer
        memset(buffer, '\0', *buffer_size);
        server_socket->recv(1, buffer, *buffer_size);
        user = string(buffer);

        //Recebe a senha para o buffer
        memset(buffer, '\0', *buffer_size);
        server_socket->recv(1, buffer, *buffer_size);
        passwd = string(buffer);

        //Pesquisa usuário e senha no banco de dados
        it = db->find(user);
        if(it != db->end() && it->second == passwd){

			cout << "Usuário e senha aceitos, seja bem vindo!" << endl;
            memset(buffer, '\0', *buffer_size);
            msg = "OK";
            msg.copy(buffer, msg.size(), 0);
            server_socket->send(1, buffer, *buffer_size);

            command = "";
			argument = "";

            //Enquanto o comando recebido do cliente for diferente de exit
            while(command != "exit"){
                memset(buffer, '\0', *buffer_size);
                server_socket->recv(1, buffer, *buffer_size);
                command = string(buffer);

                if(command == "exit"){
                    cout << "Fechando conexão" << endl;
                    break;
                }else{
                    memset(buffer, '\0', *buffer_size);
                    server_socket->recv(1, buffer, *buffer_size);
                    argument = string(buffer);
            	}

				if(command != ""){
					cout << "Comando recebido: " << command << " " << argument << endl;
				}

	            //Trata os comandos
	            if(command == "get"){
	                get(argument);
	            }else
	            if(command == "put"){
	                put(argument);
	            }else
	            if(command == "cd"){
					cd(argument);
	            }else
	            if(command == "ls"){
	                ls(argument);
	            }
        	}
        }else{
			cout << "Usuário e senha não aceitos, tente novamente!" << endl;
            //Usuário e senha não conferem
            memset(buffer, '\0', *buffer_size);
            msg = "NOT_OK";
            msg.copy(buffer, msg.size(), 0);
            server_socket->send(1, buffer, *buffer_size);
        }
    }
}
