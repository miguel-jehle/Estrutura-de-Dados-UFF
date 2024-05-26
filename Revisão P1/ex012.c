//Percorra umas TAB e retorne uma lista ordenada com os valores maiores que m e menores que n, sem ordenação

#include"TLSE.c"
#include"TAB.c"
#include<string.h>

TLSE* insere_ordenado(TLSE* l, int x);
TLSE* percorre(TAB* a, int m, int n, TLSE* l);
TLSE* arv2listamn(TAB* a, int m, int n);

TLSE* arv2listamn(TAB* a, int m, int n){
    if(!a) return NULL;
    TLSE* l = NULL;
    l = percorre(a,m,n,l);
    return l;
}

TLSE* percorre(TAB* a, int m, int n, TLSE* l){
    if(!a) return l;
    if((a->info > m) && (a->info < n)) l = insere_ordenado(l,a->info);
    l = percorre(a->esq,m,n,l);
    l = percorre(a->dir,m,n,l);
    return l;
}

TLSE* insere_ordenado(TLSE* l, int x){
    if(!l || l->info > x) return TLSE_insere(l,x);
    l->prox = insere_ordenado(l->prox,x);
    return l;
}

int main(void){
  int no, pai,x,n,m;
  TLSE* lista = NULL;
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
  printf("Insira o limite inferior: ");
  scanf("%d", &m);
  printf("Insira o limite superior: ");
  scanf("%d", &n);
  TAB_imp_ident(a);
  lista = arv2listamn(a,m,n);
  TLSE_imp_rec(lista);
  printf("\n");
  
  TAB_libera(a);
  return 0;
}