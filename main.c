#include <stdio.h>
#include <stdlib.h>

#include "headers/pcv.h"

int main()
{
   int quantidadeCidades, origem;

   scanf("%i %i", &quantidadeCidades, &origem);

   float** matriz_distancias = ler_matriz_distancias(quantidadeCidades);

   cidade_t* cidadeOrigem = cidade_criar(origem, quantidadeCidades, matriz_distancias);

   cidade_t** cidadesDestino = (cidade_t**)malloc((quantidadeCidades - 1)*sizeof(cidade_t*));
   if(cidadesDestino == NULL)
   {
      exit(1);
   }

   int j = 0;
   for(int i = 0; i < quantidadeCidades; ++i)
   {
      if(i != (origem - 1))
      {
         cidadesDestino[j] = cidade_criar(i + 1, quantidadeCidades, matriz_distancias);
         j++;
      }
   }

   list_t* melhorTrajeto = calcular_melhor_trajeto(cidadesDestino, cidadeOrigem, quantidadeCidades);


   float melhorDistancia = lista_get_distancia(melhorTrajeto);

   printf("Melhor trajeto: ");
   lista_imprimir(melhorTrajeto);
   printf("Melhor distância: %.2f\n", melhorDistancia);

   matriz_apagar(&matriz_distancias, quantidadeCidades);

   cidade_apagar(&cidadeOrigem);
   for(int i = 0; i < quantidadeCidades - 1; ++i)
   {
	cidade_apagar(&cidadesDestino[i]);
   }
   free(cidadesDestino);

   lista_apagar(&melhorTrajeto);
   

   return EXIT_SUCCESS;
}