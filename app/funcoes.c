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
  char *nome = NULL ;
  int senha;
  arq = fopen("controle.txt" , "r");
  fgets ( buffer , MAX , arq);
  printf("%s\n", buffer);
  printf("%s  | %d\n", usuario, pass);
  while (!feof(arq))
  {
    nome = strtok(buffer, ",");
    senha = atoi(strtok(NULL, ","));
    printf("%s  | %d\n", nome, senha);
    printf("%s  | %d\n", usuario, pass);
    if( &nome == &usuario && senha == pass)
    {
      printf("entrei");
      fclose(arq);
      return 1;
    }
    fgets ( buffer , MAX , arq);
  }
  fclose(arq);
  return 0;
}
