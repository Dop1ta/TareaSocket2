#include "Shots.hpp"

using namespace std;

string realizarDisparos(char bufRecived[4096], const vector<vector<char> > &miTablaClient, const vector<vector<char> > &miTablaServer)
{
  string finaMessage = "";
  string tablaClient = "";
  string tablaServ = "";
  string message = "";
  string str = "";
  int x, y, xC, yC, cont = 0;

  // // Generar una semilla única para los números aleatorios
  // srand(time(nullptr));
  // // Generar coordenadas aleatorias para el disparo en la tabla del cliente
  // x = rand() % BORDERMAPS;
  // y = rand() % BORDERMAPS;

  for (int i = 0; bufRecived[i] != '\0'; i++)
  {
    char c = bufRecived[i];
    // Realizar operaciones con el char en la posición i
    str += c;
  }

  size_t commaPos = str.find(',');
  if (commaPos != string::npos) // Si se encuentra una coma en la cadena
  {
    string str1 = str.substr(0, commaPos);  // Obtiene la primera parte antes de la coma
    string str2 = str.substr(commaPos + 1); // Obtiene la segunda parte después de la coma

    // Convierte las partes de la cadena encontradas en un entero
    xC = stoi(str1);
    yC = stoi(str2);
  }

  for (int i = 0; i < BORDERMAPS; i++)
  {
    for (int j = 0; j < BORDERMAPS; j++)
    {
      if (i == xC && j == yC)
      {
        if (miTablaClient[i][j] != '-')
        {
          message = "!Le diste a algo!!";
          cont++;
        }
        else
        {
          message = "!Sigue intentando!";
        }
        tablaServ += "X";
      }
      else
      {
        tablaServ += miTablaServer[i][j];
      }

      if (i == x && j == y)
      {
        tablaClient += "X";
      }
      else
      {
        tablaClient += miTablaClient[i][j];
      }
    }
  }

  finaMessage = message + tablaClient + tablaServ;

  return finaMessage;
}

string DisparoServidor(string miTablaServerS)
{
  int x, y, cont = 0;
  // Generar una semilla única para los números aleatorios
  srand(time(nullptr));
  // Generar coordenadas aleatorias para el disparo en la tabla del cliente
  x = rand() % BORDERMAPS;
  y = rand() % BORDERMAPS;

  cout << "Juego inicia disparos el cliente." << endl;

  for (int i = 0; i < BORDERMAPS; i++)
  {
    for (int j = 0; j < BORDERMAPS; j++)
    {
      if (i == x && j == y)
      {
        if (miTablaServerS[i * BORDERMAPS + j] == '-')
        {
          cont++;
        }
        else
        {
          miTablaServerS[i * BORDERMAPS + j] = 'X';
        }
      }
    }
  }

  // Retornar el string modificado
  return miTablaServerS;
}

string DisparoCliente(char bufRecived[4096], string miTablaServerS)
{

  cout << "Juego inicia disparos el servidor." << endl;
  int xC, yC, cont = 0;

  string str; // Variable para almacenar la cadena convertida

  for (int i = 0; bufRecived[i] != '\0'; i++)
  {
    char c = bufRecived[i];
    // Realizar operaciones con el char en la posición i
    str += c;
  }

  size_t commaPos = str.find(',');
  if (commaPos != string::npos) // Si se encuentra una coma en la cadena
  {
    string str1 = str.substr(0, commaPos);  // Obtiene la primera parte antes de la coma
    string str2 = str.substr(commaPos + 1); // Obtiene la segunda parte después de la coma

    // Convierte las partes de la cadena encontradas en un entero
    xC = stoi(str1);
    yC = stoi(str2);
  }

  // Modificar el valor en la coordenada (xC, yC)
  for (int i = 0; i < BORDERMAPS; i++)
  {
    for (int j = 0; j < BORDERMAPS; j++)
    {
      if (i == xC && j == yC)
      {
        if (miTablaServerS[i * BORDERMAPS + j] == '-')
        {
          cont++;
        }
        else
        {
          miTablaServerS[i * BORDERMAPS + j] = 'X';
        }
      }
    }
  }

  // Retornar el string modificado
  return miTablaServerS;
}
