#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <pthread.h>
#include <stdlib.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

#include "Utils.hpp"
#include "Shots.hpp"

using namespace std;

class SocketThread
{
public:
  SocketThread(int);
  ~SocketThread();

  void startThread();

private:
  int clientSocket;
};