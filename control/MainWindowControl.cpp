#include "MainWindowControl.hpp"


void MainWindowControl::login_logout(){
	string user, passwd;
	Glib::RefPtr<TextBuffer> text;
	text = Gtk::TextBuffer::create();

	if(main_window->get_connect_disconnect()->get_active() == true){
		text->set_text("True");
		main_window->get_connection_log()->set_buffer(text);
	}else{
		text->set_text("False");
		main_window->get_connection_log()->set_buffer(text);
	}
}

MainWindowControl::MainWindowControl(FTPClient* ftp_client, MainWindow* main_window){
	FTPClient* ftp_client;
	MainWindow* main_window;
}

MainWindowControl::void connect(){
	main_window->get_connection_log->signal_clicked().connect(sigc::mem_fun(*this,&MainWindowControl::login_logout));
}
