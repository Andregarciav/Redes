/*#include <stdio.h>
#include <stdlib.h>


void imprime_matriz(int m[10][10])
{
  char c = 'A';
  int i, j;
  //primeira linha
  printf("\t1  2  3  4  5  6  7  8  9  10\n\n");

  for (i=0;i<10;i++)
  {
     printf("%c:\t", c++);
        for (j=0;j<10;j++)
        {
            printf("%d  ", m[i][j]);
        }
     printf("\n");
  }

  printf("------------------------------------\n");

}
Porta_avioes()//, int Navio_tanque[4], int contratorpedeiros[3], int submarinos[2])
{
    int barco[5];
    int i;
    for (i = 0; i<5; i++)
    {
       barco[i]=1;
    }


}
int main ()
{
    int matriz[10][10];
    int i, j;
    int linha, coluna;
    int orientado;
    for (i=0;i<10;i++)
        {
            for (j=0;j<10;j++)
            {
             matriz[i][j]=0;
            }
        }
    imprime_matriz(matriz);
    printf("Digite a linha do porta avioes:\n");
    scanf("%d", &linha);
    linha-=1;
    printf("Digite a coluna do porta avioes:\n");
    scanf("%d", &coluna);
    coluna-=1;
    printf("Digite 1 para a orientacao horizonta e 2 para vertical do porta avioes:\n");
    scanf("%d", &orientado);
    if (orientado = '1')
    {
        for (i = coluna ; i < (coluna+4) ; i++)
        {
            matriz[linha][i] = Porta_avioes();
        }
    imprime_matriz(matriz);
    }
    else
    {
        for (i = linha ; i < (linha+4) ; i++)
        {
            matriz[i][coluna] = Porta_avioes();
        }
    imprime_matriz(matriz);
    }

return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>

int matriz[10][10]; // Variavel global

void imprime_matriz(int m[10][10])
{
  char c = 'A';
  int i, j;
  //primeira linha
  printf("\t1  2  3  4  5  6  7  8  9  10\n\n");

  for (i=0;i<10;i++)
  {
     printf("%c:\t", c++);
        for (j=0;j<10;j++)
        {
            printf("%d  ", m[i][j]);
        }
     printf("\n");
  }

  printf("------------------------------------\n");

}
/*int Porta_avioes()//, int Navio_tanque[4], int contratorpedeiros[3], int submarinos[2])
{
    int barco[5];
    int i;
    for (i = 0; i<5; i++)
    {
       barco[i]=1;
    }

    return 0;
}*/

int isere_barco (int barco, int y, int x, int dir)
{
        if (dir == 1) {
                if (x + barco >= 10) return 1;
                for (int i = 0 ; i < barco ; i++)
                {
                        matriz[y][x+i] = barco;
                }

        }
        else if (dir == 2) {
                if (y + barco >= 10) return 1;
                for (int i = 0 ; i < barco ; i++)
                {
                        matriz[y+i][x] = barco;
                }

        }
        else return 1;

        return 0;
}

int main ()
{
    int i, j;
    int linha, coluna;
    int orientado;
    int barco;
    char *tipo_barco[4] = {"submarinos", "Contra_torpedeiros", "Navio_tanque", "Porta_avioes"};
    for (i=0;i<10;i++)
        {
            for (j=0;j<10;j++)
            {
             matriz[i][j]=0;
            }
        }
    imprime_matriz(matriz);
    printf("Digite o barco:\n1 - submarinos\n2 - Contra_torpedeiros\n3 - Navio_tanque\n4 - Porta_avioes\n");
    scanf("%d", &barco);
    printf("Digite a linha do %s:\n", tipo_barco[barco-1]);
    scanf("%d", &linha);
    linha-=1;
    printf("Digite a coluna do %s:\n", tipo_barco[barco-1]);
    scanf("%d", &coluna);
    coluna-=1;
    printf("Digite 1 para a orientacao horizonta e 2 para vertical do %s:\n", tipo_barco[barco-1]);
    scanf("%d", &orientado);
    // if (orientado = '1')
    // {
    //     for (i = coluna ; i < (coluna+4) ; i++)
    //     {
    //         matriz[linha][i] = Porta_avioes();
    //     }

    if (isere_barco(barco+1, linha, coluna, orientado)) {
            printf("fora dos limites, tente de novo\n");
    }
    imprime_matriz(matriz);
    // }
    // else
    // {
    //     for (i = linha ; i < (linha+4) ; i++)
    //     {
    //         matriz[i][coluna] = Porta_avioes();
    //     }
    // imprime_matriz(matriz);
    // }

return 0;
}
