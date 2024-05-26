/*
Considere o grafo a seguir, que representa seguidores no
Instagram. Cada pessoa tem nome e idade (nome é o id do
vértice). Uma aresta (v1, v2) significa que v1 segue v2 no
Instagram.

Q1- Quantas pessoas uma determinada pessoa segue? int numero_seguidos(TGrafo *g, char *nome);

Q2- Quem são os seguidores de uma determinada pessoa? (função imprime os nomes dos seguidores, caso a flag imprime seja
    True, e retorna quantidade de seguidores) int seguidores(TGrafo *vertice, char *nome, int imprime);

Q3- Quem é a pessoa mais popular? (tem mais seguidores) TGrafo *mais_popular(TGrafo *g);

Q4- 4. Quais são as pessoas que só seguem pessoas mais velhas do que ela própria? (função imprime os nomes das pessoas, caso a
    flag imprime seja True, e retorna quantidade de pessoas) int segue_mais_velho(TGrafo *g, int imprime);
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct vizinhos_p{
    char nome[10];
    struct vizinhos_p* prox_viz;
}TVIZP;

typedef struct grafo_p{
    char nome[10];
    int idade;
    struct grafo_p* prox;
    TVIZP* vizinhos;
}TGP;
//----------------------------------------------------------
//          Funções gerais
//----------------------------------------------------------

TGP* insere(TGP* g,char* n, int idade){
    if(!g){
        TGP* novo = (TGP*)malloc(sizeof(TGP));
        novo->idade = idade;
        strcpy(novo->nome,n);
        novo->prox = NULL;
        novo->vizinhos = NULL;
        return novo;
    }
    g->prox = insere(g->prox,n,idade);
}

TGP* busca(TGP* g, char* nome){
    if(!g) return NULL;
    if(strcmp(g->nome,nome) == 0 ) return g;
    return busca(g->prox,nome);
}

void libera_aresta(TVIZP* v){
    if(!v) return;
    libera_aresta(v->prox_viz);
    free(v);
}

void libera(TGP* g){
    if(!g) return;
    libera_aresta(g->vizinhos);
    libera(g->prox);
    free(g);
}

TGP* cria_aresta(TGP* g, char* x, char* y){
    TGP* src = busca(g,x);
    TVIZP* novo = (TVIZP*)malloc(sizeof(TVIZP));
    strcpy(novo->nome,y);
    novo->prox_viz = src->vizinhos;
    src->vizinhos = novo;
    return g;
}

void imp_rec(TGP *g){
  if(g){
    printf("\n\t%s: ", g->nome);
    TVIZP *v = g->vizinhos;
    while(v){
      printf(" %s -->", v->nome);
      v = v->prox_viz;
    }
    printf("\n");
    imp_rec(g->prox);
  }
}
//--------------------------------------------------------
//      Funções para Q1
//--------------------------------------------------------
int numero_seguidos(TGP *g, char *nome){
    TGP* p = busca(g,nome);
    TVIZP* v = p->vizinhos;
    int cont = 0;
    while(v){
        cont++;
        v = v->prox_viz;
    }
    return cont;
}
//-------------------------------------------------------
//      Funções para Q2
//-------------------------------------------------------
int seg_aux(TGP* g,char* nome){
    if(!g) return 0;
    if(strcmp(g->nome,nome)==0) return seg_aux(g->prox,nome);
    TVIZP* v = g->vizinhos;
    while(v){
        if(strcmp(v->nome,nome)==0){
            printf("\t%s\n",g->nome);
            return 1 + seg_aux(g->prox,nome);
        }
        v = v->prox_viz;
    }
    return seg_aux(g->prox,nome);
}

int seguidores(TGP *vertice, char *nome,int imprime){

    imprime = seg_aux(vertice,nome);
    if(imprime) printf("\n\t%s possui %d seguidores.",nome,imprime);
    else printf("\n\t%s nao possui seguidores :( ",nome);
    return 0;
}
//-------------------------------------------------------
//      Funções para Q3
//-------------------------------------------------------


//---------------------------------------------------------
int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao,ver,id,a,b;
    char n[10], x[10], y[10];
    TGP* grafo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Criar perfil\n\t2 - Seguir alguem\n\t3 - Imprimir grafo\n\t4 - Verificar numero de seguidores\n\t5 - Verificar quem sao os seguidores");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite o nome da pessoa que esta criando o perfil: ");
            scanf("%s", n);
            printf("\n");
            printf("\n\tDigite a idade da pessoa que esta criando o perfil: ");
            scanf("%d", &id);
            grafo = insere(grafo,n,id);
            break;
        
        case 2:
            printf("\n\tDigite a pessoa que vai seguir alguem: ");
            scanf("%s", x);
            printf("\n");
            printf("\n\tDigite quem a pessoa quer seguir: ");
            scanf("%s", y);
            printf("\n");
            grafo = cria_aresta(grafo,x,y);
            break;

        case 3:
            printf("\n\tO grafo eh: ");
            imp_rec(grafo);
            printf("\n");
            break;
        case 4:
            printf("\n\tDigite a pessoa que voce quer saber a quantidade de seguidores: ");
            scanf("%s", x);
            printf("\n");
            a = numero_seguidos(grafo,x);
            printf("\n\tEsta pessoa segue %d pessoa(s): ",a);
            printf("\n");
            break;
        case 5:
            printf("\n\tDigite a pessoa que voce quer saber quem sao os seguidores: ");
            scanf("%s", x);
            printf("\n");
            printf("\n\tOs seguidores sao: ");
            a = seguidores(grafo,x,b);
            printf("\n");
            break;
        case 6:

            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    libera(grafo);
    return 0;
}

