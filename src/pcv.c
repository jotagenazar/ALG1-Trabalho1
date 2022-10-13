#include <stdio.h>
#include <stdlib.h>

#include "../Includes/pcv.h"

//os indices da matriz de distancia correspondem ao id - 1 de cada cidade 

float** ler_matriz_distancias(int n_cidades) { //função que aloca e lê a matriz de distancias entre as cidades inserida pelo usuário com base no numero de cidades passado
    //alocação das linhas da matriz
    float** matriz = (float**)malloc(n_cidades * sizeof(float*));
    if(matriz == NULL) return NULL;

    for(int i = 0; i < n_cidades; ++i) { //alocacão de cada coluna referente às linhas criadas da matriz
        matriz[i] = (float*)malloc(n_cidades * sizeof(float));

        //caso a alocação falhe
        if(matriz[i] == NULL) {
            for(int j = 0; j < i; ++j) {
                free(matriz[i]);
            }

            free(matriz);

            return NULL;
        }
    }

    //preenchimento inicial da matriz para limpeza
    for(int i = 0; i < n_cidades; i++) {
        for(int j = 0; j < n_cidades; j++) {
            matriz[i][j] = -1;
        }
    }

    //leitura das distancias e preenchimento real da matriz
    int a, b;
    float distancia;
    while(scanf("%i %i %f", &a, &b, &distancia) != EOF) { //leitura de cada linha até o fim da entrada
        matriz[a-1][b-1] = distancia; //preenche a posicao referente à linha em 'a' e coluna em 'b'    
        matriz[b-1][a-1] = distancia; //preenche a posicao referente à linha em 'b' e coluna em 'a'    
    }

    return matriz; //retorno da matriz alocada
}

void matriz_apagar(float*** matriz_distancias, int n_cidades) { //procedimento que apaga a matriz de distancias passada
    if(matriz_distancias == NULL || *matriz_distancias == NULL) return; //se o ponteiro é nulo, não há o que desalocar

    //para cada linha da matriz, sua coluna é desalocada
    for(int i = 0; i < n_cidades; ++i) {
        free((*matriz_distancias)[i]);
    }
    //desalocação do array de linhas da matriz
    free(*matriz_distancias);

    *matriz_distancias = NULL;
}

void troca(cidade_t** a, int i, int j) { //procedimento que troca duas cidades num array de cidades com base nos seus indices
  cidade_t* temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

                                                                                                                    
void heap_permutacao(list_t** melhorLista, cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int k, int tam) {
                                                                                            //elemento até o qual a permutacao ocorrera
                                                                                                        //tamanho total do array permutado
    for (int i = 0; i < k; i++) { //laco para calcular cada permutacao
        heap_permutacao(melhorLista, cidadesDestino, cidadeOrigem, k - 1, tam);


        if (k % 2 == 1){
            troca(cidadesDestino, 0, k - 1);
        }
        else{
            troca(cidadesDestino, i, k-1);
        }
    }

    if (k == 1) { //condicao de parada da recursao, terminada uma permutacao
        //criacao da lista e insercao da cidade de origem
        list_t* listaAtual = lista_criar();
        lista_inserir(listaAtual, cidadeOrigem);

        //insercao da permutacao na lista
        for(int i = 0; i < tam; i++) {
            if(!lista_inserir(listaAtual, cidadesDestino[i])) {
                lista_apagar(&listaAtual);
                return;
            }
        }

        //insercao do fim do trajeto, retorno à cidade de origem
        if(!lista_inserir(listaAtual, cidadeOrigem)) {
            lista_apagar(&listaAtual);
            return;
        }

        //calculo da distancia, avalia se a permutacao calculada possui distancia menor que a do melhor trajeto
        float distanciaAtual = lista_get_distancia(listaAtual);
        float melhorDistancia = lista_get_distancia(*melhorLista);

        if(melhorDistancia == 0 || distanciaAtual < melhorDistancia) { //caso a permutacao seja melhor
            lista_apagar(melhorLista);
            *melhorLista = listaAtual;
        } else if(distanciaAtual == melhorDistancia) { //se as distancias forem iguais, a lista crescente é a escolhida
            if(cidade_get_cidade_id(cidadesDestino[0]) < cidade_get_cidade_id(list_get_primeiro_destino(*melhorLista))) {
                lista_apagar(melhorLista);
                *melhorLista = listaAtual;               
            } else {
                lista_apagar(&listaAtual);
            }
        } else { //caso a melhor lista passada seja melhor que a permutacao atual
            lista_apagar(&listaAtual);
        }
    }
}
                                //cidades a serem visitadas  //cidade de origem    //quantidade de cidades
list_t* calcular_melhor_trajeto(cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int n_cidades) { //função que calcula o melhor trajeto com base na distancia por meio de permutacao
    list_t* melhorLista = lista_criar();    //alocação da lista onde será guardado o melhor caminho

    //permutacao do array de cidades a serem visitadas, será armazenada na lista melhorLista
    heap_permutacao(&melhorLista, cidadesDestino, cidadeOrigem, n_cidades - 1, n_cidades - 1);
                                                                //k permutada  //tamanho total
    return melhorLista;
}