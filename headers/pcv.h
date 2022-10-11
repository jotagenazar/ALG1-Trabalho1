#ifndef PCV_H
#define PCV_H

#include "lista.h"

float** ler_matriz_distancias(int n_cidades);

list_t* calcular_melhor_trajeto(cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int n_cidades);

void matriz_apagar(float*** matriz_distancias, int n_cidades);

#endif