#ifndef PCV_H
	#define PCV_H
	
	#include <stdbool.h>
	#include "item.h"
	#include "Pilha.h"

	float** ler_matriz_distancias(int n_cidades);
	void matriz_apagar(float*** matriz_distancias, int n_cidades);
	void troca(ITEM **a, int i, int j);
    void print_vetor(int *vetor, int n);
    PILHA* calcular_melhor_trajeto(ITEM** vetor, int tam, ITEM* inicio);

#endif