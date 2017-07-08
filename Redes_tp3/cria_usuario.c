#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "server.h"
#define MAX 80


void criaArquivo (novo* usuario)
{
  printf("entrei2");
  printf("entrei0");
  scanf("%s\n", usuario[0].login);
  printf("entrei1");
  printf("%s\n", usuario[0].login);
  scanf ("%d" , &usuario[0].senha);
  printf("%d\n", *usuario[0].senha);
  FILE *arq = fopen(usuario[0].login , "w");
  if (arq == NULL)
  {
    printf("Erro ao criar o arquivo");
  }
}
