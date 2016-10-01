#include "TransferDialog.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

void TransferDialog::on_close(){
	hide();
}

void TransferDialog::on_notification_from_worker_thread(){
	if(work_thread && *has_finish){
		if (work_thread->joinable()){
			work_thread->join();
		}

		delete work_thread;
		work_thread = nullptr;
    }
	update_widgets();
}

void TransferDialog::update_widgets(){
	if(*has_finish){
		ok_button->set_visible(true);
	}else{
		transf_progress->set_fraction(*progress);
		ok_button->set_visible(true);
	}
}

TransferDialog::TransferDialog(string message, Window* modal){
	this->message = new Label(message);
	content = new Box(ORIENTATION_VERTICAL);
	transf_progress = new ProgressBar;
	dispatcher = new Glib::Dispatcher();
	dispatcher->connect(sigc::mem_fun(*this,&TransferDialog::on_notification_from_worker_thread));

	progress = new float(0.0);
	has_finish = new bool(false);

	ok_button = new Button("Concluir");
	ok_button->set_margin_top(6);

	content->pack_start(*(this->message),true,true);
	content->pack_start(*transf_progress,true,true);
	content->pack_start(*ok_button,true,true);

	HeaderBar* hb = new HeaderBar();
	hb->set_title("Transferência de Arquivos");
	hb->set_show_close_button(false);
	set_titlebar(*hb);

	get_content_area()->pack_start(*content, true, true);
	set_transient_for(*modal);
	set_size_request(400,-1);
	set_resizable(false);
	show_all_children();

	ok_button->set_visible(false);

	ok_button->signal_clicked().connect(sigc::mem_fun(*this,&TransferDialog::on_close));
}

TransferDialog::~TransferDialog(){
	delete content;
	delete message;
	delete transf_progress;
}

void TransferDialog::set_message(string message){
	this->message->set_label(message);
}

ProgressBar* TransferDialog::get_transf_progress(){
	return transf_progress;
}

Button* TransferDialog::get_ok_button(){
	return ok_button;
}

void TransferDialog::put_file(string file_name, FTPClient* ftp_client){
	set_message(file_name);
	set_visible(true);

	work_thread = new thread([&]{
		ftp_client->put(file_name, this);
	});
}

/*void TransferDialog::get(string file_name, FTPClient* ftp_client){
	//work_thread = new thread([=]{ftp_client->get(file_name, this);});
}*/


void TransferDialog::notify(float progress, bool has_finish){
	*(this->progress) = progress;
	*(this->has_finish) = has_finish;
	dispatcher->emit();
}
