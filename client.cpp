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

int main(int argc, char *argv[])
{

  if (argv[1] == NULL || argv[2] == NULL)
  {
    cout << "Porfavor ingrese el puerto y la IP" << endl;
    return 0;
  }

  // Create a socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    cerr << "Can't create a socket! Quitting" << endl;
    return -1;
  }

  int port = atoi(argv[2]);

  // Create a hint structure for the server we're connecting with
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port);

  // inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr); // Use the IP address of the server here
  inet_pton(AF_INET, argv[1], &hint.sin_addr); // Use the IP address of the server here

  // Connect to the server on the socket
  int connectRes = connect(sock, (sockaddr *)&hint, sizeof(hint));
  if (connectRes == -1)
  {
    cerr << "No se puede conectar al server" << endl;
    return -2;
  }

  // While loop to send and receive data
  char buf[4096];
  string userInput;

  do
  {
    // Prompt the user for some text
    cout << "Ingrese coordeandas donde quiere disparar > ";
    getline(cin, userInput);

    // Send the text
    int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
    if (sendRes == -1)
    {
      cerr << "Could not send to server! Quitting" << endl;
      break;
    }

    // Wait for response
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1)
    {
      cerr << "There was an error getting response from server" << endl;
    }
    else
    {
      // Display response
      cout << "SERVER> " << string(buf, bytesReceived) << endl;
    }

  } while (true);

  // Close the socket
  close(sock);

  return 0;
}
