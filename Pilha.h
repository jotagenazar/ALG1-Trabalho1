#ifndef _PILHA_H
#define _PILHA_H

  #include "item.h"
  #include <stdbool.h>

  #define TAM 150

  typedef struct pilha PILHA;

  PILHA *pilha_criar(void);
  void pilha_apagar(PILHA **pilha);
  bool pilha_vazia(PILHA *pilha);
  bool pilha_cheia(PILHA *pilha, int n_cidades);
  int pilha_tamanho(PILHA *pilha);
  ITEM *pilha_topo(PILHA *pilha);
  bool pilha_empilhar(PILHA *pilha, ITEM *item);
  ITEM *pilha_desempilhar(PILHA *pilha);
  float pilha_get_distancia(PILHA* pilha);
  void pilha_set_distancia(PILHA* pilha, float distancia);
  void pilha_print(PILHA *pilha);
  void pilha_set_topo(PILHA* pilha, ITEM* novo_topo);
  int pilha_get_tamanho(PILHA* pilha);

#endif 
