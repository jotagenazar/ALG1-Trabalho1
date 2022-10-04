#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Pilha.h"
#include "item.h"

struct pilha{
    int tamanho;
    float dist_total;
    ITEM* topo;
};

PILHA *pilha_criar(void){
    PILHA* p = (PILHA*)malloc(sizeof(PILHA));
    p->tamanho = 0;
    p->dist_total = 0;
    p->topo = NULL;
    return p;
}

void pilha_apagar(PILHA **pilha){
    if(pilha != NULL && *pilha != NULL){
        if(pilha_vazia(*pilha) == false){
            ITEM* aux = (*pilha)->topo;
            while(aux != NULL){
                free(aux);
                aux = item_get_anterior(aux);
            }
        }
        free(*pilha);
    }
}

bool pilha_vazia(PILHA *pilha){
    if(pilha->tamanho == 0){
        return true;
    }
    return false;
}

bool pilha_cheia(PILHA *pilha, int n_cidades){
    if(pilha->tamanho == n_cidades + 1){
        /* n_cidades + 1 eh o maximo que a pilha
        pode empilhar.*/
        return true;
    }
    return false;
}

int pilha_tamanho(PILHA *pilha){
    if(pilha == NULL){
        return -1;
    }
    return pilha->tamanho;
}

ITEM *pilha_topo(PILHA *pilha){
    if(pilha == NULL){
        return NULL;
    }
    return pilha->topo;
}

bool pilha_empilhar(PILHA *pilha, ITEM *item){
    if(pilha == NULL || item == NULL){
        return false;
    }
   
    pilha->tamanho++;
   
    if(pilha->topo==NULL){//Primeiro item
        pilha->topo = item;
        item_set_anterior(item, NULL);
    }
    else{
        item_set_anterior(item, pilha->topo);
        if(item_get_distancia(item) == -1){
            return false;
        }
        pilha->topo = item;
        pilha->dist_total += item_get_distancia(item);
    }
    return true;
}

ITEM *pilha_desempilhar(PILHA *pilha){
    if(pilha==NULL || pilha_vazia(pilha) == true){
        return NULL;
    }

    //Atualizando tamanho e distancia
    pilha->tamanho--;

    if(pilha->tamanho != 0){
        pilha->dist_total -= item_get_distancia(pilha->topo);
    }

    //Tirando o elemento do topo
    ITEM* p = pilha->topo;
    pilha->topo = item_get_anterior(pilha->topo);
    item_set_anterior(p, NULL);
    return p;
}

void pilha_print(PILHA *pilha){
    if(pilha != NULL){
        int tam = pilha->tamanho;
        ITEM* aux = pilha->topo;
        printf("Cidades: ");
        while(tam > 0){
            printf("%i ", item_get_chave(aux));
            aux = item_get_anterior(aux);
            tam--;
        }
        printf("\n");
        printf("DISTANCIA: %.2f \n", pilha->dist_total);
    }
}