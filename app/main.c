#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "server.h"


int main()
{
  int aux;
  novo *msg=calloc( 1 , sizeof(novo));
  scanf("%c %s %d %s %[^\n]s" , &msg->tipo , msg->login , &msg->senha , msg->arquivo , msg->conteudo);
  msg->tipo = toupper(msg->tipo);
  if (msg->tipo == 'N')
  {
    aux = verificaUsuario(msg->login, msg->senha);
        if (aux == 1)
    printf("%d\n", aux);
  }


  printf("%c %s %d %s %s\n", msg->tipo , msg->login , msg->senha , msg->arquivo , msg->conteudo);
  free(msg);
  return 0;
}
