#include <stdio.h>
#include <stdlib.h>
#include "pcv.h"
#include "item.h"
#include "Pilha.h"

int qtd = 0;

float** ler_matriz_distancias(int n_cidades)
{
    float** matriz = (float**)malloc(n_cidades * sizeof(float*));

    if(matriz == NULL) return NULL;

    for(int i = 0; i < n_cidades; ++i)
    {
        matriz[i] = (float*)malloc(n_cidades * sizeof(float));

        if(matriz[i] == NULL)
        {
            for(int j = 0; j < i; ++j)
            {
                free(matriz[i]);
            }

            free(matriz);

            return NULL;
        }
    }

    int a, b;
    float distancia;

    for(int i = 0; i < n_cidades; i++)
    {
        for(int j = 0; j < n_cidades; j++)
        {
            matriz[i][j] = -1;
        }
    }

   //Preenchendo a matriz
   while(scanf("%i %i %f", &a, &b, &distancia) != EOF)
   {
        matriz[a-1][b-1] = distancia;
        matriz[b-1][a-1] = distancia;
   }

    return matriz;
}

void matriz_apagar(float*** matriz_distancias, int n_cidades)
{
    if(matriz_distancias == NULL || *matriz_distancias == NULL) return;

    for(int i = 0; i < n_cidades; ++i)
    {
        free(*matriz_distancias[i]);
    }

    free(*matriz_distancias);

    *matriz_distancias = NULL;
}

void troca(ITEM **a, int i, int j){
  ITEM* temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void print_vetor(int *vetor, int n){
    for(int i = 0; i < n; i++){
        printf("%i ", vetor[i]);
    }
    printf("\n");
}

void heap_permutacao(PILHA* melhorPilha, ITEM** vetor, int parte, int tam, ITEM* inicio){
    if (parte == 1)
    {
        PILHA* pilhaAtual = pilha_criar();
        print_vetor_itens(vetor, tam);
        
        pilha_empilhar(pilhaAtual, inicio);

        for(int i = 0; i < tam; i++)
        {
            if(!pilha_empilhar(pilhaAtual, vetor[i])) 
            {
                pilha_apagar(&pilhaAtual);
                return;
            }
        }

        if(!pilha_empilhar(pilhaAtual, inicio)) 
        {
            pilha_apagar(&pilhaAtual);
            return;
        }
        //pilha_print(pilhaAtual);

        if(pilha_get_distancia(pilhaAtual) < pilha_get_distancia(melhorPilha));
        {
            pilha_apagar(&melhorPilha);

            melhorPilha = pilhaAtual;
        }

        return;
    }
 
    for (int i = 0; i < parte; i++) {
        heap_permutacao(melhorPilha, vetor, parte - 1, tam, inicio);

        if (parte % 2 == 1){
            troca(vetor, 0, parte - 1);
        }
        else{
            troca(vetor, i, parte-1);
        }
    }
}

PILHA* calcular_melhor_trajeto(ITEM** vetor, int tam, ITEM* inicio)
{
    PILHA* melhorPilha = pilha_criar();
    pilha_set_distancia(melhorPilha, 0);

    heap_permutacao(melhorPilha, vetor, tam, tam, inicio);

    return melhorPilha;
}
// void pcv(ITEM** vetor, int n_cidades, int origem){
//     PILHA* pilha = pilha_criar();
//     int tam = n_cidades - 1;


//     //Empilhando a cidade de origem:
//     pilha_empilhar(pilha, vetor[origem-1]);

    

//     pilha_apagar(pilha);
// }

void print_qtd(){
    printf("TOTAL %i \n", qtd);
}