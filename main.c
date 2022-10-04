#include "Pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include "pcv.h"
#include "item.h"

int main(){
   int n_cidades, origem;
   scanf("%i %i", &n_cidades, &origem);
   float matriz[n_cidades][n_cidades];
   int a = 0, b = 0;
   float dist;
   origem--;

   for(int i = 0; i < n_cidades; i++){
      for(int j = 0; j < n_cidades; j++){
         matriz[i][j] = -1;
      }
   }

   //Preenchendo a matriz
   while(scanf("%i %i %f", &a, &b, &dist) != EOF){
      matriz[a-1][b-1] = dist;
      matriz[b-1][a-1] = dist;
   }

   //Printando a matriz:
   for(int i = 0; i < n_cidades; i++){
      for(int j = 0; j < n_cidades; j++){
         printf("%.2f ", matriz[i][j]);
      }
      printf("\n");
   }

   // //Criando o item de inicio:
   // ITEM* inicio = item_criar(origem, n_cidades);
   // if(inicio == NULL){
   //    printf("Erro ao criar cidade de origem.\n");
   //    return 1;
   // }
   // for(int i = 0; i < n_cidades; i++){
   //    item_set_distancia(inicio, i, matriz[origem][i]);
   // }
   //Criando os itens
   ITEM** vetor = vetor_criar(n_cidades, origem, matriz[][n_cidades]);

   for(int i = 0; i < n_cidades - 1; i++){
      for(int j = 0; j < n_cidades; j++){
         item_set_distancia(vetor[i], j, matriz[i][j]);
      }
   }

   print_vetor_itens(vetor, n_cidades);

   //Criando pilha de teste:
   PILHA* pilha = pilha_criar();
   if(pilha == NULL){
      printf("Erro ao criar a pilha.\n");
      return 1;
   }

   pilha_empilhar(pilha, vetor[0]);
   pilha_empilhar(pilha, vetor[1]);
   pilha_empilhar(pilha, vetor[2]);
   pilha_empilhar(pilha, vetor[4]);
   pilha_empilhar(pilha, vetor[3]);
   pilha_empilhar(pilha, vetor[0]);

   pilha_print(pilha);

   printf("TAMANHO: %i \n", pilha_tamanho(pilha));

   printf("Desempilhando:\n");
   while(pilha_vazia(pilha) == false){
      pilha_desempilhar(pilha);
   }

   pilha_print(pilha);

   printf("TAMANHO: %i \n", pilha_tamanho(pilha));

   //heap_permutacao(pilha, vetor, n_cidades, n_cidades, inicio);
   
   //item_apagar(&inicio);
   pilha_apagar(&pilha);
   vetor_apagar(vetor, n_cidades);
   return 0;
}