#Compila primeiro model
cd model/
	g++ -std=c++11 -o Directory.o -c Directory.cpp
	g++ -std=c++11 -o FileBuffer.o -c FileBuffer.cpp
	g++ -std=c++11 -o Socket.o -c Socket.cpp
	g++ -std=c++11 -o FTPClient.o Socket.o FileBuffer.o -c FTPClient.cpp
