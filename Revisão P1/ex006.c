/*
Retornar o tamanho (menor caminho) entre dois nós da arvore requisitados, alem de estar limitado a um numero maximo de arestas que voce pode se mover, se nao existir, retornar -infinito.
*/

#include"TG.c"
#include<limits.h>

int acha_menor(TG*g, TG* orig, int dest, int lim, int menor){
    if(lim == -1 || !orig) return INT_MAX;
    TVIZ* v = orig->prim_viz;
    int resp;

    //Para verificar se o dest está na lista de vizinhos
    while(v){
        if(v->id_viz == dest) return 1;
        v = v->prox_viz;
    }

    //Caso não
    v = orig->prim_viz;
    while(v){
        TG* no_aux = TG_busca_no(g,v->id_viz);
        resp = acha_menor(g,no_aux,dest,lim-1,menor);
        if(resp != INT_MAX) resp++;
        if((resp < menor) && (resp <= lim)) menor = resp;
        v = v->prox_viz;
    }
    return menor;
}

int menor_caminho(TG* g,int src,int dest, int n){
    if(!g) return INT_MAX;
    if(src == dest) return 0;
    TG* no_src = TG_busca_no(g, src);
    int menor = __INT_MAX__;
    return acha_menor(g,no_src,dest,n,menor);

}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, y,z;
    TG* grafo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Menor caminho ate n passos\n");
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
            printf("\n\tDigite o no de origem: ");
            scanf("%d", &x);
            printf("\n\tDigite o no de destino: ");
            scanf("%d", &y);
            printf("\n\tDigite o limite de passos que deseja dar: ");
            scanf("%d", &z);
            int resp;
            resp = menor_caminho(grafo,x,y,z);
            if(resp != INT_MIN) printf("\n\tO numero de passos eh: %d",resp);
            else printf("\n\tNao ha caminhor menor que %d",z);    
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
