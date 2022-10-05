#include <stdio.h>
#include <stdlib.h>

#include "Pilha.h"
#include "pcv.h"
#include "item.h"

int main(){
   int n_cidades, origem;

   scanf("%i %i", &n_cidades, &origem);
   origem--;

   float** matriz_distancias = ler_matriz_distancias(n_cidades);

   //Printando a matriz:
   for(int i = 0; i < n_cidades; i++)
   {
      for(int j = 0; j < n_cidades; j++)
      {
         printf("%.2f ", matriz_distancias[i][j]);
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

   ITEM** vetor = vetor_criar(n_cidades, origem, matriz_distancias);

   print_vetor_itens(vetor, n_cidades);

   //Criando pilha de teste:
   PILHA* pilha = pilha_criar();
   if(pilha == NULL)
   {
      printf("Erro ao criar a pilha.\n");
      return EXIT_FAILURE;
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
   
   matriz_apagar(&matriz_distancias, n_cidades);
   //item_apagar(&inicio);
   pilha_apagar(&pilha);
   vetor_apagar(vetor, n_cidades);

   return EXIT_SUCCESS;
}