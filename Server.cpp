#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>

#include "SocketThread.hpp"

using namespace std;

void *startThread(void *arg)
{
  SocketThread *socketThread = static_cast<SocketThread *>(arg);
  socketThread->startThread();
  delete socketThread;
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  // Verifica si se ingresó el puerto como argumento
  if (argv[1] == NULL)
  {
    cout << "Porfavor ingrese el puerto" << endl;
    return 0;
  }

  int listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening == -1)
  {
    cerr << "No se puede crear el socket" << endl;
    exit(-1);
  }
  // Configura la dirección y puerto del socket
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(atoi(argv[1]));
  inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
  // Vincula el socket a la direccion y puerto
  bind(listening, (sockaddr *)&hint, sizeof(hint));

  listen(listening, SOMAXCONN);

  sockaddr_in client;
  socklen_t clientSize = sizeof(client);

  while (true)
  {
    // Acepta la conexion que entra
    int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
    if (clientSocket == -1)
    {
      cerr << "Error en accept(). Continuando..." << endl;
      continue;
    }

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    // Obtiene informacion del cliente
    if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
      cout << "Juego nuevo en el puerto [" << service << "]" << endl;
    }
    else
    {
      inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
      cout << "Juego nuevo en el puerto " << ntohs(client.sin_port) << endl;
    }

    SocketThread *socketThread = new SocketThread(clientSocket);
    pthread_t tid;
    pthread_create(&tid, NULL, startThread, static_cast<void *>(socketThread));
    pthread_detach(tid);
  }

  return 0;
}
