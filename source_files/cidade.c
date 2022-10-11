#include <stdio.h>
#include <stdlib.h>

#include "../headers/cidade.h"

struct cidade
{
    int cidade_id;
    float *distancias;	
};

cidade_t *cidade_criar(int cidade, int n_cidades, float** matriz_distancias)
{
    cidade_t* p = (cidade_t*)malloc(sizeof(cidade_t));

    p->cidade_id = cidade;
    p->distancias = (float*)malloc(n_cidades * sizeof(float));

    if(p->distancias == NULL)
    {
        return NULL;
    }

    for(int i = 0; i < n_cidades; i++)
    {
        p->distancias[i] = matriz_distancias[p->cidade_id - 1][i];
    }

    return p;
}

int cidade_get_cidade_id(cidade_t *cidade)
{
    if(cidade == NULL) return -1;

    return cidade->cidade_id;
}

float* cidade_get_distancias(cidade_t *cidade)
{
    if(cidade == NULL) return NULL;

    return cidade->distancias;
}

bool cidade_apagar(cidade_t **cidade)
{
    if(cidade==NULL || *cidade==NULL)
    {
        return false;
    }

    free((*cidade)->distancias);
    free(*cidade);

    *cidade = NULL;
    
    return true;
}