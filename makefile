m = ../model/
v = ../view/
c = ../control/

all: MyFTP

MyFTP: FTPClient.o MainWindow.o MainWindowControl.o MyFTP.o

FTPClient.o: Directory.o FileBuffer.o Socket.o
