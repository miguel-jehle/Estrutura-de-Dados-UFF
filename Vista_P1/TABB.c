#include "TABB.h"

void TABB_libera(TABB* t){
  if(t){
    TABB_libera(t->esq);
    TABB_libera(t->dir);
    free(t);
  }
}

TABB* TABB_busca(int e, TABB* t){
  if(!t) return NULL;
  if(e < t->info) return TABB_busca(e, t->esq);
  if(e > t->info) return TABB_busca(e, t->dir);
  return t;
}

void imprime_aux(TABB* a, int andar){
  if(a){
    int j;
    imprime_aux(a->esq, andar + 1);
    for(j = 0; j <= andar; j++) printf("   ");
    printf("%d\n", a->info);
    imprime_aux(a->dir, andar + 1);
  }
}

void TABB_imprime(TABB* a){
  imprime_aux(a, 1);
}

TABB* TABB_cria(int x, TABB* e, TABB* d){
  TABB* a = (TABB*) malloc(sizeof(TABB));
  a->info = x;
  a->esq = e;
  a->dir = d;
  return a;
}

TABB* TABB_insere(int e, TABB* t){
  if(!t) t = TABB_cria(e, NULL, NULL);
  else if(e < t->info) t->esq = TABB_insere(e, t->esq);
  else if(e > t->info) t->dir = TABB_insere(e, t->dir);
  return t;
}

TABB* TABB_retira(int e, TABB *t){
  if(!t) return t;
  else if(e < t->info) t->esq = TABB_retira(e, t->esq);
  else if(e > t->info) t->dir = TABB_retira(e, t->dir);
  else{
    if((!t->esq) && (!t->dir)){
      free(t);
      t = NULL;
    }
    else if((!t->esq) || (!t->dir)){
      TABB *q = t;
      if(!t->dir) t = t->esq;
      else t = t->dir;
      free(q); 
    }
    else{
      TABB *f = t->esq;
      while(f->dir) f = f->dir;
      t->info = f->info;
      f->info = e;
      t->esq = TABB_retira(e, t->esq);
    }
  }
  return t;  
}
