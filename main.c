/*

Alunos: Henrique S. Marques (11815722), Lucas Greff Meneses (13671615), João Gabriel Manfré Nazar (13733652)
Trabalho 1 - PCV
Professor: Marcelo Manzato

*/


#include <stdio.h>
#include <stdlib.h>

#include "Includes/pcv.h"

int main() {
   int quantidadeCidades, origem; //variaveis que armazenam a quantidade de cidades e o id da cidade de origem
   scanf("%i %i", &quantidadeCidades, &origem);

   //leitura da matriz de distancias
   float** matrizDistancias = ler_matriz_distancias(quantidadeCidades);

   //criacao da estrutura da cidade de origem
   cidade_t* cidadeOrigem = cidade_criar(origem, quantidadeCidades, matrizDistancias);

   //criacao do vetor com as cidades-destino
   cidade_t** cidadesDestino = criar_vetor_cidades_destino(matrizDistancias, quantidadeCidades, origem);

   //criação da lista que armazena o melhor trajeto e calculo dele
   list_t* melhorTrajeto = calcular_melhor_trajeto(cidadesDestino, cidadeOrigem, quantidadeCidades);

   //impressão do melhor trajeto e da sua distancia
   lista_imprimir(melhorTrajeto);

   //desalocações e finalização do programa
   matriz_apagar(&matrizDistancias, quantidadeCidades);
   cidade_apagar(&cidadeOrigem);
   apagar_cidades_destino(cidadesDestino, quantidadeCidades);
   lista_apagar(&melhorTrajeto);

   return EXIT_SUCCESS;
}