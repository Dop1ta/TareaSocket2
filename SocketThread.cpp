#include "SocketThread.hpp"

SocketThread::SocketThread(int clientSocket) : clientSocket(clientSocket) {}

SocketThread::~SocketThread()
{
}

void SocketThread::startThread()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dist(0, 1);

  char bufRecived[4096];

  int randomNum;
  string tablaClient = "";
  string tablaServ = "";
  string comTabla = "";
  string welcome_message = "";
  string todosLosTableros = "";
  string frase_str;
  string miTablaServerS = "";

  vector<string>
      turn = {"Tu comienzas el juego>", "Yo comienzo el juego >"};
  vector<vector<char> > miTablaClient = crearTabla();
  vector<vector<char> > miTablaServerDisparos(BORDERMAPS, vector<char>(BORDERMAPS, '-'));
  vector<vector<char> > miTablaServer = crearTabla();

  // Cadena que delimita el tablero inicial
  for (int i = 0; i < BORDERMAPS; i++)
  {
    for (int j = 0; j < BORDERMAPS; j++)
    {
      tablaClient += miTablaClient[i][j];
      tablaServ += miTablaServerDisparos[i][j];
      miTablaServerS += miTablaServer[i][j];
    }
  }

  memset(bufRecived, 0, 4096);

  randomNum = dist(gen);       // Genera un numero aleatorio para ver quien comienza el juego
  frase_str = turn[randomNum]; // Se obtiene el resultado del turno segun el numero generado

  // Mensaje de bienvenida para el cliente
  welcome_message += frase_str + tablaClient + tablaServ;

  send(clientSocket, welcome_message.c_str(), welcome_message.size() + 1, 0);

  int cont = 0;

  while (true)
  {

    memset(bufRecived, 0, 4096);

    int bytesReceived = recv(clientSocket, bufRecived, 4096, 0);
    if (bytesReceived == -1)
    {
      cerr << "Error in recv(). Quitting" << endl;
      break;
    }

    if (bytesReceived == 0)
    {
      cout << "Jugador desconectado [" << clientSocket << "]" << endl;
      break;
    }

    tablaClient = DisparoServidor(tablaClient);
    miTablaServerS = DisparoCliente(bufRecived, miTablaServerS);

    frase_str = "";
    welcome_message = "";
    tablaServ = "";

    for (int i = 0; i < BORDERMAPS; i++)
    {
      for (int j = 0; j < BORDERMAPS; j++)
      {
        if (miTablaServerS[i * BORDERMAPS + j] == 'X')
        {
          tablaServ += 'X';
          cont++;
        }
        else
        {
          tablaServ += '-';
        }
      }
    }

    frase_str = "!Le diste a algo!!";

    welcome_message += frase_str + tablaClient + tablaServ;
    send(clientSocket, welcome_message.c_str(), welcome_message.size() + 1, 0);

    if (cont == 22)
    {
      close(clientSocket);
    }
  }

  close(clientSocket); // Se cierra el socket del cliente
}
