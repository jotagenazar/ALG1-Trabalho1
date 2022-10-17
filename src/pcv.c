#include <stdio.h>
#include <stdlib.h>

#include "../Includes/pcv.h"

//os indices da matriz de distancia correspondem ao id - 1 de cada cidade 

float** ler_matriz_distancias(int quantidadeCidades) { //função que aloca e lê a matriz de distancias entre as cidades inserida pelo usuário com base no numero de cidades passado
    //alocação das linhas da matriz
    float** matriz = (float**)malloc(quantidadeCidades * sizeof(float*));
    if(matriz == NULL) return NULL;

    for(int i = 0; i < quantidadeCidades; ++i) { //alocacão de cada coluna referente às linhas criadas da matriz
        matriz[i] = (float*)malloc(quantidadeCidades * sizeof(float));

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
    for(int i = 0; i < quantidadeCidades; i++) {
        for(int j = 0; j < quantidadeCidades; j++) {
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

void matriz_apagar(float*** matrizDistancias, int quantidadeCidades) { //procedimento que apaga a matriz de distancias passada
    if(matrizDistancias == NULL || *matrizDistancias == NULL) return; //se o ponteiro é nulo, não há o que desalocar

    //para cada linha da matriz, sua coluna é desalocada
    for(int i = 0; i < quantidadeCidades; ++i) {
        free((*matrizDistancias)[i]);
    }
    //desalocação do array de linhas da matriz
    free(*matrizDistancias);

    *matrizDistancias = NULL;
}

cidade_t** criar_vetor_cidades_destino(float** matrizDistancias, int quantidadeCidades, int origem)
{
   //criacao do array que armazena as cidades até as quais será realizada uma viagem
   cidade_t** cidadesDestino = (cidade_t**)malloc((quantidadeCidades - 1)*sizeof(cidade_t*));
   if(cidadesDestino == NULL){
      exit(1);
   }

   //criacao de cada cidade de destino e armazenamento no array de cidades de destino
   int j = 0;
   for(int i = 0; i < quantidadeCidades; ++i) {
      if(i != (origem - 1)) {
         cidadesDestino[j] = cidade_criar(i + 1, quantidadeCidades, matrizDistancias);
         j++;
      }
   }

   return cidadesDestino;
}

void apagar_cidades_destino(cidade_t** cidadesDestino, int quantidadeCidades)
{
   for(int i = 0; i < quantidadeCidades - 1; ++i) { //laço para cada cidade de destino
	   cidade_apagar(&cidadesDestino[i]);
   }
   free(cidadesDestino);
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

    if (k == 1) //condicao de parada da recursao, terminada uma permutacao 
    {
        //criacao da lista e insercao da cidade de origem
        list_t* listaAtual = lista_criar();
        lista_inserir(listaAtual, cidadeOrigem);

        float melhorDistancia = lista_get_distancia(*melhorLista); 
        float distanciaAtual;

        //insercao da permutacao na lista
        for(int i = 0; i < tam; i++)
        {
            if(lista_inserir(listaAtual, cidadesDestino[i])) 
            {
                distanciaAtual = lista_get_distancia(listaAtual);
                // Caso a distância atual seja maior que a melhorDistancia, passamos para a próxima recursão
                if((distanciaAtual > melhorDistancia) && (melhorDistancia != 0))
                {
                    lista_apagar(&listaAtual);
                    return;
                }
            }
            else 
            {
                lista_apagar(&listaAtual);
                return;
            }
        }

        //insercao do fim do trajeto, retorno à cidade de origem
        if(lista_inserir(listaAtual, cidadeOrigem)) 
        {
            distanciaAtual = lista_get_distancia(listaAtual);
            // Caso a distância atual seja maior que a melhorDistancia, passamos para a próxima recursão
            if((distanciaAtual > melhorDistancia) && (melhorDistancia != 0))
            {
                lista_apagar(&listaAtual);
                return;
            }
        }
        else
        {
            lista_apagar(&listaAtual);
            return;
        }

        if(melhorDistancia == 0)
        {
            lista_apagar(melhorLista);
            *melhorLista = listaAtual; 

            return;           
        }
        // Se as distancias forem iguais, a lista crescente é a escolhida
        if(distanciaAtual == melhorDistancia) 
        {
            if(cidade_get_cidade_id(cidadesDestino[0]) < cidade_get_cidade_id(cidadesDestino[tam - 1]))
            {
                lista_apagar(melhorLista);
                *melhorLista = listaAtual; 
                return;              
            } 
            else 
            {
                lista_apagar(&listaAtual);
                return;
            }
        }

        // Caso nenhum dos casos acima tenham sido atingidos, trocamos a melhor lista pela atual
        lista_apagar(melhorLista);
        *melhorLista = listaAtual;
    }
}
                                //cidades a serem visitadas  //cidade de origem    //quantidade de cidades
list_t* calcular_melhor_trajeto(cidade_t** cidadesDestino, cidade_t* cidadeOrigem, int quantidadeCidades) { //função que calcula o melhor trajeto com base na distancia por meio de permutacao
    list_t* melhorLista = lista_criar();    //alocação da lista onde será guardado o melhor caminho

    //permutacao do array de cidades a serem visitadas, será armazenada na lista melhorLista
    heap_permutacao(&melhorLista, cidadesDestino, cidadeOrigem, quantidadeCidades - 1, quantidadeCidades - 1);
                                                                //k permutada  //tamanho total
    return melhorLista;
}