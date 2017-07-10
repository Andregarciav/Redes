#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>

#define MAX 128
typedef struct newUser
{
  char tipo;
  char login[15];
  int senha;
  char arquivo[MAX];
  char conteudo[MAX];
}novo;
