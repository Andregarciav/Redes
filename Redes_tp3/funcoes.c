#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "server.h"
void verificaUsuario(novo *usuario)
{
  printf("%s\n deu?", usuario[0].login);
  int i=0;
  if(!usuario)
  {
    criaArquivo(usuario[0].login);
    return 1;
  }
  return 0;
}
