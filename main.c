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

   int tamanhoVetor = n_cidades - 1;
   ITEM** vetor = vetor_criar(n_cidades, indexOrigem, matriz_distancias);
   
   ITEM* cidadeOrigem = item_criar(origem, n_cidades);

   PILHA* melhorTrajeto = calcular_melhor_trajeto(vetor, tamanhoVetor, cidadeOrigem);
   
   float melhorDistancia = pilha_get_distancia(melhorTrajeto);

   printf("DISTANCIA: %.2f\n", melhorDistancia);

   matriz_apagar(&matriz_distancias, n_cidades);
   item_apagar(&cidadeOrigem);
   pilha_apagar(&melhorTrajeto);
   vetor_apagar(vetor, n_cidades);

   return EXIT_SUCCESS;
}