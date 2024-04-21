//(Q5) testar se dois grafos são iguais - int ig(TG *g1, TG *g2)
#include"TG.c"

int ver_ig_arestas(TVIZ*g, int g2, TG* bckp){
    if(!g) return 1;
    if(!TG_busca_aresta(bckp,g2,g->id_viz)) return 0;
    return ver_ig_arestas(g->prox_viz,g2,bckp);
}

int ver_ig(TG* g1, TG* g2,TG* bckp){ //Ver se as infos de g2 estoa em g1
    if(!g1) return 1;
    TG* g = TG_busca_no(bckp,g2->id_no);
    if(!g) return 0;
    if(!ver_ig_arestas(g->prim_viz,g2->id_no,bckp)) return 0;
    return ver_ig(g1, g2->prox_no,bckp);
}

int ig(TG* g1, TG* g2){
    return (ver_ig(g1,g2,g1) && ver_ig(g2,g1,g2));
}

/*
int ver_arestas(TVIZ* v1, TVIZ* v2){
    if(!v1 && !v2) return 1;
    if(!v1 || !v2) return 0;
    if(v1->id_viz != v2->id_viz) return 0;
    return ver_arestas(v1->prox_viz,v2->prox_viz);
}

int ig(TG *g1, TG *g2){
    if(!g1 && !g2) return 1;
    if(!g1 || !g2) return 0;
    if(g1->id_no != g2->id_no) return 0;
    if(!ver_arestas(g1->prim_viz,g2->prim_viz)) return 0;
    return ig(g1->prox_no,g2->prox_no);
}
*/

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, y,ver;
    TG* grafo = NULL;
    TG* segundo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No no primeiro\n\t2 - Inserir Aresta no primeiro\n\t3 - Inserir No no segundo\n\t4 - Inserir Aresta no segundo\n\t5 - Imprimir grafos\n\t6 - Verificar igualdade\n");
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
            break;
        case 3:
            printf("\n\tDigite o no a ser inserido no grafo: ");
            scanf("%d", &x);
            printf("\n");
            segundo = TG_ins_no(segundo,x);
            break;
        case 4:
            printf("\n\tDigite o no que deseja inserir a aresta: ");
            scanf("%d", &x);
            printf("\n");
            printf("\n\tDigite o no que deseja conectar com o no inserido: ");
            scanf("%d", &y);
            printf("\n");
            TG_ins_aresta(segundo,x,y);
            break;
        case 5:
            printf("\n\tOs grafos: ");
            printf("\n\tPrimeiro grafo:");
            TG_imp_rec(grafo);
            printf("\n");
            printf("\n\tSegundo grafo:");
            TG_imp_rec(segundo);
            printf("\n");
            break;
        case 6:
            ver = ig(grafo,segundo);
            if(ver) printf("\n\t Os grafos sao iguais!!!");
            if(!ver) printf("\n\t Os grafos nao sao iguais :( ");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TG_libera(grafo);
    TG_libera(segundo);
    return 0;
}