#include <gtkmm.h>
#include "MainWindow.hpp"
using namespace Gtk;


int main(int argc, char** argv){

	Main kit(argc, argv);
	MainWindow mftp;

	kit.run(mftp);
	return 0;
}
