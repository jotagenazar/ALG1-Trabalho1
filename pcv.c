#include <stdio.h>
#include <stdlib.h>
#include "pcv.h"
#include "item.h"
#include "Pilha.h"

int qtd = 0;

void troca(ITEM **a, int i, int j){
  ITEM* temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void print_vetor(int *vetor, int n){
    for(int i = 0; i < n; i++){
        printf("%i ", vetor[i]);
    }
    printf("\n");
}

void heap_permutacao(PILHA* pilha,ITEM** vetor, int parte, int tam, ITEM* inicio){
    if (parte == 1) {
        qtd++;
        pilha_empilhar(pilha, inicio);

        for(int i = 0; i < tam; i++){
            if(item_get_chave(vetor[i])!= item_get_chave(inicio)){
                pilha_empilhar(pilha, vetor[i]);
            }
        }
        pilha_empilhar(pilha, inicio);

        pilha_print(pilha);
        printf("Desempilhando:\n");
        while(pilha_vazia(pilha) == false){
            pilha_desempilhar(pilha);
        }
        return;
    }
 
    for (int i = 0; i < parte; i++) {
        heap_permutacao(pilha, vetor, parte - 1, tam, inicio);

        if (parte % 2 == 1){
            troca(vetor, 0, parte - 1);
        }
        else{
            troca(vetor, i, parte-1);
        }
    }
}

// void pcv(ITEM** vetor, int n_cidades, int origem){
//     PILHA* pilha = pilha_criar();
//     int tam = n_cidades - 1;


//     //Empilhando a cidade de origem:
//     pilha_empilhar(pilha, vetor[origem-1]);

    

//     pilha_apagar(pilha);
// }

void print_qtd(){
    printf("TOTAL %i \n", qtd);
}