/*
Copyright (c) 2017 Gabriel de Biasi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char** argv) {
  int clientSocket, nBytes;
  char buffer[128];
  struct sockaddr_in serverAddr;
  socklen_t size;

  /* Checking the arguments */
  if(argc != 3) {
    printf("\n[TCP Client] Argument error.\n\n");
    exit(1);
  }

  /* Create TCP socket */
  clientSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET --> IPv4, SOCK_STREAM --> TCP

  if (clientSocket == -1) {
      printf("\n[TCP Client] Socket error.\n\n");
      exit(1);
  }

  /* Configure settings in address struct */
  serverAddr.sin_family = AF_INET;                 // IPv4
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]); // Get the IP address by the argument 
  serverAddr.sin_port = htons(atoi(argv[2]));      // Get the port by the argument

  memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // for compatibility

  /* Initialize size variable to be used later on */
  size = sizeof(struct sockaddr_in);

  printf("[TCP Client] Trying to connect to the server...\n");
  // Trying to connect in the TCP Server
  if (connect(clientSocket, (struct sockaddr*) &serverAddr, size) < 0) {
      printf("\n[TCP Client] Connection Error.\n\n");
      exit(1);
  }

  printf("[TCP Client] CONNECTED! Welcome to the Sum Calculator.\n");
  while(1) {
    printf("[TCP Client] Enter the first number or zero to quit: ");
    fgets(buffer, 128, stdin);
    nBytes = strlen(buffer)+1;

    // Sending data, without specifying a destination,
    // because the TCP connection is already made.
    write(clientSocket, buffer, nBytes);

    if(atoi(buffer) == 0) break;

    printf("\n[TCP Client] Enter the second number: ");
    fgets(buffer, 128, stdin);
    nBytes = strlen(buffer)+1;
    send(clientSocket, buffer, nBytes, 0);

    // Receiving data, without specifying a destination, 
    // because the TCP connection is already made.
    nBytes = recv(clientSocket, buffer, 128, 0);
    printf("\n[TCP Client] Answer received: %d\n\n", atoi(buffer));
  }
  printf("\n[TCP Client] Quitting...\n");
  close(clientSocket); // Releasing the socket.
  return 0;
}
