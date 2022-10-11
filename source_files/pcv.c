#include <stdio.h>
#include <stdlib.h>

#include "../headers/pcv.h"

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

void troca(cidade_t** a, int i, int j)
{
  cidade_t* temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void heap_permutacao(list_t** melhorLista, cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int parte, int tam)
{
    for (int i = 0; i < parte; i++) {
        heap_permutacao(melhorLista, cidadesDestino, cidadeOrigem, parte - 1, tam);

        if (parte % 2 == 1){
            troca(cidadesDestino, 0, parte - 1);
        }
        else{
            troca(cidadesDestino, i, parte-1);
        }
    }

    if (parte == 1)
    {
        list_t* listaAtual = lista_criar();

        lista_inserir(listaAtual, cidadeOrigem);

        for(int i = 0; i < tam; i++)
        {
            if(!lista_inserir(listaAtual, cidadesDestino[i])) 
            {
                lista_apagar(&listaAtual);
                return;
            }
        }

        if(!lista_inserir(listaAtual, cidadeOrigem)) 
        {
            lista_apagar(&listaAtual);
            return;
        }

        float distanciaAtual = lista_get_distancia(listaAtual);
        float melhorDistancia = lista_get_distancia(*melhorLista);

        if(melhorDistancia == 0 || distanciaAtual < melhorDistancia)
        {
            lista_apagar(melhorLista);

            *melhorLista = listaAtual;
        }
        else if(distanciaAtual == melhorDistancia)
        {
            if(cidade_get_cidade_id(cidadesDestino[1]) < cidade_get_cidade_id(list_get_primeiro_destino(*melhorLista)))
            {
                lista_apagar(melhorLista);

                *melhorLista = listaAtual;               
            }
            else
            {
                lista_apagar(&listaAtual);
            }
        }
        else
        {
            lista_apagar(&listaAtual);
        }
    }
}

list_t* calcular_melhor_trajeto(cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int n_cidades)
{
    list_t* melhorLista = lista_criar();

    heap_permutacao(&melhorLista, cidadesDestino, cidadeOrigem, n_cidades - 1, n_cidades - 1);

    return melhorLista;
}