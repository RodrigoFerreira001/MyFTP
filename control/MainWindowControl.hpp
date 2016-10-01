#include "../model/FTPClient.hpp"
#include "../view/MainWindow.hpp"
#include "../view/ConfigWindow.hpp"
#include <string>
class MainWindowControl{
private:
	FTPClient* ftp_client;
	MainWindow* main_window;
	ConfigWindow* cfg_window;

	void login_logout();
	bool lls(GdkEventButton* event);
	bool ls(GdkEventButton* event);
	void close_config_window();
	void config();
	void save_config();
	void close_window();
	void local_refresh();
	void remote_refresh();
	void put();
	void get();

public:
	MainWindowControl(FTPClient* ftp_client, MainWindow* main_window, ConfigWindow* cfg_window);
	~MainWindowControl();
	void connect();
};
