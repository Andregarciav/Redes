(unsigned)#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAX(x,y) (x>y ? x:y)

int main(int argc, char** argv) {
  int server_socket, client_sockets[100], bytes, v6only, selected;
  char buffer[128], client_ip[150];
  unsigned int size;
  int i, j, stack_max;
  fd_set stack;

  /* New struct ! */
  struct sockaddr_in6 server_addr, client_addr;

  /* Checking the arguments */
  if(argc != 2) {
  printf("\n[TCP Server] Argument error.\n\n");
  exit(1);
  }

  /* Creating TCP socket */
  server_socket = socket(AF_INET6, SOCK_STREAM, 0);  // AF_INET6 --> IPv6, SOCK_STREAM --> TCP
  if (server_socket == -1) {
  printf("\n[TCP Server] Socket error.\n\n");
  exit(1);
  }

  /* Socket now working with IPv4 and IPv6 */
  v6only = 0;
  if (setsockopt(server_socket, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only)) != 0) {
  printf("\n[TCP Server] Socket IPv6/IPv4 error.\n\n");
  exit(1);  
  }

  /* Configure settings in address struct */
  memset(&server_addr, 0, sizeof(server_addr));   // Cleaning the entire struct

  server_addr.sin6_family = AF_INET6;           // IPv6
  server_addr.sin6_addr = in6addr_any;          // Any IP address for the server
  server_addr.sin6_port = htons(atoi(argv[1])); // Gets the port number by the first argument


  /* Bind socket with address struct */
  if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
  printf("\n[TCP Server] Bind Error\n\n");
  exit(1);
  }

  /* Initialize size variable to be used later on */
  size = sizeof(struct sockaddr_in6);

  listen(server_socket, 5); // Transform the socket in an TCP listener, waiting for TCP connections.
  for(i = 0; i < 100; i++) client_sockets[i] = 0;

  // Initializing stack and putting the server socket.
  while(1) {

    // Making the stack
    FD_ZERO(&stack);
    client_sockets[0] = server_socket;
    stack_max = server_socket;
    for(i = 0; i < 100; i++) {
      if(client_sockets[i] > 0) {
        FD_SET(client_sockets[i], &stack);
        stack_max = MAX(client_sockets[i], stack_max);
      }
    }

    printf("[TCP Server] Waiting for something happen...\n\n");
    selected = select(stack_max+1, &stack, NULL, NULL, NULL);
    if(selected == -1) {
      perror("[TCP Server] Select error.\n");
    } else {
      // looping looking for the pending socket
      for (i = 0; i <= 100; i++) {
        if (FD_ISSET(client_sockets[i], &stack)) { // we got one!!
          if (client_sockets[i] == server_socket) {
            // new connection in master socket!
            for(j = 0; client_sockets[j] != 0; j++);
            client_sockets[j] = accept(client_sockets[i], NULL, NULL);
            if(client_sockets[j] == -1) {
              perror("[TCP Server] Accept Error.\n");
              client_sockets[j] = 0;
            } else {
              getpeername(client_sockets[j], (struct sockaddr *) &client_addr, &size);
              inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip, sizeof(client_ip));
              printf("[TCP Server] Client [%s:%d] Connected!\n\n", client_ip, ntohs(client_addr.sin6_port));
              // keep track of the max stack
              stack_max = MAX(client_sockets[j], stack_max);
            }
          } else {
            // client socket!
            memset(&buffer, 0, sizeof(buffer));
            bytes = read(client_sockets[i], buffer, 128);
            if(strcmp(buffer, "q") == 0 || bytes < 0) {
              printf("[TCP Server] Client closed.\n");
              close(client_sockets[i]);
              client_sockets[i] = 0;
            } else {
              printf("[TCP Server] Message received:\"%s\"\n", buffer);
              for(j = 0; (unsigned) j < strlen(buffer); j+=2) {
                buffer[j] = toupper(buffer[j]);
              }      
              printf("[TCP Server] Response: %s\n\n", buffer);
              bytes = send(client_sockets[i], buffer, sizeof(buffer), 0);
            }
          }
          break;
        }
      }
    }
  }
  close(server_socket);
  return 0;
}
