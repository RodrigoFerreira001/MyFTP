g++ -std=c++11 model/Directory.cpp model/FileBuffer.cpp model/Socket.cpp model/FTPClient.cpp\
	view/Item.cpp view/ConfigWindow.cpp view/FileList.cpp view/MainWindow.cpp\
	control/MainWindowControl.cpp\
	MyFTP.cpp  -g -o MyFTP `pkg-config --cflags --libs gtkmm-3.0`

g++ -std=c++11 model/Directory.cpp model/FileBuffer.cpp model/Socket.cpp model/FTPServer.cpp\
	model/MyFTPServer.cpp -o MyFTPServer

mv MyFTPServer ../
