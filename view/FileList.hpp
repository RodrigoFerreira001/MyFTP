#pragma once

#include "Item.hpp"
#include <gtkmm/listbox.h>
#include <vector>
#include <string>
using namespace Gtk;

class FileList : public ListBox{
public:
	void insert(vector<string>* dir);
	void clear();
};
