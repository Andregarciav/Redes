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
#include <netinet/in.h>
#include <string.h>

int main(int argc, char** argv) {
  int clientSocket, nBytes;
  socklen_t size;
  char buffer[1024];
  struct sockaddr_in serverAddr;

  /* Checking the Arguments */
  if(argc != 3) {
    printf("\n[CLIENT] Argument error.\n\n");
    exit(1);
  }

  /* Create UDP socket */
  clientSocket = socket(AF_INET, SOCK_DGRAM, 0); // AF_INET --> IPv4, SOCK_DGRAM --> UDP

  if (clientSocket == -1) {
      printf("\n[CLIENT] Socket error.\n\n");
      exit(1);
  }

  /* Configure settings in address struct */
  serverAddr.sin_family = AF_INET;                 // IPv4
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]); // Get the IP address by the argument 
  serverAddr.sin_port = htons(atoi(argv[2]));      // Get the port by the argument

  memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // for compatibility

  size = sizeof(struct sockaddr_in);
  while(1) {
    printf("[CLIENT] Type a sentence to send to server:\n");
    /* Reads the sentence from the keyboard */
    fgets(buffer, 1024, stdin);
    printf("[CLIENT] Sending to server...\n");

    nBytes = strlen(buffer) + 1;
    
    /* Send message to server */
	
    sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *) &serverAddr, size);

    /* Receive message from server */
    nBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);

    printf("[CLIENT] Received from server: %s\n\n",buffer);

  }

  return 0;
}
