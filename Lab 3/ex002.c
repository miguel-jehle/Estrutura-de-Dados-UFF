/*
(Q2) Retornar todas as informações ancestrais de um nó na árvore B, da raiz da árvore até o elemento passado como parâmetro, usando a biblioteca de lista encadeada - TLSEINT* misc(TARVB *a, int elem), onde:
*/
#include "TLSEINT.c"
#include "TARVB.c"
#include <limits.h>

TLSEINT* percorre(TARVB* a,TLSEINT* l,int elem){
    if(!a) return l;
    int i = 0; // indice para descer
    while(i < a->nchaves && a->chave[i] < elem) i++;

    int j;
    int menor = elem;
    for(j = a->nchaves-1; j >= 0; j--){
        if(a->chave[j] < menor){
            menor = a->chave[j];
            break;
        }
    }
    if (menor == elem) menor = INT_MIN;

    int maior = elem;
    for(j = 0; j < a->nchaves; j++){
        if(a->chave[j] > maior){
            maior = a->chave[j];
            break;
        }
    }
    if(maior == elem) maior = INT_MAX;

    
    if(a->chave[i] == elem) {
      l = TLSEINT_insere(l,menor,maior);
      return l;
    } 
    l = percorre(a->filho[i],l,elem);
    l = TLSEINT_insere(l,menor,maior);
    return l;
}

TLSEINT* misc(TARVB *a, int elem){
    if(!a) return NULL;
    if(!TARVB_Busca(a,elem)) return NULL;
    TLSEINT* lista = NULL;
    lista = percorre(a,lista, elem);
    return lista;
}

int main(void){
  TARVB *arvore = TARVB_Inicializa();
  TLSEINT* lista = NULL;
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
  printf("Digite o valor n: ");
  scanf("%d", &x);
  lista = misc(arvore,x);
  printf("A lista eh: ");
  TLSEINT_imprime(lista);
  TLSEINT_libera(lista);
  TARVB_Libera(arvore);
  return 0;
}