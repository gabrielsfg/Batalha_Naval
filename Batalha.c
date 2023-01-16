#include<stdio.h>
#include<stdlib.h>
#include <time.h>


#define DIM 5
#define NAVIOS 3

//Funcao para iniciar o mapa com -1 em todas as posicoes
void init_mapa(int mapa[][DIM]){
    int i,j;
    for(i=0;i<DIM;i++){
        for (j=0;j<DIM; j++){
            mapa[i][j] = -1; 
        }
    }
}

//Funcao para mostrar o mapa 
// - em posicoes que nao tomaram tiro
// / em posicoes que tomaram tiro e nao havia navios
// X em posicoes que tomaram tiro e havia navio
void mostra_mapa(int mapa[][DIM]){
    int i, j;
    printf("\t1 \t2 \t3 \t4 \t5");
    printf("\n");

    for(i=0; i<DIM;i++){
        printf("%d", i+1);
        for(j=0;j<DIM;j++){
            if (mapa[i][j]==-1){
                printf("\t-");
            }else if (mapa[i][j]==0){
                printf("\t/");
            }else if (mapa[i][j]==1){
                printf("\tX");
            }
        }
        printf("\n");
    }
}

void init_navios(int navios[][2]){
    srand( time(0) );
    int navio, anterior;

    for(navio = 0; navio<NAVIOS;navio++){
        navios[navio][0] = rand()%5;
        navios[navio][1] = rand()%5;
        for(anterior=0 ; anterior < navio ; anterior++){
                if( (navios[navio][0] == navios[anterior][0])&&(navios[navio][1] == navios[anterior][1]) )
                    do{
                        navios[navio][0]= rand()%5;
                        navios[navio][1]= rand()%5;
                    }while( (navios[navio][0] == navios[anterior][0])&&(navios[navio][1] == navios[anterior][1]) );
            }
    }
}

void atirar(int tiro[2]){
    printf("Linha: ");
    scanf("%d",&tiro[0]);
    tiro[0]--;

    printf("Coluna: ");
    scanf("%d",&tiro[1]);
    tiro[1]--;
}

int tiro_certo(int tiro[2], int navios[][2]){
    int navio;
    for(navio=0 ; navio < 3 ; navio++){
        if( tiro[0]==navios[navio][0] && tiro[1]==navios[navio][1]){
            printf("Você acertou o tiro (%d,%d)\n",tiro[0]+1,tiro[1]+1);
            return 1;
        }
    }
    return 0;
}

void mapa_atualizado(int tiro[2], int navios[][2], int tabuleiro[][5]){
        if(tiro_certo(tiro,navios))
            tabuleiro[tiro[0]][tiro[1]]=1;
        else
            tabuleiro[tiro[0]][tiro[1]]=0;
    }

int main()
{
    int mapa[DIM][DIM];
    int navios[NAVIOS][2];
    int tiro[2];
    int tentativas = 0, acertos = 0;

    init_mapa(mapa);
    init_navios(navios);

    printf("\n");

    do{
        mostra_mapa(mapa);
        atirar(tiro);
        tentativas++;

        if(tiro_certo(tiro, navios)){
            acertos++;
        }

        mapa_atualizado(tiro,navios,mapa);
    }while(acertos != 3);

    printf("\n Final de jogo. Voce ganhou apos %d tentativas /n", tentativas);
    mostra_mapa(mapa);




    return 0;
}
