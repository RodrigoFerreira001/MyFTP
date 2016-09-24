#include "FTPClient.hpp"
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char** argv){

    stringstream* ss;
	string command, argument;
    string ip;
    int port;
	int s_pos;
    int buffer_size = 1024;
	string user, passwd;

    ip = string(argv[1]);

    ss = new stringstream(argv[2]);
    *ss >> port;
    delete ss;

    FTPClient* client = new FTPClient(ip, port, buffer_size);

	cout << "Usuário:\n> ";
	getline(cin, user);

	cout << "Senha:\n> ";
	getline(cin, passwd);

	if(client->login(user, passwd)){
        cout << "Login realizado com sucesso, seja bem vindo!\n";
		while(command != "exit"){
			argument = "";
			cout << "> ";
			getline(cin, command);

			s_pos = command.find_first_of(' ');

			if(s_pos != -1){
				argument = command.substr(s_pos + 1, command.size() - s_pos + 1);
				command = command.substr(0, s_pos);
			}

			if(command == "get"){
				if(argument.size() != 0){
					client->get(argument);
				}else{
					cout << "Erro: informe o nome do arquivo" << endl;
				}
			}else
			if(command == "put"){
				if(argument.size() != 0){
					client->put(argument);
				}else{
					cout << "Erro: informe o nome do arquivo" << endl;
				}
			}else
			if(command == "ls"){
				vector<string>* dir_content = client->ls(argument);
				for(int i = 0; i < dir_content->size(); i++){
					cout << dir_content->at(i) << endl;
				}
			}else
			if(command == "cd"){
				if(argument.size() != 0){
					client->cd(argument);
				}else{
					cout << "Erro: informe o nome do diretório" << endl;
				}
			}else
			if(command == "lls"){
				vector<string>* dir_content = client->lls(argument);
				for(int i = 0; i < dir_content->size(); i++){
					cout << dir_content->at(i) << endl;
				}
			}else
			if(command == "lcd"){
				if(argument.size() != 0){
					client->lcd(argument);
				}else{
					cout << "Erro: informe o nome do diretório" << endl;
				}
			}else
			if(command == "exit"){
				break;
			}else{
				cout << "Comando inválido!" << endl;
			}
		}
    }else{
        cout << "Erro ao fazer login, tente novamente!\n";
    }

	client->exit();

    return 0;
}
