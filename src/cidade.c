#include <stdio.h>
#include <stdlib.h>

#include "../Includes/cidade.h"

cidade_t *cidade_criar(int cidade, int n_cidades, float** matriz_distancias) { //função que aloca e preenche uma cidade e seu vetor de distâncias, retorna o endereço da cidade
    cidade_t* p = (cidade_t*)malloc(sizeof(cidade_t)); //alocação da cidade a ser retornada

    p->cidade_id = cidade; 

    //preencimento do vetor de distancias
    p->distancias = (float*)malloc(n_cidades * sizeof(float));
    if(p->distancias == NULL) { //caso erro na alocação das distancias, o array nao podera ser preenchido
        return NULL;
    }
    for(int i = 0; i < n_cidades; i++) { //para cada posicao do vetor, a distancia é preenchida a partir da matriz de distancias
        p->distancias[i] = matriz_distancias[p->cidade_id - 1][i];
    }

    return p; //retorno do endereço da cidade criada
}

int cidade_get_cidade_id(cidade_t *cidade) { //função que retorna o id da cidade passada
    if(cidade == NULL) return -1;

    return cidade->cidade_id;
}

float* cidade_get_distancias(cidade_t *cidade) { //função que retorna o array de distancias da cidade passada
    if(cidade == NULL) return NULL;

    return cidade->distancias;
}

bool cidade_apagar(cidade_t **cidade) { //funcao que apaga a cidade passada
    if(cidade==NULL || *cidade==NULL) { //se os ponteiros já forem nulos, não há o que apagar
        return false;
    }

    free((*cidade)->distancias);
    free(*cidade);

    *cidade = NULL;
    
    return true;
}