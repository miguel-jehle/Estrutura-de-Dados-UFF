/*
Q1 - Verifique se um grafo é bipartido, retorne 1 caso sim e 0 caso não, é permitido o uso da estrutura TLSE para auxiliar. int teste(TG* g)

Definição de bipartido: Um grafo ao qual podemos separar em duas partições, como exemplo uma U e outra V, na qual, os nós de U
                        somente se ligam aos nós de V e os de V somente aos de U. Além disso, o grafo deve ser todo conectado para
                        configurar como um grafo bipartido.

Dica: Para entender melhor, um grafo bipartido, olhado na implementação de sua estrutura (nós principais e nós de vizinhos), se trata de
      um grafo ao qual podemos dividir em 2 grafos, um em que os nós principais são somente do conjunto U e os vizinhos todos somente de V,
      e no outro vice-versa, desenhe e ficará mais visível a definição de fato de um grafo bipartido.
*/

#include"TG.c"
#include"TLSE.c"

int ver_conect(TG* g, TLSE* JV){
    if(!JV) return 0;
    while(g){
        if(!TLSE_busca(JV,g->id_no)) return 0;
        g = g->prox_no;
    }
    return 1;
}

int ver_rep(TLSE* U, TLSE* V){
    if(!U || !V) return 0;
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
    int resp = ver_rep(U,V) && ver_rep(V,U) && ver_conect(g,JV);
    TLSE_libera(U);
    TLSE_libera(V);
    TLSE_libera(JV);
    return resp;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, y;
    TG* grafo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Verificar grafo bipartido\n");
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
            printf("\n\tO verificador eh: %d",teste(grafo));
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

