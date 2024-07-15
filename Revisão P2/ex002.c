//Percorra uma Árvore B e retorne um vetor que contenha todos os valores entre mn em ordem crescente!

#include "TARVBM.c"

int* preenche(TARVBM* a, int m, int n, int* vet, int* ind){
    if(!a) return vet;
    int i = 0;
    if(!a->folha){
        while(i < a->nchaves && a->chave[i] < m) i++;
        vet = preenche(a->filho[i], m,n,vet,ind);
    }
    if(a->folha){
        while(i < a->nchaves){
            if(m < a->chave[i] && a->chave[i] < n) vet[(*ind)++] = a->chave[i];
            i++;
        }
        vet = preenche(a->prox,m,n,vet,ind);
    }
    return vet;
}

int tam(TARVBM* a, int m, int n){
    if(!a) return 0;
    int cont = 0, i = 0;
    if(!a->folha){
        while(i < a->nchaves && a->chave[i] < m) i++;
        cont += tam(a->filho[i], m,n);
    }
    if(a->folha){
        while(i < a->nchaves){
            if(m < a->chave[i] && a->chave[i] < n) cont ++;
            i++;
        }
        cont += tam(a->prox,m,n);
    }
    return cont;
}

int* mn(TARVBM* a, int m, int n){
    if(!a) return NULL;
    int t = tam(a,m,n);
    printf("TAMANHO: %d", t);
    int* vet = (int*)malloc(sizeof(int)*t);
    int ind = 0;
    vet = preenche(a,m,n,vet,&ind);
    return vet;
}

int main(void){
  TARVBM *arvore = TARVBM_inicializa();
  int t, x,y;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      scanf("%d", &from);
      arvore = TARVBM_retira(arvore, from, t);
      TARVBM_imprime(arvore);
    }
    else if(num == -1){
      printf("\n");
      TARVBM_imprime(arvore);
      break;
    }
    else if(!num){
      printf("\n");
      TARVBM_imprime(arvore);
    }
    else arvore = TARVBM_insere(arvore, num, t);
    printf("\n\n");
  }
  printf("Digite o limite inferior 'm': ");
  scanf("%d",&x);
  printf("Digite o limite superior 'n': ");
  scanf("%d",&y);
  int* vet = mn(arvore,x,y);
  int tamanho = tam(arvore,x,y);
  printf("Os valores contidos entre m e n em ordem crescente são: ");
  for(int i = 0; i < tamanho; i++) printf("%d ", vet[i]);
  free(vet);
  TARVBM_libera(arvore);
  return 0;
}