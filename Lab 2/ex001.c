/*
    Dado um grafo conectado, verifique se ele pode ser transformado em árvore binária:
*/

// Algortimo: faço uma lista dos filhos daquele nó, chamo recursivamente pro proximo, com a lista, se o cara da nova chamada, for vizinho do seu irmão, dá pau
#include "TG.c"
#include"TLSE.c"

TLSE* insere_fim(TLSE* l, int x){
    if(!l) l = TLSE_insere(l,x);
    else l->prox = insere_fim(l->prox,x);
    return l;
}

TLSE* cria_lista(TG* g){
    TLSE* l = NULL;
    l = insere_fim(l,g->id_no);
    TVIZ* v = g->prim_viz;
    while(v){
        l = insere_fim(l,v->id_viz);
        v = v->prox_viz;
    }
    return l;
}


int ver_parentesco(TG* grafo,TLSE* lista_pai){
    TVIZ* lista_viz = grafo->prim_viz;
    TLSE* pai = lista_pai;
    while(lista_viz){
        if(TLSE_busca(lista_pai,lista_viz->id_viz)){
            if(lista_viz->id_viz != pai->info) return 0;
        }
        lista_viz = lista_viz->prox_viz;
    }
    return 1;
}

int teste(TG* g){
    if(!g) return 0;
    int ver;
    TG* m = g;
    while(m){
        TLSE* l = cria_lista(g);
        TVIZ* vizinhos = g->prim_viz;
        while(vizinhos){
            TG* filho = TG_busca_no(g,vizinhos->id_viz);
            ver =ver_parentesco(filho,l);//No filho, passo a lista do pai
            if(ver == 0) return ver;
            vizinhos = vizinhos->prox_viz;
        }
        TLSE_libera(l);
        m = m->prox_no;
    }
    return 1;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, y,ver;
    TG* grafo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Verificador Arvore\n");
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
            grafo = TG_ins_no(grafo,x);
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
            TG_imp_rec(grafo);
            printf("\n");
            break;
        case 4:
            ver = teste(grafo);
            if(ver) printf("\n\tO grafo pode ser arvore");
            else printf("\n\tO grafo NAO pode ser arvore");
            printf("\n");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TG_libera(grafo);
    return 0;
}