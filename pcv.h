#ifndef PCV_H
	#define PCV_H
	
	#include <stdbool.h>
	#include "item.h"
	#include "Pilha.h"

	void troca(ITEM **a, int i, int j);
    void print_vetor(int *vetor, int n);
    void heap_permutacao(PILHA* pilha,ITEM** vetor, int parte, int tam, ITEM* inicio);
	void print_qtd();

#endif