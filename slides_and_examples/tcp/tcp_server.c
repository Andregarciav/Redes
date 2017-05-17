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
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int serverSocket, clientSocket, num1, num2, nBytes;
  char buffer[128];

  struct sockaddr_in serverAddr, clientAddr;
  socklen_t size;

  /* Checking the arguments */
  if(argc != 2) {
    printf("\n[TCP Server] Argument error.\n\n");
    exit(1);
  }

  /* Creating TCP socket */
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);  // AF_INET --> IPv4, SOCK_STREAM --> TCP

  if (serverSocket == -1) {
      printf("\n[TCP Server] Socket error.\n\n");
      exit(1);
  }

  /* Configure settings in address struct */
  serverAddr.sin_family = AF_INET;            // IPv4
  serverAddr.sin_addr.s_addr = INADDR_ANY;    // Any IP address for the server
  serverAddr.sin_port = htons(atoi(argv[1])); // Gets the port number by the first argument

  memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // For compatibility

  /* Bind socket with address struct */
  if( bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
    printf("\n[TCP Server] Bind Error\n\n");
    exit(1);
  }

  /* Initialize size variable to be used later on */
  size = sizeof(struct sockaddr_in);

  listen(serverSocket, 5); // Transform the socket in an TCP listener, waiting for TCP connections.

  while(1) {
    // If a new client try to connect, ANOTHER socket is created just for it (clientSocket).
    printf("[TCP Server] Waiting for clients...\n\n");

    clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &size); // Blocks the execution waiting por clients
    if (clientSocket < 0) { // Test the new socket.
        perror("[TCP Server] Connection Error.\n");
        exit(1);
    }

    printf("[TCP Server] Client [%s:%d] Connected!\n\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    while(1) {
        nBytes = read(clientSocket, buffer, 128); // Receiving first number
        num1 = atoi(buffer);
        if(nBytes < 0 || num1 == 0) break;

        nBytes = read(clientSocket, buffer, 128); // Receiving second number
        num2 = atoi(buffer);
	if(nBytes < 0) break;

        sprintf(buffer, "%d", num1+num2); // Calculates the sum
        nBytes = write(clientSocket, buffer, 128); // Sending back
        if(nBytes < 0) break;
    }

    printf("[TCP Server] Client [%s:%d] Connection Closed.\n\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    close(clientSocket); // Releasing the socket for the client
  }
  close(serverSocket); // Releasing the socket of the server
  return 0;
}
