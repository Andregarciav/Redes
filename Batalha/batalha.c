
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matriz[10][10];
int matriz_cpu[10][10];

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


int isere_barco (int barco, int y, int x, int dir, int matrizInsere[10][10])
{
        if (dir == 1) {
                if (x + barco >= 10) return 0;
                for (int i = 0 ; i < barco ; i++)
                {
                        matrizInsere[y][x+i] = barco;
                }

        }
        else if (dir == 2) {
                if (y + barco >= 10) return 0;
                for (int i = 0 ; i < barco ; i++)
                {
                        matrizInsere[y+i][x] = barco;
                }

        }
        else return 0;

        return 1;
}
/*void preenche_cpu(){
    int maxbarcos_cpu = 4;
    int barco;
    int limite_barcos[4]={1,1,1,1};
    int maxbarcos = 4;
    int limite_barcos_cpu[4]={1,1,1,1};
    int i, j;
    int linha, coluna;
    char clinha;                //caractere da linha
    int orientado;
    char *tipo_barco[4] = {"submarinos", "Contra_torpedeiros", "Navio_tanque", "Porta_avioes"};


    while (maxbarcos_cpu >0)
    {

        srand (time (NULL));
        //printf("Digite o barco:\n2 - submarinos\n3 - Contra_torpedeiros\n4 - Navio_tanque\n5 - Porta_avioes\n");
        barco = rand()%4;
        printf("Digite a linha do %s:\n", tipo_barco[barco+2]);
        //scanf(" %c", &clinha);
        linha = rand()%10;
        //if(clinha > 'H')  //converte caracter para inteiro da matriz
        //        linha = (int)(clinha - 97);
        //else
        //        linha = (int)(clinha - 65);
        //printf("Digite a coluna do %s:\n", tipo_barco[barco-2]);
        //scanf(" %d", &coluna);
        coluna=rand()%10;
        printf("Digite 1 para a orientacao horizonta e 2 para vertical do %s:\n", tipo_barco[barco]);
        //scanf(" %d", &orientado);
        orientado = rand()%2;
        if (limite_barcos_cpu[barco] > 0 )
        {
            printf("Inserido! %d %d %d orientado %d \n", barco, linha, coluna, orientado);
            isere_barco(barco, linha, coluna, orientado, matriz_cpu);
            limite_barcos_cpu[barco]--;
            maxbarcos_cpu--;
        }
        else
        {
            printf("fora dos limites, tente de novo\n");
        }

        imprime_matriz(matriz_cpu);
    }

}
*/
int main ()
{
    int i, j;
    int linha, coluna;
    char clinha;                //caractere da linha
    int orientado;
    int barco;
    int limite_barcos[4]={1,1,1,1};
    int maxbarcos = 4;
  //  int limite_barcos_cpu[4]={1,1,1,1};

    char *tipo_barco[4] = {"submarinos", "Contra_torpedeiros", "Navio_tanque", "Porta_avioes"};

    // barcos cpu
    /*for (i=0;i<10;i++)
        {
            for (j=0;j<10;j++)
            {
             matriz_cpu[i][j]=0;
            }
        }

    preenche_cpu();
    imprime_matriz(matriz_cpu);
*/
    for (i=0;i<10;i++)
        {
            for (j=0;j<10;j++)
            {
             matriz[i][j]=0;
            }
        }
    imprime_matriz(matriz);
    while (maxbarcos >0)
    {
        printf("Digite o barco:\n2 - submarinos\n3 - Contra_torpedeiros\n4 - Navio_tanque\n5 - Porta_avioes\n");
        scanf(" %d", &barco);
        printf("Digite a linha do %s:\n", tipo_barco[barco-2]);
        scanf(" %c", &clinha);
        if(clinha > 'H')  //converte caracter para inteiro da matriz
                linha = (int)(clinha - 97);
        else
                linha = (int)(clinha - 65);
        printf("Digite a coluna do %s:\n", tipo_barco[barco-2]);
        scanf(" %d", &coluna);
        coluna-=1;
        printf("Digite 1 para a orientacao horizonta e 2 para vertical do %s:\n", tipo_barco[barco-2]);
        scanf(" %d", &orientado);
        if (limite_barcos[barco-2] > 0)
        {
            printf("Inserido! %d %d %d %d \n", barco, linha, coluna, orientado);
            isere_barco(barco, linha, coluna, orientado, matriz);
            limite_barcos[barco-2]--;
            maxbarcos--;
        }
        else
        {
            printf("fora dos limites, tente de novo\n");
        }
        imprime_matriz(matriz);
    }



return 0;
}
