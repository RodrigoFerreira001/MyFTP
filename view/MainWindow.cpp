#include "MainWindow.hpp"

MainWindow::MainWindow(){
	//Widgets para construção de tela
	HeaderBar* header = new HeaderBar;
	Label* user_label = new Label("Usuário");
	Label* passwd_label = new Label("Senha");
	Separator* login_separator = new Separator;
	Separator* local_separator = new Separator;
	Separator* remote_separator = new Separator;
	Separator* log_separator = new Separator;
	Box* login_box = new Box(ORIENTATION_HORIZONTAL);
	Box* file_box = new Box(ORIENTATION_HORIZONTAL);
	Box* local_box = new Box(ORIENTATION_VERTICAL);
	Box* remote_box = new Box(ORIENTATION_VERTICAL);
	Box* local_menu_box = new Box(ORIENTATION_HORIZONTAL);
	Box* remote_menu_box = new Box(ORIENTATION_HORIZONTAL);
	Box* local_frame_box = new Box(ORIENTATION_VERTICAL);
	Box* remote_frame_box = new Box(ORIENTATION_VERTICAL);
	Box* action_box = new Box(ORIENTATION_VERTICAL);
	Box* action_box_up = new Box(ORIENTATION_VERTICAL);
	Box* action_box_down  = new Box(ORIENTATION_VERTICAL);
	ScrolledWindow* local_scroll = new ScrolledWindow;
	ScrolledWindow* remote_scroll = new ScrolledWindow;
	ScrolledWindow* log_scroll = new ScrolledWindow;
	Frame* local_frame = new Frame("Arquivos Locais");
	Frame* remote_frame = new Frame("Arquivos Remotos");

	//Widgets manipuláveis
	//Botão de configuração
	config_button = new Button;
	config_button->set_tooltip_text("Configurar");
	Image* config_button_img = new Image;
	config_button_img->set_from_icon_name("application-menu-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	config_button->set_image(*config_button_img);

	user_entry = new Entry;

	passwd_entry = new Entry;
	passwd_entry->set_visibility(false);

	connect_disconnect = new ToggleButton("Conectar");
	connect_disconnect->set_size_request(150, -1);
	connect_disconnect->set_tooltip_text("Conectar/Disconectar");

	local_refresh = new Button;
	local_refresh->set_tooltip_text("Recarregar Conteúdo Local");
	Image* local_refresh_img = new Image;
	local_refresh_img->set_from_icon_name("system-restart-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	local_refresh->set_image(*local_refresh_img);

	local_mkdir = new Button;
	local_mkdir->set_tooltip_text("Criar Novo Diretório Local");
	Image* local_mkdir_img = new Image;
	local_mkdir_img->set_from_icon_name("folder-new-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	local_mkdir->set_image(*local_mkdir_img);

	local_rm = new Button;
	local_rm->set_tooltip_text("Remover Item Local Selecionado");
	Image* local_rm_img = new Image;
	local_rm_img->set_from_icon_name("edit-delete-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	local_rm->set_image(*local_rm_img);

	remote_refresh = new Button;
	remote_refresh->set_tooltip_text("Recarregar Conteúdo Remoto");
	Image* remote_refresh_img = new Image;
	remote_refresh_img->set_from_icon_name("system-restart-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	remote_refresh->set_image(*remote_refresh_img);


	remote_mkdir = new Button;
	remote_mkdir->set_tooltip_text("Criar Novo Diretório Remoto");
	Image* remote_mkdir_img = new Image;
	remote_mkdir_img->set_from_icon_name("folder-new-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	remote_mkdir->set_image(*remote_mkdir_img);


	remote_rm = new Button;
	remote_rm->set_tooltip_text("Remover Item Remoto Selecionado");
	Image* remote_rm_img = new Image;
	remote_rm_img->set_from_icon_name("edit-delete-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	remote_rm->set_image(*remote_rm_img);

	local_list = new FileList;
	remote_list = new FileList;

	get_button = new Button;
	get_button->set_tooltip_text("Obter Arquivo Selecionado");
	Image* get_button_img = new Image;
	get_button_img->set_from_icon_name("go-next-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	get_button->set_image(*get_button_img);

	put_button = new Button;
	put_button->set_tooltip_text("Enviar Arquivo Selecionado");
	Image* put_button_img = new Image;
	put_button_img->set_from_icon_name("go-previous-symbolic", IconSize(GTK_ICON_SIZE_BUTTON));
	put_button->set_image(*put_button_img);

	connection_log = new TextView;
	connection_log->set_editable(false);

	//Configura o HeaderBar
	header->set_title("MainWindow");
	header->set_show_close_button(true);
	header->pack_start(*config_button);
	header->show_all_children();

	//Define a headerbar
	set_titlebar(*header);

	//Add main_box na janela principal
	Box* main_box = new Box(ORIENTATION_VERTICAL);
	main_box->set_margin_top(18);
	main_box->set_margin_right(18);
	main_box->set_margin_bottom(18);
	main_box->set_margin_left(18);
	add(*main_box);

	//Add login_box to main_box
	main_box->pack_start(*login_box, true, true);

	//Fill login_box
	user_label->set_margin_right(6);
	user_label->set_margin_bottom(12);
	login_box->pack_start(*user_label, false, false);

	user_entry->set_margin_right(12);
	user_entry->set_margin_bottom(12);
	login_box->pack_start(*user_entry, false, false);

	passwd_label->set_margin_right(6);
	passwd_label->set_margin_bottom(12);
	login_box->pack_start(*passwd_label, false, false);

	passwd_entry->set_margin_right(12);
	passwd_entry->set_margin_bottom(12);
	login_box->pack_start(*passwd_entry, false, false);

	connect_disconnect->set_margin_bottom(12);
	login_box->pack_end(*connect_disconnect, true, true);

	//Add main Separator
	main_box->pack_start(*login_separator, true, true);

	//Add file context box
	main_box->pack_start(*file_box, true, true);

	//Fill file box
	file_box->set_margin_top(12);
	local_box->set_margin_right(12);
	file_box->pack_start(*local_box, true, true);

	action_box->set_margin_right(12);
	file_box->pack_start(*action_box, false, false);
	file_box->pack_start(*remote_box, true, true);

	//Fill local box
	local_box->pack_start(*local_frame, true, true);
	local_frame->add(*local_frame_box);
	local_menu_box->set_margin_bottom(6);
	local_menu_box->set_margin_left(6);
	local_frame_box->pack_start(*local_menu_box, true, false);
	local_menu_box->pack_start(*local_refresh, false, false);
	local_menu_box->pack_start(*local_mkdir, false, false);
	local_menu_box->pack_start(*local_rm, false, false);
	local_refresh->set_margin_right(6);
	local_mkdir->set_margin_right(6);
	local_rm->set_margin_right(6);
	local_frame_box->pack_start(*local_separator,true,true);
	local_frame_box->pack_start(*local_scroll, true, true);
	local_scroll->add(*local_list);
	local_scroll->set_size_request(-1, 200);

	//Fill action box
	action_box->pack_start(*action_box_up, true, true);
	action_box->pack_start(*put_button, false, false);
	action_box->pack_start(*get_button, false, false);
	action_box->pack_start(*action_box_down, true, true);

	//Fill remote box
	remote_box->pack_start(*remote_frame, true, true);
	remote_frame->add(*remote_frame_box);
	remote_menu_box->set_margin_bottom(6);
	remote_menu_box->set_margin_left(6);
	remote_frame_box->pack_start(*remote_menu_box, true, false);
	remote_menu_box->pack_start(*remote_refresh, false, false);
	remote_menu_box->pack_start(*remote_mkdir, false, false);
	remote_menu_box->pack_start(*remote_rm, false, false);
	remote_refresh->set_margin_right(6);
	remote_mkdir->set_margin_right(6);
	remote_rm->set_margin_right(6);
	remote_frame_box->pack_start(*remote_separator,true,true);
	remote_frame_box->pack_start(*remote_scroll, true, true);
	remote_scroll->add(*remote_list);
	remote_scroll->set_size_request(-1, 200);

	main_box->pack_start(*log_separator, true, true);
	log_separator->set_margin_top(12);
	log_separator->set_margin_bottom(12);

	main_box->pack_start(*log_scroll, true, true);
	log_scroll->add(*connection_log);
	log_scroll->set_size_request(-1, 100);

	set_resizable(false);
	show_all_children();
}

MainWindow::~MainWindow(){
	delete config_button;
	delete user_entry;
	delete passwd_entry;
	delete connect_disconnect;
	delete local_refresh;
	delete local_mkdir;
	delete local_rm;
	delete remote_refresh;
	delete remote_mkdir;
	delete remote_rm;
	delete local_list;
	delete remote_list;
	delete get_button;
	delete put_button;
	delete connection_log;
}

Button* MainWindow::get_config_button(){
	return config_button;
}

Entry* MainWindow::get_user_entry(){
	return user_entry;
}

Entry* MainWindow::get_passwd_entry(){
	return passwd_entry;
}

ToggleButton* MainWindow::get_connect_disconnect(){
	return connect_disconnect;
}

Button* MainWindow::get_local_refresh(){
	return local_refresh;
}

Button* MainWindow::get_local_mkdir(){
	return local_mkdir;
}

Button* MainWindow::get_local_rm(){
	return local_rm;
}

Button* MainWindow::get_remote_refresh(){
	return remote_refresh;
}

Button* MainWindow::get_remote_mkdir(){
	return remote_mkdir;
}

Button* MainWindow::get_remote_rm(){
	return remote_rm;
}

FileList* MainWindow::get_local_list(){
	return local_list;
}

FileList* MainWindow::get_remote_list(){
	return remote_list;
}

Button* MainWindow::get_get_button(){
	return get_button;
}

Button* MainWindow::get_put_button(){
	return put_button;
}

TextView* MainWindow::get_connection_log(){
	return connection_log;
}
