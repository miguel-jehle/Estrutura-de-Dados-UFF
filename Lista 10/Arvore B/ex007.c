//quantidade de nós folha: int nf(TARVB *a);

#include "TARVB.c"

int nf(TARVB *a){
    if(!a) return 0;
    int i = 0;
    int cont = 0;
    if(a->folha) cont++;
    while(i < a->nchaves){
        cont+= nf(a->filho[i]);
        i++;
    }
    cont += nf(a->filho[i]);
    return cont;
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
    int resp = nf(arvore);
    printf("o numero de nos internos da arvore eh: %d\n",resp);
    TARVB_Imprime(arvore);
    TARVB_Libera(arvore);
    return 0;
}