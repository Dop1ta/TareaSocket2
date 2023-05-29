#include "Utils.hpp"

// Funcion que retorna un numero segun el nombre del barco
int getNumeroBarcos(const string &nombre)
{
  if (nombre == "Portaaviones")
  {
    return 1;
  }
  else if (nombre == "Buque")
  {
    return 2;
  }
  else if (nombre == "Submarino")
  {
    return 2;
  }
  else if (nombre == "Lancha")
  {
    return 3;
  }

  return 0;
}

vector<vector<char> > crearTabla()
{
  vector<vector<char> > tabla(BORDERMAPS, vector<char>(BORDERMAPS, '-'));

  // Estructura para almacenar la información de los barcos
  struct Barco
  {
    string nombre;
    int tamano;
  };

  // Vector de barcos
  vector<Barco> barcos = {{"Portaaviones", 5}, {"Buque", 4}, {"Submarino", 3}, {"Lancha", 1}};

  // Contadores para los barcos asignados
  int portaavionesAsignados = 0;
  int buquesAsignados = 0;
  int submarinosAsignados = 0;
  int lanchasAsignadas = 0;

  // Asignaciones aleatorias de los barcos en la tabla
  srand(time(0)); // Inicializar la semilla aleatoria

  for (const Barco &barco : barcos)
  {
    int cantidadAsignada = 0;

    while (cantidadAsignada < getNumeroBarcos(barco.nombre))
    {
      int fila = rand() % BORDERMAPS;
      int columna = rand() % BORDERMAPS;
      bool solapado = false;

      // Verificar si el barco se solapa con otra unidad en la tabla
      for (int i = 0; i < barco.tamano; i++)
      {
        if (columna + i >= BORDERMAPS || tabla[fila][columna + i] != '-')
        {
          solapado = true;
          break;
        }
      }

      if (!solapado)
      {
        // Asignar el barco en la tabla
        for (int i = 0; i < barco.tamano; i++)
        {
          tabla[fila][columna + i] = barco.nombre[0]; // Usar la primera letra del nombre del barco como identificador
        }

        cantidadAsignada++;
      }
    }
  }

  return tabla;
}