//Refaça as bibliotecas de heap para funcionar com heaps k-nárias. Assim, no lugar de termos funções de esquerda e direita, teremos funções que retornam os k possíveis filhos de um nó.

#include<stdio.h>
#include<stdlib.h>

int filho_i(int ind, int i, int k){ // retorna o iésimo filho
    return (k * ind + i);
}

int pai(int ind, int k){
    if(ind > 0) return (ind-1)/k;
    return -1;
}

void maxheapfy(int* vet, int n,int indice, int k){
    int maior = indice;
    for(int i = 0; i < k; i++){
        int filho = filho_i(indice,i,k);
        if(filho < n && vet[filho] > vet[maior]) maior = filho;
    }
    if(maior != indice){
        int temp = vet[indice];
        vet[indice] = vet[maior];
        vet[maior] = temp;
        maxheapfy(vet,n,maior,k); 
    }
}

void build_max_heap(int* vet, int n, int k){
    int ult_pai = pai(n-1,k);
    for(int i = ult_pai; i >= 0; i--){
        maxheapfy(vet,n,i,k);
    }
}

void heapsort(int* vet, int n, int k){
    build_max_heap(vet,n,k);
    for(int i = n-1; i >= 1; i--){
        int temp = vet[0];
        vet[0] = vet[i];
        vet[i] = temp;
        maxheapfy(vet,i,0,k);
    }
}

int main(void){
  int *vet, n, i = 0,k;
  printf("Digite o tamanho do vetor de elementos a serem ordenados... ");
  scanf("%d",&n);
  printf("Digite o tipo k-ésimo que a árvore será: ");
  scanf("%d",&k);
  if(n <= 0) return 0;
  vet = (int *) malloc(sizeof(int) * n);

  for(i = 0; i < n; i++) vet[i] = rand() % n;
 
  printf("Antes de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  heapsort(vet, n, k);

  printf("Depois de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  free(vet);
  return 0;
}