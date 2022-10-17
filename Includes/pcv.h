#ifndef PCV_H
    #define PCV_H

    #include "lista.h"

    float** ler_matriz_distancias(int quantidadeCidades); //função que aloca e lê a matriz de distancias entre as cidades inserida pelo usuário com base no numero de cidades passado
    void matriz_apagar(float*** matrizDistancias, int quantidadeCidades); //procedimento que apaga a matriz de distancias passada

    cidade_t** criar_vetor_cidades_destino(float** matrizDistancias, int quantidadeCidades, int origem);
    void apagar_cidades_destino(cidade_t** cidadesDestino, int quantidadeCidades);

    list_t* calcular_melhor_trajeto(cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int n_cidades);

#endif