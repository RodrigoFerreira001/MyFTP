#pragma once

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/separator.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/headerbar.h>

#include <string>
#include <vector>
#include "FileList.hpp"
using namespace std;
using namespace Gtk;

class MainWindow : public Window{
private:
	Button* config_button;
	Entry* user_entry;
	Entry* passwd_entry;
	ToggleButton* connect_disconnect;
	Button* local_refresh;
	Button* local_mkdir;
	Button* local_rm;
	Button* remote_refresh;
	Button* remote_mkdir;
	Button* remote_rm;
	FileList* local_list;
	FileList* remote_list;
	Button* get_button;
	Button* put_button;
	TextView* connection_log;

public:
	MainWindow();
	~MainWindow();
	
	Button* get_config_button();
	Entry* get_user_entry();
	Entry* get_passwd_entry();
	ToggleButton* get_connect_disconnect();
	Button* get_local_refresh();
	Button* get_local_mkdir();
	Button* get_local_rm();
	Button* get_remote_refresh();
	Button* get_remote_mkdir();
	Button* get_remote_rm();
	FileList* get_local_list();
	FileList* get_remote_list();
	Button* get_get_button();
	Button* get_put_button();
	TextView* get_connection_log();
};
