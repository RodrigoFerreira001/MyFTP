#include "ConfigWindow.hpp"

ConfigWindow::ConfigWindow(){
	ip_entry = new Entry;
	port_entry = new Entry;
	cancel = new Button("Cancelar");
	save = new Button("Salvar");

	Label* ip_label = new Label("IP");
	Label* port_label = new Label("Porta");
	Box* main_box = new Box(ORIENTATION_VERTICAL);
	Box* entry_box = new Box(ORIENTATION_VERTICAL);
	Box* action_box = new Box(ORIENTATION_HORIZONTAL);

	main_box->set_margin_top(18);
	main_box->set_margin_right(18);
	main_box->set_margin_bottom(18);
	main_box->set_margin_left(18);

	main_box->pack_start(*entry_box, true, true);
	main_box->pack_start(*action_box, true, true);

	ip_label->set_margin_bottom(6);
	ip_entry->set_margin_bottom(12);

	port_label->set_margin_bottom(6);

	entry_box->pack_start(*ip_label,true,false);
	entry_box->pack_start(*ip_entry,false,false);
	entry_box->pack_start(*port_label,false,false);
	entry_box->pack_start(*port_entry,true,false);

	action_box->set_margin_top(12);
	save->set_margin_right(6);
	action_box->pack_end(*cancel, true, true);
	action_box->pack_end(*save, true, true);

	get_content_area()->pack_start(*main_box, true, true);

	HeaderBar* hb = new HeaderBar();
	hb->set_title("Configurar");
	hb->set_show_close_button(false);
	set_titlebar(*hb);

	set_resizable(false);
	show_all_children();
}

ConfigWindow::~ConfigWindow(){
	delete ip_entry;
	delete port_entry;
	delete cancel;
	delete save;
}

Entry* ConfigWindow::get_ip_entry(){
	return ip_entry;
}

Entry* ConfigWindow::get_port_entry(){
	return port_entry;
}

Button* ConfigWindow::get_cancel(){
	return cancel;
}

Button* ConfigWindow::get_save(){
	return save;
}
