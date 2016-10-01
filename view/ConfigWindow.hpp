#pragma once

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
using namespace Gtk;

class ConfigWindow : public Dialog{
private:
	Entry* ip_entry;
	Entry* port_entry;
	Button* cancel;
	Button* save;

public:
	ConfigWindow();
	~ConfigWindow();
	Entry* get_ip_entry();
	Entry* get_port_entry();
	Button* get_cancel();
	Button* get_save();
};
