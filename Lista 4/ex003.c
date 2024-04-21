/*
(Q3) se esta estrutura tivesse um campo cor (int cor) na estrutura de grafo, teste se nós vizinhos não
tem a mesma cor. A função retorna um se os vizinhos não tem a mesma cor e zero, caso contrário:
int nao_tem_mesma_cor(TG *g);
*/
#include"stdio.h"
#include"stdlib.h"
#define AZUL 1;
#define AMARELO 2;
#define VERMELHO 3;
#define VERDE 4;

//=========================== Refazendo a Biblioteca ========================================

typedef struct viz{
    int id_viz, cor;
    struct viz *prox_viz;
}TVIZ_cor;

typedef struct grafo{
    int id_no, cor;
    TVIZ_cor *prim_viz;
    struct grafo *prox_no;
}TG_cor;

void TG_imp(TG_cor *g){
  if(g){
    printf("\n\t%d(%d): ", g->id_no,g->cor);
    TVIZ_cor *v = g->prim_viz;
    while(v){
      printf("%d(%d) --> ", v->id_viz,v->cor);
      v = v->prox_viz;
    }
    printf("\n");
    TG_imp(g->prox_no);
  }
}

void TG_libera_viz(TVIZ_cor *v){
  if(!v) return;
  TG_libera_viz(v->prox_viz);
  free(v);
}

void TG_libera_rec(TG_cor *g){
  if(g){
    TG_libera_viz(g->prim_viz);
    TG_libera_rec(g->prox_no);
    free(g);
  }
}

TG_cor* TG_busca_no(TG_cor* g, int x){
  if((!g) || (g->id_no == x)) return g;
  return(TG_busca_no(g->prox_no, x));
}

TVIZ_cor* TG_busca_aresta(TG_cor *g, int no1, int no2){
  TG_cor *p1 = TG_busca_no(g,no1), *p2 = TG_busca_no(g,no2);
  if((!p1) || (!p2)) return NULL;
  TVIZ_cor *resp = p1->prim_viz;
  while((resp) && (resp->id_viz != no2)) resp = resp->prox_viz;
  return resp;
}

TG_cor* TG_ins_no(TG_cor *g, int x, int cor){
  TG_cor *p = TG_busca_no(g, x);
  if(!p){
    p = (TG_cor*) malloc(sizeof(TG_cor));
    p->id_no = x;
    p->prox_no = g;
    p->cor = cor;
    p->prim_viz = NULL;
    g = p;
  }
  return g;
}

void TG_ins_um_sentido(TG_cor *g, int no1, int no2){
  TG_cor *p = TG_busca_no(g, no1), *q = TG_busca_no(g, no2);
  if((!p) || (!q)) return;
  TVIZ_cor *aresta = TG_busca_aresta(g, no1, no2);
  if(aresta) return;
  aresta = (TVIZ_cor *) malloc(sizeof(TVIZ_cor));
  aresta->id_viz = no2;
  aresta->cor = q->cor;
  aresta->prox_viz = p->prim_viz;
  p->prim_viz = aresta;
}

void TG_ins_aresta(TG_cor *g, int no1, int no2){
  TG_ins_um_sentido(g, no1, no2);
  TG_ins_um_sentido(g, no2, no1);
}

//==================================Código da Questão================================================
int ver_cor(TVIZ_cor*v, int cor){
    if(!v) return 1;
    if(v->cor == cor) return 0;
    return ver_cor(v->prox_viz,cor);
}

int nao_tem_mesma_cor(TG_cor *g){
    if(!g) return 1;
    return (ver_cor(g->prim_viz,g->cor) && nao_tem_mesma_cor(g->prox_no));
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, y,c,ver;
    TG_cor* grafo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Verifica Cores\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite o no a ser inserido no grafo: ");
            scanf("%d", &x);
            printf("\n");
            printf("\n\tDigite a cor do no a ser inserido no grafo: ");
            scanf("%d", &c);
            printf("\n");
            grafo = TG_ins_no(grafo,x,c);
            break;
        
        case 2:
            printf("\n\tDigite o no que deseja inserir a aresta: ");
            scanf("%d", &x);
            printf("\n");
            printf("\n\tDigite o no que deseja conectar com o no inserido: ");
            scanf("%d", &y);
            printf("\n");
            TG_ins_aresta(grafo,x,y);

        case 3:
            printf("\n\tO grafo eh: ");
            TG_imp(grafo);
            printf("\n");
            break;
        case 4:
            ver = nao_tem_mesma_cor(grafo);
            if(ver) printf("\n\tNao existe vizinhos da mesma cor");
            else printf("\n\tExistem vizinhos de mesma cor");
            break; 

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TG_libera_rec(grafo);
    return 0;
}