#include <stdio.h>
#include <stdlib.h>

#include "headers/pcv.h"

int main() {
   int quantidadeCidades, origem; //variaveis que armazenam a quantidade de cidades e o id da cidade de origem
   scanf("%i %i", &quantidadeCidades, &origem);

   //leitura da matriz de distancias
   float** matriz_distancias = ler_matriz_distancias(quantidadeCidades);

   //criacao da estrutura da cidade de origem
   cidade_t* cidadeOrigem = cidade_criar(origem, quantidadeCidades, matriz_distancias);

   //criacao do array que armazena as cidades até as quais será realizada uma viagem
   cidade_t** cidadesDestino = (cidade_t**)malloc((quantidadeCidades - 1)*sizeof(cidade_t*));
   if(cidadesDestino == NULL){
      exit(1);
   }

   //criacao de cada cidade de destino e armazenamento no array de cidades de destino
   int j = 0;
   for(int i = 0; i < quantidadeCidades; ++i) {
      if(i != (origem - 1)) {
         cidadesDestino[j] = cidade_criar(i + 1, quantidadeCidades, matriz_distancias);
         j++;
      }
   }

   //criação da lista que armazena o melhor trajeto e calculo dele
   list_t* melhorTrajeto = calcular_melhor_trajeto(cidadesDestino, cidadeOrigem, quantidadeCidades);

   //criacao da variavel que armazena a distancia total da lista de melhor trajeto
   float melhorDistancia = lista_get_distancia(melhorTrajeto);

   //impressão do melhor trajeto e da sua distancia
   printf("Melhor trajeto: ");
   lista_imprimir(melhorTrajeto);
   printf("Melhor distância: %.2f\n", melhorDistancia);

   //desalocações e finalização do programa
   matriz_apagar(&matriz_distancias, quantidadeCidades);
   cidade_apagar(&cidadeOrigem);
   for(int i = 0; i < quantidadeCidades - 1; ++i) { //laço para cada cidade de destino
	   cidade_apagar(&cidadesDestino[i]);
   }
   free(cidadesDestino);
   lista_apagar(&melhorTrajeto);

   return EXIT_SUCCESS;
}