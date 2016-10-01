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
		Item* list_item = (Item*)main_window->get_remote_list()->get_selected_row()->get_child();
		if(list_item->get_type() == "folder"){
			if(ftp_client->cd(string(list_item->get_name()->get_label().c_str()))){
				main_window->get_remote_list()->clear();
				main_window->get_remote_list()->insert(ftp_client->ls(""));
			}
		}
	}
}

void MainWindowControl::config(){
	cfg_window->set_transient_for(*main_window);
	cfg_window->run();
}

void MainWindowControl::save_config(){
	cfg_window->hide();
}

void MainWindowControl::close_config_window(){
	cfg_window->get_ip_entry()->set_text("");
	cfg_window->get_port_entry()->set_text("");
	cfg_window->hide();
}


void MainWindowControl::close_window(){
	if(ftp_client->get_status()){
		ftp_client->exit();
	}
}

void MainWindowControl::local_refresh(){
	main_window->get_local_list()->clear();
	main_window->get_local_list()->insert(ftp_client->lls(""));
}

void MainWindowControl::remote_refresh(){
	main_window->get_remote_list()->clear();
	main_window->get_remote_list()->insert(ftp_client->ls(""));
}

void MainWindowControl::put(){
	ListBoxRow* box_row = main_window->get_local_list()->get_selected_row();
	if(box_row != nullptr){
		Item* list_item = (Item*)box_row->get_child();
		string file_name = string(list_item->get_name()->get_label().c_str());

		if(list_item->get_type() == "file"){
			if(ftp_client->put(file_name)){
				main_window->get_remote_list()->clear();
				main_window->get_remote_list()->insert(ftp_client->ls(""));
			}else{
				cout << "Error" << endl;
			}
		}
	}
}

void MainWindowControl::get(){
	ListBoxRow* box_row = main_window->get_remote_list()->get_selected_row();
	if(box_row != nullptr){
		Item* list_item = (Item*)box_row->get_child();
		string file_name = string(list_item->get_name()->get_label().c_str());

		if(list_item->get_type() == "file"){

			if(ftp_client->get(file_name)){
				main_window->get_local_list()->clear();
				main_window->get_local_list()->insert(ftp_client->lls(""));
			}else{
				cout << "Error" << endl;
			}
		}
	}
}

MainWindowControl::MainWindowControl(FTPClient* ftp_client, MainWindow* main_window, ConfigWindow* cfg_window){
	this->ftp_client = ftp_client;
	this->main_window = main_window;
	this->cfg_window = cfg_window;
}

MainWindowControl::~MainWindowControl(){
	if(ftp_client->get_status()){
		ftp_client->exit();
	}
}

void MainWindowControl::connect(){
	main_window->get_local_list()->insert(ftp_client->lls(""));
	cfg_window->set_transient_for(*main_window);

	//Toggle button signal handler
	main_window->get_connect_disconnect()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::login_logout));
	main_window->get_local_list()->signal_button_press_event().connect(sigc::mem_fun(*this, &MainWindowControl::lls));
	main_window->get_remote_list()->signal_button_press_event().connect(sigc::mem_fun(*this, &MainWindowControl::ls));
	main_window->get_local_refresh()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::local_refresh));
	main_window->get_remote_refresh()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::remote_refresh));
	main_window->get_put_button()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::put));
	main_window->get_get_button()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::get));
	main_window->get_config_button()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::config));

	cfg_window->get_cancel()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::close_config_window));
	cfg_window->get_save()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowControl::save_config));

	main_window->signal_hide().connect(sigc::mem_fun(*this, &MainWindowControl::close_window));
}
