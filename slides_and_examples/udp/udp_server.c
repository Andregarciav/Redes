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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int i, udpSocket, nBytes;
  socklen_t size;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;

  /* Checking the arguments */
  if(argc != 2) {
    printf("\n[SERVER] Argument error.\n\n");
    exit(1);
  }

  /* Creating UDP socket */
  udpSocket = socket(AF_INET, SOCK_DGRAM, 0);  // AF_INET--> IPv4, SOCK_DGRAM --> UDP

  if (udpSocket == -1) {
      printf("\n[SERVER] Socket error.\n\n");
      exit(1);
  }

  /* Configure settings in address struct */
  serverAddr.sin_family = AF_INET;            // IPv4
  serverAddr.sin_addr.s_addr = INADDR_ANY;    // Any IP address for the server
  serverAddr.sin_port = htons(atoi(argv[1])); // Gets the port number by the first argument

  memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // For compatibility

  /* Bind socket with address struct */
  if( bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
    printf("\n[SERVER] Bind Error\n\n");
    exit(1);
  }
  
  size = sizeof(struct sockaddr_in);
  while(1) {
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on clientAddr variable */
    printf("[SERVER] Waiting for messages...\n\n");
    nBytes = recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *) &clientAddr, &size);

    printf("[SERVER] Message received from:\nIP: \"%s:%d\"\nMessage: %sSending back...\n\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buffer);    

    /* Convert message received to uppercase */
    for(i=0; i < nBytes-1; i++) buffer[i] = toupper(buffer[i]);

    /* Send uppercase message back to client, using serverStorage as the address */
    sendto(udpSocket, buffer, nBytes, 0, (struct sockaddr *) &clientAddr, size);
  }

  return 0;
}
