#include<stdio.h>
#include<stdlib.h>

#define QUADRADO 1
#define TRIANGULO 2
#define RETANGULO 3
#define TRAPEZIO 4

typedef struct TABB_geo{
    int id,area;
    struct TABB_geo* esq; *dir;
    void* forma;
}TABBG;

typedef struct quadrado{
    int lado;
}TQ;

TABBG *TABBG_cria_quadrado(int lado){
  TABBG *novo = (TABBG *) malloc(sizeof(TABBG));
  novo->forma = (TQ*)malloc(sizeof(TQ));
  novo->forma->lado = lado;
  novo->area = lado*lado;
  novo->id = QUADRADO;
  novo->esq = NULL;
  novo->dir = NULL;
  (*(novo->forma))->lado = 2;
  return novo;
}

TABBG *TABBG_inicializa(void){
  return NULL;
}
TABBG *TABBG_cria_triangulo(int base, int altura){
  TABBG *novo = (TABBG *) malloc(sizeof(TABBG));
  novo->base = base;
  novo->altura = altura;
  novo->area = (base*altura)/2;
  novo->id = TRIANGULO;
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}

TABBG *TABBG_cria_retangulo(int base, int altura){
  TABBG *novo = (TABBG *) malloc(sizeof(TABBG));
  novo->base = base;
  novo->altura = altura;
  novo->area = (base*altura);
  novo->id = RETANGULO;
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}

TABBG *TABBG_cria_trapezio(int base,int Base, int altura){
  TABBG *novo = (TABBG *) malloc(sizeof(TABBG));
  novo->base = base;
  novo->altura = altura;
  novo->Base = Base;
  novo->area = ((base+Base)*altura)/2;
  novo->id = TRAPEZIO;
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}





