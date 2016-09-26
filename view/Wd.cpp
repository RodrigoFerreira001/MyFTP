#include "MainWindow.hpp"
#include <gtkmm/application.h>
using namespace Gtk;

int main(int argc, char**argv){
	auto application = Application::create(argc, argv, "org.rodrigo.window");
	MainWindow mw;
	return application->run(mw);
}
