#include "MainWindowControl.hpp"

void MainWindowControl::login_logout(){
	//Armazena usuário e senha
	string user, passwd;

	//Busca o buffer do log
	Glib::RefPtr<TextBuffer> text;
	text = main_window->get_connection_log()->get_buffer();

	user = string(main_window->get_user_entry()->get_text().c_str());
	passwd = string(main_window->get_passwd_entry()->get_text().c_str());
	main_window->get_remote_list()->clear();

	//Se o botão for pressionado e o estado final for ativo
	if(main_window->get_connect_disconnect()->get_active()){
		//Se não haver conexão
		if(ftp_client->get_status() == false){
			//Se a conexão for bem sucessedida
			if(ftp_client->connect()){
				text->insert_at_cursor("\nConexão estabelecida");
				//Se o login ocorrer com sucesso
				if(ftp_client->login(user, passwd)){
					text->insert_at_cursor("\nLogin estabelecido!");
					main_window->get_connect_disconnect()->set_label("Desconectar");
					main_window->get_remote_list()->insert(ftp_client->ls(""));
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
	}else{ // Botão com estado final inativo
		//Se existir conexão
		if(ftp_client->get_status()){
			text->insert_at_cursor("\nConexão encerrada");
			main_window->get_connect_disconnect()->set_label("Conectar");
			main_window->get_remote_list()->clear();
			ftp_client->exit();
		}
	}
}

bool MainWindowControl::lls(GdkEventButton* event){
	if(event->type == 5 /*DOUBLE_BUTTON_PRESS*/){
		Item* list_item = (Item* )main_window->get_local_list()->get_selected_row()->get_child();
		if(list_item->get_type() == "folder"){
			if(ftp_client->lcd(string(list_item->get_name()->get_label().c_str()))){
				main_window->get_local_list()->clear();
				main_window->get_local_list()->insert(ftp_client->lls(""));
			}
		}
	}
}

bool MainWindowControl::ls(GdkEventButton* event){
	if(event->type == 5 /*DOUBLE_BUTTON_PRESS*/){
		Item* list_item = (Item* )main_window->get_remote_list()->get_selected_row()->get_child();
		if(list_item->get_type() == "folder"){
			if(ftp_client->cd(string(list_item->get_name()->get_label().c_str()))){
				main_window->get_remote_list()->clear();
				main_window->get_remote_list()->insert(ftp_client->ls(""));
			}
		}
	}
}


void MainWindowControl::close_window(){
	if(ftp_client->get_status()){
		ftp_client->exit();
	}
}

MainWindowControl::MainWindowControl(FTPClient* ftp_client, MainWindow* main_window){
	this->ftp_client = ftp_client;
	this->main_window = main_window;
}

void MainWindowControl::connect(){
	main_window->get_local_list()->insert(ftp_client->lls(""));

	//Toggle button signal handler
	main_window->get_connect_disconnect()->signal_clicked().connect(sigc::mem_fun(*this,&MainWindowControl::login_logout));
	main_window->get_local_list()->signal_button_press_event().connect(sigc::mem_fun(*this,&MainWindowControl::lls));
	main_window->get_remote_list()->signal_button_press_event().connect(sigc::mem_fun(*this,&MainWindowControl::ls));
	main_window->signal_hide().connect(sigc::mem_fun(*this, &MainWindowControl::close_window));
}
