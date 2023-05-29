programa: all
	
all: Client.o Server.o SocketThread.o Utils.o Shots.o
	g++ -o client Client.o Utils.o
	g++ -o server Server.o Utils.o SocketThread.o Shots.o

client.o: Client.cpp
	g++ -c Client.cpp

server.o: Server.cpp 
	g++ -c Server.cpp

SocketThread.o: SocketThread.cpp
	g++ -c SocketThread.cpp

Utils.o: Utils.cpp
	g++ -c Utils.cpp

Shots.o: Shots.cpp
	g++ -c Shots.cpp

clean:
	rm -f server client Server.o Utils.o SocketThread.o Shots.o Client.o