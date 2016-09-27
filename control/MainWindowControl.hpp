#include "../model/FTPClient.hpp"
#include "../view/MainWindow.hpp"
#include <string>

class MainWindowControl{
private:
	FTPClient* ftp_client;
	MainWindow* main_window;
	void login_logout();
	bool lls(GdkEventButton* event);
	bool ls(GdkEventButton* event);
	void close_window();

public:
	MainWindowControl(FTPClient* ftp_client, MainWindow* main_window);
	void connect();
};
