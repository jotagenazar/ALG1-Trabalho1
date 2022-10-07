#include <stdio.h>
#include <stdlib.h>
#include "pcv.h"
#include "item.h"
#include "Pilha.h"

int qtd = 0;

void heap_permutacao(PILHA* melhorPilha,PILHA* pilhaAtual, ITEM** vetor, int parte, int tam, ITEM* inicio)
{
    for (int i = 0; i < parte; i++) {
        heap_permutacao(melhorPilha, vetor, parte - 1, tam, inicio);

        if (parte % 2 == 1){
            troca(vetor, 0, parte - 1);
        }
        else{
            troca(vetor, i, parte-1);
        }
    }

    if (parte == 1)
    {
        if(pilha_get_tamanho(pilhaAtual) == 0){
            pilha_empilhar(pilhaAtual, inicio);

            for(int i = tam - 1; i >= 0; i--){
                if(!pilha_empilhar(pilhaAtual, vetor[i])){
                    return
                }
            }
        }

        if(!pilha_empilhar(pilhaAtual, inicio)){
            return;
        }


        return;
    }
}

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
        free((*matriz_distancias)[i]);
    }

    free(*matriz_distancias);

    *matriz_distancias = NULL;
}

void troca(ITEM **a, int i, int j)
{
  ITEM* temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void trocarPilhas(PILHA* pilhaMelhor, PILHA* pilhaAtual)
{
    while(!pilha_vazia(pilhaMelhor))
    {
        pilha_desempilhar(pilhaMelhor);
    }

    while(!pilha_vazia(pilhaAtual))
    {
        ITEM* aux = pilha_desempilhar(pilhaAtual);

        pilha_empilhar(pilhaMelhor, aux);
    }
}

void heap_permutacao(PILHA** melhorPilha, ITEM** vetor, int parte, int tam, ITEM* inicio)
{
    for (int i = 0; i < parte; i++) {
        heap_permutacao(melhorPilha, vetor, parte - 1, tam, inicio);

        if (parte % 2 == 1){
            troca(vetor, 0, parte - 1);
        }
        else{
            troca(vetor, i, parte-1);
        }
    }

    if (parte == 1)
    {
        PILHA* pilhaAtual = pilha_criar();

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

        printf("DISTANCIA PILHA ATUAL: %.2f\n", pilha_get_distancia(pilhaAtual));
        printf("Trajeto Atual: ");
        pilha_print(pilhaAtual);

        printf("DISTANCIA PILHA MELHOR: %.2f\n\n\n", pilha_get_distancia(*melhorPilha));

        if(pilha_get_distancia(pilhaAtual) < pilha_get_distancia(*melhorPilha))
        {
            pilha_apagar(melhorPilha);

            *melhorPilha = pilhaAtual;

            //pilha_apagar(&pilhaAtual);
        }
        else
        {
            pilha_apagar(&pilhaAtual);
        }


        return;
    }
}

PILHA* calcular_melhor_trajeto(ITEM** vetor, int tam, ITEM* inicio)
{
    PILHA* melhorPilha = pilha_criar();
    pilha_set_distancia(melhorPilha, RAND_MAX);

    heap_permutacao(&melhorPilha, vetor, tam, tam, inicio);

    printf("MELHOR PILHA: ");
    pilha_print(melhorPilha);
    return melhorPilha;
}