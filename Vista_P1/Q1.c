#include "TG.h"
#include "TLSE.h"

int ver_conect(TG* g, TLSE* JV){
    if(!JV) return 0;
    while(g){
        if(!TLSE_busca(JV,g->id_no)) return 0;
        g = g->prox_no;
    }
    return 1;
}

int ver_rep(TLSE* U, TLSE* V){
    if(!U || !V) return 0; //Adição desta condição para caso só exista um nó.
    while(U){
        if(TLSE_busca(V,U->info)) return 0;
        U = U->prox;
    }
    return 1;
}

void teste_aux(TG* g, TLSE** U, TLSE** V, TLSE**JV, int x){
    if(!g) return;
    TG* no = TG_busca_no(g,x);
    if(TLSE_busca((*JV),no->id_no)) return;
    if(!TLSE_busca((*U),no->id_no)) (*U) = TLSE_insere((*U),no->id_no);
    if(!TLSE_busca((*JV),no->id_no)) (*JV) = TLSE_insere((*JV),no->id_no);
    TVIZ* viz = no->prim_viz;

    while(viz){
        if(!TLSE_busca((*V),viz->id_viz)) (*V) = TLSE_insere((*V),viz->id_viz);
        viz = viz->prox_viz;
    }

    viz = no->prim_viz;
    while(viz){
        teste_aux(g,V,U,JV,viz->id_viz);
        viz = viz->prox_viz;
    }
    return;
}

int teste(TG* g){
    if(!g) return 0;
    TLSE* U = NULL;
    TLSE* V = NULL;
    TLSE* JV = NULL;
    teste_aux(g,&U,&V,&JV,g->id_no);

    //Salvo o retorno na variável para fazer a liberação das listas.
    int resp = ver_rep(U,V) && ver_rep(V,U) && ver_conect(g,JV);
    TLSE_libera(U);
    TLSE_libera(V);
    TLSE_libera(JV);
    return resp;
}


int main(void){
  TG *g = TG_inicializa();
  printf("Digite os nos do grafo (pare quando um numero menor ou igual a zero for fornecido)...\n");
  int no1, no2;
  while(1){
    scanf("%d", &no1);
    if(no1 <= 0) break;
    g = TG_ins_no(g, no1);    
  }
 
  printf("Digite as arestas (pare quando um dos nos nao pertencer ao grafo)...\n");
  while(1){
    scanf("%d%d", &no1, &no2);
    if(!TG_busca_no(g, no1) || !TG_busca_no(g, no2)) break;
    TG_ins_aresta(g, no1, no2);
  }
  TG_imprime(g);
  printf("Bipartido? %d\n", teste(g));
  TG_libera(g);
  return 0;
}

