#include <stdio.h>
#include <stdlib.h>

#include "Pilha.h"
#include "pcv.h"
#include "item.h"

int main(){
   int n_cidades, origem;

   scanf("%i %i", &n_cidades, &origem);
   int indexOrigem = origem - 1;

   float** matriz_distancias = ler_matriz_distancias(n_cidades);

   printf("MATRIZ:\n");

   for(int i = 0; i < n_cidades; i++){
      for(int j = 0; j < n_cidades; j++){
         printf("%.2f ", matriz_distancias[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   int tamanhoVetor = n_cidades - 1;
   ITEM** vetor = vetor_criar(n_cidades, indexOrigem, matriz_distancias);

   printf("\n");
   print_vetor_itens(vetor, tamanhoVetor);
   printf("\n");
   
   ITEM* cidadeOrigem = item_criar(origem, n_cidades, matriz_distancias);



   PILHA* melhorTrajeto = calcular_melhor_trajeto(vetor, tamanhoVetor, cidadeOrigem);

   float melhorDistancia = pilha_get_distancia(melhorTrajeto);

   //TESTE

   // printf("TESTE:\n");
   // PILHA* pilha = pilha_criar();

   // pilha_empilhar(pilha, cidadeOrigem);
   // pilha_print(pilha);
   // pilha_empilhar(pilha, vetor[0]);
   // pilha_print(pilha);
   // pilha_empilhar(pilha, vetor[1]);
   // pilha_print(pilha);
   // pilha_empilhar(pilha, vetor[2]);
   // pilha_print(pilha);
   // pilha_empilhar(pilha, vetor[3]);
   // pilha_print(pilha);
   // pilha_empilhar(pilha, cidadeOrigem);
   // pilha_print(pilha);

   // pilha_apagar(pilha);

   matriz_apagar(&matriz_distancias, n_cidades);
   item_apagar(&cidadeOrigem);
   //pilha_apagar(&melhorTrajeto);
   vetor_apagar(vetor, tamanhoVetor);

   return EXIT_SUCCESS;
}