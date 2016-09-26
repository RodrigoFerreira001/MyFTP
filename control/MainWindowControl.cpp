#include "MainWindowControl.hpp"

void MainWindowControl::login_logout(){

	string user, passwd;
	Glib::RefPtr<TextBuffer> text;

	//Busca o buffer do log
	text = main_window->get_connection_log()->get_buffer();

	user = string(main_window->get_user_entry()->get_text().c_str());
	passwd = string(main_window->get_passwd_entry()->get_text().c_str());
	main_window->get_remote_list()->clear();

	if(main_window->get_connect_disconnect()->get_active()){
		if(ftp_client->get_status() == false){
			if(ftp_client->connect()){
				text->insert_at_cursor("\nConexão estabelecida");
				if(ftp_client->login(user, passwd)){
					text->insert_at_cursor("\nLogin estabelecido!");
					main_window->get_connect_disconnect()->set_label("Desconectar");
					main_window->get_remote_list()->insert(ftp_client->ls("."));
					main_window->get_remote_list()->show_all_children();
				}else{
					ftp_client->disconnect();
					text->insert_at_cursor("\nErro no login!");
					main_window->get_connect_disconnect()->set_label("Conectar");
					main_window->get_connect_disconnect()->set_active(false);
				}
			}else{
				text->insert_at_cursor("\nConexão não estabelecida");
				main_window->get_connect_disconnect()->set_label("Conectar");
				main_window->get_connect_disconnect()->set_active(false);
			}
		}
	}else{
		if(ftp_client->get_status()){
			text->insert_at_cursor("\nConexão encerrada");
			main_window->get_connect_disconnect()->set_label("Conectar");
			main_window->get_remote_list()->clear();
			ftp_client->exit();
		}

	}
}


MainWindowControl::MainWindowControl(FTPClient* ftp_client, MainWindow* main_window){
	this->ftp_client = ftp_client;
	this->main_window = main_window;
}

void MainWindowControl::connect(){
	main_window->get_local_list()->insert(ftp_client->lls("."));
	main_window->get_local_list()->show_all_children();
	main_window->get_connect_disconnect()->signal_clicked().connect(sigc::mem_fun(*this,&MainWindowControl::login_logout));
}
