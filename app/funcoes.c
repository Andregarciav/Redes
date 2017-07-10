#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "server.h"

int verificaUsuario(char *usuario , int pass)
{
  FILE *arq;
  char buffer[MAX];
  char *nome;
  int senha;
  arq = fopen("controle.txt" , "r");
  fgets ( buffer , MAX , arq);
  while (!feof)
  {
  nome = strtok(buffer,",");
  senha = atoi(strtok(NULL,","));
  if( nome == &usuario && senha == pass)
  return 1;
  }
  fclose(arq);
  return 0;
}
