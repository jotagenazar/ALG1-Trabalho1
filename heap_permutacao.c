#include <stdio.h>
#include <stdlib.h>

int qtd = 0;

//1 2 3 4 5 6
//0 1 2 3 4 5

void reverse(int* vetor, int ini, int fim){
    //O fim seria o tamanho do vetor;
    int tam_novo = fim - ini;
    int aux[tam_novo];
    int k = 0;

    for(int i = fim - 1; i >= ini; i--){
        aux[k] = vetor[i];
        k++;
    }
    k = 0;
    for(int i = ini; i < fim; i++){
        vetor[i] = aux[k];
        k++;
    }
}

void troca(int *a, int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void print_vetor(int *vetor, int n){
    for(int i = 0; i < n; i++){
        printf("%i ", vetor[i]);
    }
    printf("\n");
}

void heap_permutacao(int *vetor, int parte, int tam){
    //Time Complexity: O(N*N!)
    //Auxiliary Space: O(N)

    if (parte == 1) {
        qtd++;
        print_vetor(vetor, tam);
        return;
    }
 
    for (int i = 0; i < parte; i++) {
        heap_permutacao(vetor, parte - 1, tam);

        if (parte % 2 == 1){
            //printf("TROCA: 0 e %i\n", parte - 1);
            troca(vetor, 0, parte - 1);
        }
        else{
            //printf("TROCA: %i e %i\n", i, parte - 1);
            troca(vetor, i, parte-1);
        }
    }
}

void permutacao(int *vetor, int tam){
    if(qtd <= 24){
        int x = -1, y = -1;
        qtd++;
        print_vetor(vetor, tam);
        //Procurando o maior x:
        for(int i =0; i < tam; i++){
            if(vetor[i] < vetor[i+1]){
                x = i;
            }
        }

        //Procurando o maior y:
        for(int i = 0; i < tam; i++){
            if(vetor[x] < vetor[i]){
                y = i;
            }
        }

        troca(vetor, x, y);
        reverse(vetor, x + 1, tam);
        permutacao(vetor, tam);
    }
}

int main(void){
    int tam = 5;
    int vetor[5] = {1,2,3,4,5};

    heap_permutacao(vetor, tam, tam);
    printf("TOTAL: %i \n", qtd);

    // reverse(vetor, 1, 4);
    // print_vetor(vetor, tam);

    // permutacao(vetor, tam);

    return 0;
}