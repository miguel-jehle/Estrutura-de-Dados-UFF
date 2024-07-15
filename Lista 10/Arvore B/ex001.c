//Retorne o sucessor de um elemento, caso ele seja o maior, retorne INT_MAX. int suc (TARVB* a, int elem);

#include "TARVB.c"
#include "limits.h"

void percorre(TARVB* a, int elem, int* resp){
  if(!a) return;
  int i = 0;
  while(i < a->nchaves){
    percorre(a->filho[i],elem,resp);
    if(a->chave[i] > elem && a->chave[i] < *resp) *resp = a->chave[i];
    i++;
  }
  percorre(a->filho[i],elem,resp);
  return;
}

int suc (TARVB* a, int elem){
    int resp = INT_MAX;
    percorre(a,elem,&resp);
    return resp;
}

int main(void){
  TARVB *arvore = TARVB_Inicializa();
  int t, x;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      scanf("%d", &from);
      arvore = TARVB_Retira(arvore, from, t);
      TARVB_Imprime(arvore);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime(arvore);
      break;
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime(arvore);
    }
    else arvore = TARVB_Insere(arvore, num, t);
    printf("\n\n");
  }
  printf("Digite o valor ao qual voce quer o sucessor: ");
  scanf("%d", &x);
  int resp = suc(arvore,x);
  printf("O sucessor de %d eh %d\n",x, resp);
  TARVB_Libera(arvore);
  return 0;
}