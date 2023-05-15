#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

void socketS(int port);

int main(int argc, char *argv[])
{

  if (argv[1] == NULL)
  {
    cout << "Porfavor ingrese el puerto" << endl;
    return 0;
  }

  int port = atoi(argv[1]);

  socketS(port);

  return 0;
}

void socketS(int port)
{

  cout << "port" << port << endl;

  // Creacion del socket
  int listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening == -1)
  {
    cerr << "No se puede crear el socket" << endl;
    exit(-1);
  }

  // Bind the ip address and port to a socket
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port); // Puerto
  inet_pton(AF_INET, "192.168.0.1", &hint.sin_addr);

  bind(listening, (sockaddr *)&hint, sizeof(hint));

  // Tell Winsock the socket is for listening
  listen(listening, SOMAXCONN);

  // Wait for a connection
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);

  int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);

  char host[NI_MAXHOST];    // Client's remote name
  char service[NI_MAXSERV]; // Service (i.e. port) the client is connect on

  memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);

  if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
  {
    cout << host << " connected on port " << service << endl;
  }
  else
  {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    cout << host << " connected on port " << ntohs(client.sin_port) << endl;
  }

  // Close listening socket
  close(listening);

  // While loop: accept and echo message back to client
  char buf[4096];

  while (true)
  {
    memset(buf, 0, 4096);

    // Wait for client to send data
    int bytesReceived = recv(clientSocket, buf, 4096, 0);
    if (bytesReceived == -1)
    {
      cerr << "Error in recv(). Quitting" << endl;
      break;
    }

    if (bytesReceived == 0)
    {
      cout << "Client disconnected " << endl;
      break;
    }

    cout << string(buf, 0, bytesReceived) << endl;

    send(clientSocket, buf, bytesReceived + 1, 0);
  }

  // Close the socket
  close(clientSocket);
}