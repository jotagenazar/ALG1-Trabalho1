#ifndef LISTA_H
    #define LISTA_H

    #include <stdbool.h>
    #include "cidade.h"

    typedef struct list list_t; //estrutura de dados referente à lista que armazena os nós com as cidades

    list_t* lista_criar(); //função que cria e aloca uma lista e retorna seu endereço
    void lista_apagar(list_t** list); //procedimento que desaloca a lista passada e cada um de seus nós

    bool lista_vazia(list_t* list); //função que checa se a lista esta vazia
    bool lista_inserir(list_t* list, cidade_t* x); //função que cria um novo nó com a cidade passada e o insere na ultima posição. se o caminho criado é possível, retorna verdadeiro; se impossível, retorna falso
    
    float lista_get_distancia(list_t* list); //funcao que retorna a distancia total entre as cidades armazenadas na lista passada
    
    void lista_imprimir(list_t* list); //procedimento que imprime cada cidade da lista passada como parametro

#endif //LISTA_H