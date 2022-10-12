#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/lista.h"

typedef struct node node_t;

struct node { //estrutura de dados referente aos nós guardados na lista
    cidade_t* cidade; //endereco da cidade guardada no nó
    node_t* next; //endereco do próximo nó
};

struct list { //estrutura de dados referente à lista que armazena os nós com as cidades
    float dist_total; //armazena o valor da distancia total da lista, da primeira à última cidade armazenada
    node_t *start; node_t *end; //armazenam o primeiro e o último nó da lista, respectivamente
};


list_t* lista_criar() { //função que cria e aloca uma lista e retorna seu endereço
    //alocação
    list_t* list = (list_t*)malloc(sizeof(list_t));
    assert(list != NULL);

    //inicialização
    list->start = NULL;
    list->end = NULL;
    list->dist_total = 0;

    return list; //retorno do endereço da lista
}

cidade_t* list_get_primeiro_destino(list_t* list) { //função que retorna a cidade no primeiro nó da lista
    if(list == NULL) return NULL;

    return list->start->next->cidade;
}


bool lista_inserir(list_t* list, cidade_t* x) { //função que cria um novo nó com a cidade passada e o insere na ultima posição. se o caminho criado é possível, retorna verdadeiro; se impossível, retorna falso
    assert(list != NULL);

    //alocação do novo nó com a cidade passada
    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);
    newNode->cidade = x;
    newNode->next = NULL;
    
    //inserção do nó na lista e cálculo da distancia entre a nova cidade e a anterior
    float dist; //armazena a distancia entre essas duas cidades
    if(lista_vazia(list)) { 
        list->start = newNode;
        dist = 0;
    } else { //se a lista não estiver vazia, o nó é inserido ao final da lista
        list->end->next = newNode; //o nó do ultimo elemento aponta para o novo nó
        dist = (cidade_get_distancias(list->end->cidade))[(cidade_get_cidade_id(x)) - 1]; //a distancia entre as cidades é extraída do array de distancias da ultima cidade antes da inserção
                //extrai o array de distancias            //extrai o id da cidade inserida
    }

    //atualização do fim da lista e da distancia total para considerar a adição da nova cidade
    list->dist_total += dist;
    list->end = newNode;

    if(dist == -1) return false; //se a distancia entre as duas ultimas cidades for invalida, o caminho entre elas nao existe, a inserção retorna falso

    return true; //retorna verdadeiro para a lista com um possivel caminho
}

float lista_get_distancia(list_t* list) { //funcao que retorna a distancia total entre as cidades armazenadas na lista passada
    if(list == NULL) return -1;

    return list->dist_total;
}

bool lista_vazia(list_t* list) { //função que checa se a lista esta vazia
    assert(list != NULL);

    if(list->start == NULL) {
        return true;
    }

    return false;
}

void lista_imprimir(list_t* list) { //procedimento que imprime cada cidade da lista passada como parametro
    assert(list != NULL);

    node_t* aux = list->start; //nó auxiliar de leitura se inicia no primeiro elemento

    while(aux != NULL) { //impressão de cada cidade e avanco do nó auxiliar até a ultima cidade
        printf("%d ", cidade_get_cidade_id(aux->cidade));
        aux = aux->next;
    }
    printf("\n");
}

void lista_apagar(list_t** list) { //procedimento que desaloca a lista passada e cada um de seus nós
    if(list == NULL || *list == NULL) return; //se o ponteiro é vazio não ha o que desalocar

    node_t* aux = (*list)->start; //nó auxiliar de leitura se inicia no primeiro elemento

    while(aux != NULL) { //desalocação de cada elemento e avanco do nó auxiliar até a ultima cidade
        (*list)->start = aux->next;
        free(aux);
        aux = (*list)->start;
    }

    free(*list); //desalocação da lista que armazenava os ponteiros desalocados
}