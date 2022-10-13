#ifndef CIDADE_H
    #define CIDADE_H
        
    #include <stdbool.h>

    typedef struct cidade { //estrutura de dados referente às cidades a serem inseridas pelo usuário
        int cidade_id; //registra o id da cidade
        float *distancias; //array que guarda a distância dessa cidade à cidade cujo (id - 1) é a posição da distancia no array
    } cidade_t;

    cidade_t *cidade_criar(int cidade, int n_cidades, float** matriz_distancias);//função que aloca e preenche uma cidade e seu vetor de distâncias, retorna o endereço da cidade
    bool cidade_apagar(cidade_t **cidade);//funcao que apaga a cidade passada
    
    int cidade_get_cidade_id(cidade_t *cidade); //função que retorna o id da cidade passada
    float* cidade_get_distancias(cidade_t *cidade); //função que retorna o array de distancias da cidade passada

#endif