#ifndef ITEM_H
	#define ITEM_H
	
	#include <stdbool.h>

	typedef struct item_ ITEM;

	ITEM *item_criar(int cidade, int n_cidades);
	bool item_apagar(ITEM **item);
	void item_imprimir(ITEM *item);
	int item_get_chave(ITEM *item);
	bool item_set_chave(ITEM *item, int chave);
	ITEM* item_get_anterior(ITEM* item);
	bool item_set_anterior(ITEM* item, ITEM* anterior);
	float item_get_distancia(ITEM* item);
	ITEM** vetor_criar(int n_cidades, int index_origem, float** matriz_distancias);
	bool vetor_apagar(ITEM** vetor, int n_cidades);
	bool item_set_distancia(ITEM* item, int cidade, float dist);
	void print_vetor_itens(ITEM** vetor, int n_cidades);

#endif
