#include "model/FTPClient.hpp"
#include "view/MainWindow.hpp"
#include "control/MainWindowControl.hpp"
#include "gtkmm/application.h"

int main(int argc, char** argv){
	auto application = Application::create(argc, argv, "org.rodrigo.myftp");

	FTPClient* ftp_client = new FTPClient("127.0.0.1", 8888, 1024);
	MainWindow* main_window = new MainWindow;
	MainWindowControl* main_control = new MainWindowControl(ftp_client, main_window);

	main_control->connect();

	return application->run(*main_window);
}
