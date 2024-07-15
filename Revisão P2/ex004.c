//Fazendo um heapsort de forma decrescente de uma heap binária
#include<stdio.h>
#include<stdlib.h>

int esq(int ind){
    return 2*ind + 1; 
}

int dir(int ind){
    return 2*ind + 2;
}

int pai(int ind){
    if(ind > 0) return (ind - 1)/2;
    return -1;
}

void minheapfy(int* vet, int n, int ind){
    int e = esq(ind);
    int d = dir(ind);
    int menor = ind;

    if(e < n && vet[e] < vet[menor]) menor = e;
    if(d < n && vet[d] < vet[menor]) menor = d;

    if(ind != menor){
        int temp = vet[menor];
        vet[menor] = vet[ind];
        vet[ind] = temp;
        minheapfy(vet,n,menor);
    }
}

void build_min_heap(int* vet, int n){
    int ult_pai = pai(n-1);
    for(int i = ult_pai; i >= 0; i--){
        minheapfy(vet,n,i);
    }
}

void heapsort(int* vet, int n){
    build_min_heap(vet,n);
    for(int i = n-1; i > 0; i--){
        int temp = vet[0];
        vet[0] = vet[i];
        vet[i] = temp;
        minheapfy(vet,i,0);
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

