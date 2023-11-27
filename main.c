#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char resp;
    int N, nr;
    double Req = 0, r = 0, fator = 0, soma = 0;

    double **matriz;
    double *X;

    printf("\n=======================================\n");
    printf("        Calculadora de Circuitos");
    printf("\n=======================================\n");

    printf("\nDigite a quantidade de malhas do circuito: ");
    scanf("%d", &N);
    system("cls");

    matriz = (double**) malloc(sizeof(double*) * N);

    X = (double*) malloc(sizeof(double) * N);

    for(int i = 0; i < N; i ++){
        matriz[i] = (double*)malloc(sizeof(double) * (N+1));
    }

    for(int i = 0; i < N; i ++){
        printf("\nDigite quantos resistores existem na malha %d: ", i + 1);
        scanf("%d", &nr);
        system("cls");

        Req = 0;
        for(int k = 0; k < nr; k ++){
            printf("\nOBS: Separe por espaco todos os valores\nExemplo: 1 2 3 4 5\n");
            printf("\nDigite  o valor do resistor %d que esta(ao) contido(s) na Malha %d: ", k+1, i + 1);

            scanf("%lf", &r);
            Req += r;
        }
        matriz[i][i] = Req;
        system("cls");
    }

    r = 0;
    Req = 0;

    for(int i = 0; i < N; i ++){
        printf("\nOBS: Digite somente S ou N");
        printf("\nExiste algum resistor compartilhado na malha %d? : ", i + 1);
        getchar();
        scanf("%c", &resp);
        system("cls");

        if(resp == 83){
            for(int j = 0; j < N; j ++){
                if(j != i){
                    printf("\nDigite quantos resistores estao sendo compartilhados entre %d e %d: ", i+1, j+1);
                    scanf("%d", &nr);
                    system("cls");

                    Req = 0;
                    for(int k = 0; k < nr; k ++){
                        printf("\nOBS: Separe por espaco todos os valores\nExemplo: 1 2 3 4 5\n");
                        printf("\nDigite o(s) valor(es) do(s) resistor(es), em ohm: ");
                        scanf("%lf", &r);
                        Req += (r*-1);
                    }
                    matriz[i][j] = Req;
                }
                system("cls");
            }
        }

        else{
            for(int j = 1; j < N; j ++){
                matriz[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < N; i ++){
        printf("\nQuantas fontes exitem no circuito %d: ", i+1);
        scanf("%d", &nr);
        system("cls");

        Req = 0;
        for(int j = 0; j < nr; j ++){
            printf("Digite o valor da fonte %d, em volts: ", j+1);
            scanf("%lf", &r);
            Req += r;
            system("cls");
        }

        matriz[i][N] = Req;
    }

    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N + 1; j++){
            printf("%.1lf ", matriz[i][j]);
        }
        printf("\n");
    }

    for(int k = 0; k<N-1; k++){ // "k" determina a linha do pivo
        for(int i = (k+1); i<N; i++){//Este laco se refere as linhas que sofrerao as eliminacoes, que sempre iniciarao na linha seguinte da linha pivo
        fator = matriz[i][k] / matriz[k][k];//fator de correcao que sera multiplicada pela linha pivo
        for(int j=0; j<=N; j++){//loco interno se refere a cada coluna da linha que sofrerao modificacoes da linha i
                matriz[i][j] = matriz[i][j] - fator * matriz[k][j];
            }
        }
    }

    X[N-1] = matriz[N-1][N] / matriz[N-1][N-1]; // Primeria variavel que obtamos : "x3"


// SUBSTITUICAO PROGRESSIVA => Usa a vari�vel que encontramos e acha as outras

    for(int i=N-2; i>=0; i--){  //Laco exterior se refere a linha que recebera os valores das variaveis ja encontradas para descobrirmos  as outras. Ela se inicia na penultima linha e vai ate a primeira

        soma = 0;

        for(int j=(i+1); j<N; j++){     //Laco interno se refere as colunas da linha i
            soma = soma + matriz[i][j] * X[j]; // soma todos os numeros da linha que ja tem o valor de x
        }
        X[i] = (matriz[i][N] - soma)/ matriz[i][i]; // Calcula o x da coluna i
    }

    printf("\nResultado: " );
    for(int i=0; i<N; i++)
         printf("\nI%d = %.3lf\n", i+1, X[i]);

    for(int i = 0; i < N; i ++){
        free(matriz[i]);
    }
    free(matriz);
    free(X);

    return 0;
}
