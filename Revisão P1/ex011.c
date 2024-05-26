//Verifique se uma TAB eh também uma TABB.

#include"TAB.c"
#include"string.h"

int ver_TABB(TAB* a){
    if(!a) return 1;
    if((a->esq) && ((a->info) < (a->esq->info))) return 0;
    if((a->dir) && ((a->info) > (a->dir->info))) return 0;
    return ver_TABB(a->esq) && ver_TABB(a->dir);
}

int main(void){
  int no, pai,x;
  printf("Digite a raiz da arvore... ");
  scanf("%d", &no);
  TAB *a = TAB_cria(no, NULL, NULL), *resp;
  char repete;
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido na arvore e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a, pai);
    if(!resp){
      TAB_libera(a);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a);
  x = ver_TABB(a);
  if(!x) printf("NAO eh TABB");
  else printf("Eh TABB");
  printf("\n");
  
  TAB_libera(a);
  return 0;
}
