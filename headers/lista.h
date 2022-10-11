#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

#include "cidade.h"

typedef struct list list_t;

list_t* lista_criar();

bool lista_inserir(list_t* list, cidade_t* x);

cidade_t* list_get_primeiro_destino(list_t* list);

bool lista_vazia(list_t* list);

void lista_imprimir(list_t* list);

void lista_apagar(list_t** list);

float lista_get_distancia(list_t* list);

#endif //LISTA_H