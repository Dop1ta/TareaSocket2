#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>

#include "Utils.hpp"

using namespace std;

void tableroClienteServidor(const char *subCaneda, int comienzo, int tablero);

int main(int argc, char *argv[])
{

  if (argv[1] == NULL || argv[2] == NULL)
  {
    cout << "Porfavor ingrese el puerto y la IP" << endl;
    return 0;
  }

  // Creacion del socket del cliente
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    cerr << "Can't create a socket! Quitting" << endl;
    return -1;
  }

  int port = atoi(argv[2]);

  // Crea una estructura de indicaciones para el servidor al cual nos vamos a conectar
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port);

  inet_pton(AF_INET, argv[1], &hint.sin_addr);

  string userInput;

  while (true)
  {
    // Solicita al usuario la respuesta de iniciar o no el juego
    cout << "Empezar juego 1:si y 2:no > ";
    getline(cin, userInput);

    if (userInput == "1")
    {
      break;
    }
    else
    {
      return 0;
    }
  }

  // Hace la conexion al servidor en el socket
  int connectRes = connect(sock, (sockaddr *)&hint, sizeof(hint));
  if (connectRes == -1)
  {
    cerr << "No se puede conectar al server" << endl;
    return -2;
  }

  // Bucle While para enviar y recibir datos
  char buf[4096];
  ostringstream oss;

  do
  {

    // Envia el texto ingresado por el usuario al servidor
    int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
    if (sendRes == -1)
    {
      cerr << "No se pudo enviar al servidor" << endl;
      break;
    }

    // Espera la respuesta del servidor.
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1)
    {
      cerr << "Hubo un error con la respuesta del servidor" << endl;
    }
    else
    {

      cout << buf << endl
           << endl;

      // Procesa y muestra la respuesta del servidor
      if (buf[0] == 'T' || buf[0] == 'Y')
      {
        for (int i = 0; i < 22; i++)
        {
          if (buf[i] != '>')
          {
            cout << buf[i];
          }
          else
          {
            break;
          }
        }

        cout << endl;

        const char *subCaneda = buf + 22;

        cout << "TABLERO MIS EMBARCACIONES" << endl;
        tableroClienteServidor(subCaneda, 0, BORDERMAPS);
        cout << endl
             << "TABLERO DISPAROS"
             << endl;
        tableroClienteServidor(subCaneda, 14, BORDERMAPS * 2 - 1);
      }
      else
      {
        if (buf[0] == '!')
        {
          for (int i = 0; i < 30; i++)
          {
            if (buf[i] != '!')
            {
              cout << buf[i];
            }
            else
            {
              break;
            }
          }
        }

        cout << endl;

        const char *subCaneda = buf + 18;

        cout << "TABLERO MIS EMBARCACIONES" << endl;
        tableroClienteServidor(subCaneda, 0, BORDERMAPS);
        cout << endl
             << "TABLERO DISPAROS"
             << endl;
        tableroClienteServidor(subCaneda, 14, BORDERMAPS * 2 - 1);
      }
    }

    cout << endl
         << "Ingrese donde quiere disparar (ej: 1,3)> ";
    getline(cin, userInput);

  } while (true);

  // Cierre del socket
  close(sock);

  return 0;
}

// Se implementa una funcion para mostrar el tablero
void tableroClienteServidor(const char *subCaneda, int comienzo, int tablero)
{
  for (int i = comienzo; i < tablero; i++)
  {
    if (i - comienzo < 10)
    {
      cout << "0" << i - comienzo << " |  ";
    }
    else
    {
      cout << i - comienzo << " |  ";
    }

    for (int j = comienzo; j < tablero; j++)
    {
      // cout << subCaneda[(i - comienzo) * tablero + (j - comienzo)] << "  ";
      cout << subCaneda[i * BORDERMAPS + j] << "  ";
    }
    cout << endl;
  }

  cout << "_________________________________________________" << endl;
  cout << "     ";

  for (int i = 0; i < 15; i++)
  {
    if (i < 10)
    {
      cout << "0" << i << " ";
    }
    else
    {
      cout << i << " ";
    }
  }

  cout << endl;
}
