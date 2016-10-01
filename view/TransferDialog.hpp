#ifndef TRANSFERDIALOG_HPP
#define TRANSFERDIALOG_HPP

#include <gtkmm/progressbar.h>
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/box.h>
#include <glibmm/dispatcher.h>
#include <string>
#include <thread>
#include "../model/FTPClient.hpp"
using namespace Gtk;
using namespace std;

class TransferDialog : public Dialog{
private:
	Box* content;
	Label* message;
	ProgressBar *transf_progress;
	Button* ok_button;
	Glib::Dispatcher* dispatcher;

	float* progress;
	bool* has_finish;
	thread* work_thread;

	void on_close();
	void on_notification_from_worker_thread();
	void update_widgets();

public:
	TransferDialog(string message, Window* modal);
	~TransferDialog();
	ProgressBar* get_transf_progress();
	Button* get_ok_button();
	void set_message(string message);
	void put_file(string file_name , FTPClient* ftp_client);
	//void get(string file_name, FTPClient* ftp_client);
	void notify(float progress, bool has_finish);
};

#endif
