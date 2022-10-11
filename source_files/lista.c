#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/lista.h"

typedef struct node node_t;

struct node
{
    cidade_t* cidade;
    node_t* next;
};

struct list
{
    float dist_total;
    node_t *start; node_t *end;
};


list_t* lista_criar()
{
    list_t* list = (list_t*)malloc(sizeof(list_t));
    assert(list != NULL);

    list->start = NULL;
    list->end = NULL;

    list->dist_total = 0;

    return list;
}

cidade_t* list_get_primeiro_destino(list_t* list)
{
    if(list == NULL) return NULL;

    return list->start->next->cidade;
}


bool lista_inserir(list_t* list, cidade_t* x)
{
    assert(list != NULL);

    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->cidade = x;
    newNode->next = NULL;
    float dist = 0;

    if(lista_vazia(list))
    {
        list->start = newNode;
    }
    else
    {
        list->end->next = newNode;
        dist = cidade_get_distancias(list->end->cidade)[(cidade_get_cidade_id(x)) - 1];
    }

    list->dist_total += dist;
    list->end = newNode;

    if(dist == -1) return false;

    return true;
}

float lista_get_distancia(list_t* list)
{
    if(list == NULL) return -1;

    return list->dist_total;
}

bool lista_vazia(list_t* list)
{
    assert(list != NULL);

    if(list->start == NULL)
    {
        return true;
    }

    return false;
}

void lista_imprimir(list_t* list)
{
    assert(list != NULL);

    node_t* aux = list->start;

    while(aux != NULL)
    {
        printf("%d ", cidade_get_cidade_id(aux->cidade));
        aux = aux->next;
    }
    printf("\n");
}

void lista_apagar(list_t** list)
{
    if(list == NULL || *list == NULL) return;

    node_t* aux = (*list)->start;
    while(aux != NULL)
    {
        (*list)->start = aux->next;
        free(aux);
        aux = (*list)->start;
    }

    free(*list);
}