#ifndef SHOTS_HPP
#define SHOTS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include "Utils.hpp"

using namespace std;

string realizarDisparos(char bufRecived[4096], string miTablaClient, string miTablaServer);
string DisparoServidor(string tablaClient);
string DisparoCliente(char bufRecived[4096], string miTablaServerS);

#endif // SHOTS_HPP
