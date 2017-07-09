#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>

#define MAX 80
typedef struct newUser
{
  char novo;
  char login[15];
  int senha[15];
}novo;
/*void verificaUsuario(novo *usuario)
{
  printf("%s\n deu?", usuario->login);
  int i=0;
  if(!usuario)
  {
    criaArquivo(usuario->login);
    return 1;
  }
  return verificaUsuario(usuario->login);
}
void criaArquivo (novo* usuario)
{
  printf("entrei1\n");
  printf("%s\n", *usuario->login);
  printf("entrei2\n");
  printf("%d\n", *usuario->senha);
  FILE *arq = fopen(usuario->login , "w");
  if (arq == NULL)
  {
    printf("Erro ao criar o arquivo");
  }
}*/
int main()
{
  novo *msg;
  FILE *arq;
  int senha;
  scanf("%c %s %d", &msg->novo, msg->login, &msg->senha);
  printf("entrei0\n");
  if (msg->novo == 'n' || msg->novo == 'N')
  {
    printf("novo usuario\n.");
    arq = fopen (msg->login, "r");
    printf("tentou abrir\n");
    if (arq == NULL)
    {
      printf("dentro do if\n");
      arq = fopen(msg->login , "w");
      if (arq == NULL)
      {
        printf("Erro ao criar o arquivo");
      }
      senha = atoi(&msg->senha);
      fprintf(senha, "%d", arq);
      fclose(arq);
    }
  }
  printf("%c\n", msg->novo);
  printf("%s\n", msg->login);
  printf ("%d" , *msg->senha);
  //criaArquivo(msg);
}
