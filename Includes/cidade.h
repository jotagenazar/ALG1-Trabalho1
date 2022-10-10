#ifndef CIDADE_H
#define CIDADE_H
	
#include <stdbool.h>

typedef struct cidade cidade_t;

cidade_t *cidade_criar(int cidade, int n_cidades, float** matriz_distancias);

bool cidade_apagar(cidade_t **cidade);

int cidade_get_cidade_id(cidade_t *cidade);

float* cidade_get_distancias(cidade_t *cidade);

#endif