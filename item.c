#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"

struct item_{
    int cidade;//Identificador da cidade
    float *distancias;
    ITEM* anterior;
};

ITEM *item_criar(int cidade, int n_cidades)
{
    ITEM* p = (ITEM*)malloc(sizeof(ITEM));

    p->cidade = cidade;
    p->anterior = NULL;
    p->distancias = (float*)malloc(n_cidades * sizeof(float));

    if(p->distancias == NULL)
    {
        return NULL;
    }

    return p;
}

bool item_apagar(ITEM **item){
    if(item==NULL || *item==NULL){
        return false;
    }
    free((*item)->distancias);
    free(*item);
    return true;
}

void item_imprimir(ITEM *item){
    if(item != NULL){
        printf("Cidade: %i \n", item->cidade);
    }
    printf("O item nao existe.\n");
}

int item_get_chave(ITEM *item)
{
    if(item!=NULL)
    {
        return item->cidade;
    }
}

bool item_set_chave(ITEM *item, int chave){
    if(item!=NULL){
        item->cidade = chave;
        return true;
    }
    return false;
}

ITEM* item_get_anterior(ITEM* item){
    if(item != NULL){
        return item->anterior;
    }
}

bool item_set_anterior(ITEM* item, ITEM* anterior){
    if(item==NULL || anterior==NULL){
        return false;
    }
    item->anterior = anterior;
    return true;
}

float item_get_distancia(ITEM* item){
    /*Essa funcao pega a distancia entre uma
    cidade e sua anterior na pilha.*/
    if(item==NULL){
        printf("ITEM NULL.\n");
        return -1;
    }
    return (item->anterior)->distancias[item->cidade - 1];
}

void vetor_preencher(int n_cidades, ITEM** vetor, float** matriz_distancias)
{
    for(int i = 0; i < n_cidades - 1; i++)
    {
        for(int j = 0; j < n_cidades; j++)
        {
            item_set_distancia(vetor[i], j, matriz_distancias[vetor[i]->cidade][j]);
        }
    }
}

ITEM** vetor_criar(int n_cidades, int index_origem, float** matriz_distancias)
{
    ITEM** vetor = (ITEM**)malloc((n_cidades - 1)*sizeof(ITEM*));
    if(vetor == NULL)
    {
        return NULL;
    }

    int j = 0;
    for(int i = 0; i < n_cidades; ++i)
    {
        if(i != index_origem)
        {
            vetor[j] = item_criar(i, n_cidades);
            j++;
        }
    }

    vetor_preencher(n_cidades, vetor, matriz_distancias);
    
    return vetor;
}

bool vetor_apagar(ITEM** vetor, int n_cidades){
    if(vetor == NULL){
        return false;
    }

    for(int i = 0; i < n_cidades; i++){
        item_apagar(&vetor[i]);
    }
    return true;
}

bool item_set_distancia(ITEM* item, int cidade, float dist)
{
    if(item == NULL)
    {
        return false;
    }

    item->distancias[cidade] = dist;

    return true;
}

void print_vetor_itens(ITEM** vetor, int n_cidades)
{
    if(vetor == NULL) return;

    for(int i = 0; i < n_cidades - 1; i++)
    {
        printf("Cidade %i: ", item_get_chave(vetor[i]));

        for(int j = 0; j < n_cidades; j++)
        {
            printf("%.2f ", vetor[i]->distancias[j]);
        }
        printf("\n");
    }
}