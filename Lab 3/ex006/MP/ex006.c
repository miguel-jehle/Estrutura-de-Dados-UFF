/*
(Q6) Refaça as bibliotecas de heap para funcionar com heaps ternárias. Assim, no lugar de termos funções de esquerda e direita, teremos funções que retornam os três possíveis filhos de um nó (isto é, escreva as funções filho_1, filho_2 e filho3).
*/

#include <stdio.h>
#include <stdlib.h>

int filho_1(int ind){
    return (3*ind + 1);
}

int filho_2(int ind){
    return (3*ind + 2);
}

int filho_3(int ind){
    return (3*ind + 3);
}

int pai(int ind){
    if(ind > 0) return (ind-1)/3;
    return -1;
}

void maxheapfy(int* vet, int n, int ind){
    int f1 = filho_1(ind);
    int f2 = filho_2(ind);
    int f3 = filho_3(ind);
    int maior = ind;
    if(f1 < n && vet[f1] > vet[maior]) maior = f1;
    if(f2 < n && vet[f2] > vet[maior]) maior = f2;
    if(f3 < n && vet[f3] > vet[maior]) maior = f3;
    if(maior != ind){
        int temp = vet[ind];
        vet[ind] = vet[maior];
        vet[maior] = temp;
        maxheapfy(vet, n, maior);
    }
}

void build_max_heap(int *vet, int n){
    int ult_pai = pai(n-1);
    for(int i = ult_pai; i >= 0; i--){
        maxheapfy(vet,n,i);
    }
}

void heapsort(int *vet, int n){
    build_max_heap(vet,n);
    for(int i = n-1; i > 0; i--){
        int temp = vet[0];
        vet[0] = vet[i];
        vet[i] = temp;
        maxheapfy(vet,i,0);
    }
}

int main(void){
  int *vet, n, i = 0;
  printf("Digite o tamanho do vetor de elementos a serem ordenados... ");
  scanf("%d",&n);
  if(n <= 0) return 0;
  vet = (int *) malloc(sizeof(int) * n);

  for(i = 0; i < n; i++) vet[i] = rand() % n;
 
  printf("Antes de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  heapsort(vet, n);

  printf("Depois de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  free(vet);
  return 0;
}