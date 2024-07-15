#include "TARVB.h"

int* percorre(TARVB* a, int N, int M, int *vet, int* ind){
  if(!a) return vet;
  int i = 0;
  while(i < a->nchaves){
    vet = percorre(a->filho[i],N,M,vet,ind);
    if((a->chave[i] % N == 0) && (a->chave[i] % M == 0)) vet[(*ind)++] = a->chave[i];
    i++;
  }
  vet = percorre(a->filho[i],N,M,vet,ind);
  return vet;
}

int tam(TARVB* a, int N, int M){
  if(!a) return 0;
  int i = 0, cont = 0;
  while(i < a->nchaves){
    cont += tam(a->filho[i],N,M);
    if((a->chave[i]%N == 0) && (a->chave[i] % M == 0)) cont ++;
    i++;
  }
  cont += tam(a->filho[i],N,M);
  return cont;
}


int* mult_NM(TARVB *a, int N, int M, int *tam_vet){
  if(!a){
    *tam_vet = 0;
    return NULL;
  }
  (*tam_vet) = tam(a,N,M);
  int *vet = (int*)malloc(sizeof(int)*(*tam_vet));
  int ind = 0;
  vet = percorre(a,N,M,vet,&ind);
  return vet;
}

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  int t;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para realizar a operacao e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      printf("Digite n e m... ");
      int n, m, tam_vet = 0, i;
      scanf("%d%d", &n, &m);
      int *vet = NULL;
      vet = mult_NM(arvore, n, m, &tam_vet);
      for(i = 0; i < tam_vet; i++) printf("vet[%d] = %d\n", i, vet[i]);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime(arvore);
      TARVB_Libera(arvore);
      return 0;
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime(arvore);
    }
    else arvore = TARVB_Insere(arvore, num, t);
    printf("\n\n");
  }
}
