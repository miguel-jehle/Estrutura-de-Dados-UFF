#include "TABB.h"

int tam(TABB* a);
int ver(TABB* a, int nivel, int altura);
int maior(int x, int y);

int teste(TABB *a){
  if(!a) return 0;
  int nivel = 0;
  int t = tam(a); //Adiciono o cálculo do tamanho
  return ver(a,nivel,t); //Passei o tamanho da árvore como parâmetro para verificar
}

int ver(TABB* a, int n, int altura){
  if(!a) return 1;
  int resp = 1;
  if(n % 3 == 0){
    if((!a->esq && a->dir) || (a->esq && !a->dir))  resp = 0;
  }
  if(n % 3 == 1){
    if((!a->esq) || (a->dir)) resp = 0;
   }
   if(n % 3 == 2){
    if((!a->dir) || (a->esq)) resp = 0;
   }
   //Condição criada para verificar se todas as folhas estão na mesma altura
   if((!a->esq) && (!a->dir) && (n!=altura)) resp = 0; 
   if(!resp) return 0;
   return ver(a->esq,n+1,altura) && ver(a->dir,n+1,altura);
}

int tam(TABB* a){ //Função criada para cálculo da altura
  if(!a) return -1;
  return maior(tam(a->esq),tam(a->dir)) + 1;
}

int maior(int x, int y){
  if( x > y) return x;
  return y;
}



int main(void){
  int n;
  TABB *resp = NULL;
  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    resp = TABB_insere(n, resp);
  }
  TABB_imprime(resp);
  printf("Segue o padrao? %d\n", teste(resp));
  TABB_libera(resp);
  return 0;
}

