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

typedef struct triangulo{
  int base, altura;
}TT;

typedef struct retangulo{
  int base, altura;
}TR;

typedef struct trapezio{
  int base_menor, base_maior, altura;
}TTP;

TABBG *TABBG_inicializa(void){
  return NULL;
}

TQ* cria_quadrado(int lado){
  TQ* novo = (TQ*)malloc(sizeof(TQ));
  novo->lado = lado;
  return novo;
}

TT* cria_triangulo(int base, int altura){
  TT* novo = (TT*) malloc(sizeof(TT));
  novo->base = base;
  novo->altura = altura;
  return novo;
}

TR* cria_retangulo(int base, int altura){
  TR* novo = (TR*) malloc(sizeof(TR));
  novo->base = base;
  novo->altura = altura;
  return novo;
}

TTP* cria_trapezio(int base,int Base, int altura){
  TTP* novo = (TTP*)malloc(sizeof(TTP));
  novo->base_menor = base;
  novo->altura = altura;
  novo->base_maior = Base;
  return novo;
}

TABBG* cria_no(int id){
  TABBG* novo = (TABBG*)malloc(sizeof(TABBG));
  if(id == QUADRADO){
    int lado;
    printf("Digite o lado do quadrado: ");
    scanf("%d",&lado);
    novo->forma = cria_quadrado(lado);
    novo->area = lado*lado;
  }
  if(id == RETANGULO){
    int base, altura;
     
  }
  

  
}





