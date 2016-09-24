#pragma once

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
using namespace std;
using namespace Gtk;

class Item : public Box{
private:
	Label* name;
	Image* icon;
	string* type;

public:
	Item(string name, string type);
	~Item();

	void set_name(string name);
	Label* get_name();

	Image* get_icon();

	void set_type(string type);
	string get_type();

};
