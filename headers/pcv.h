#ifndef PCV_H
    #define PCV_H

    #include "lista.h"

    float** ler_matriz_distancias(int n_cidades); //função que aloca e lê a matriz de distancias entre as cidades inserida pelo usuário com base no numero de cidades passado
    void matriz_apagar(float*** matriz_distancias, int n_cidades); //procedimento que apaga a matriz de distancias passada

    list_t* calcular_melhor_trajeto(cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int n_cidades);

#endif