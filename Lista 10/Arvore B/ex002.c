//maior elemento da árvore: TARVB* maior(TARVB *a);
#include "TARVB.c"

TARVB* maior(TARVB *a){
    if(!a) return NULL;
    int i = 0;
    while(!a->folha){
        a = a->filho[a->nchaves];
    }
    return a;
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
    TARVB* resp = maior(arvore);
    printf("O maior elemento da arvore eh %d\n",resp->chave[resp->nchaves-1]);
    TARVB_Libera(arvore);
    return 0;
}