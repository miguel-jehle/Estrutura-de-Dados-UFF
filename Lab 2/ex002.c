/*
Dados um grafo, dois nós x e y, retorne um caminho qualquer entre x e y. Se não tiver caminho, o retorno é NULL: TLSE *caminho (TG *g, int x, int y);
*/
#include"TLSE.c"
#include"TG.c"
int ver_passou(int x, TLSE* l){
    if(!TLSE_busca(l,x)) return 0; //Se não tá retorna 0
    return 1;//Senão retorna 1
}

TLSE* acha_caminho_no(TG* g,TG* no_atual,int dest,TLSE* lista,TLSE* percorrido){
    //Condição de retorno básica
    if(!no_atual) return NULL;

    //Salvo a lista de vizinhos para percorrer
    TVIZ* v = no_atual->prim_viz;

    //Percorro a lista de vizinhos para verificar se o dest se encontra nela.
    while(v) { 
        if(v->id_viz == dest) return TLSE_insere(lista,dest); //Caso sim, retorna inserindo
        v = v->prox_viz;
    } 
    
    //Se não tiver, resseto meu v para o começo da lista de vizinhos e percorro pras chamadas recursivas
    v = no_atual->prim_viz;

    //Loop para fazer as chamadas recursivas e procurar nos vizinhos
    while(v){

        //Busco o nó com o id do v atual no grafo.
        TG* aux = TG_busca_no(g,v->id_viz); 

        //Caso o v não seja um nó já visitado, chamo recursivamente para ele, faço isso para evitar ciclos.
        if(!ver_passou(v->id_viz,percorrido)){ //verificação
            percorrido = TLSE_insere(percorrido,v->id_viz); //Se não havia passado ainda,vou passar agora, então insiro
            lista = acha_caminho_no(g,aux,dest,lista,percorrido);//Chamo recursivamente
        }

        //Se a minha lista é diferente de nula, estou no processo de retornar inserindo, logo, retorno este nó inserindo também
        if(lista) return TLSE_insere(lista,v->id_viz);

        //Caso não, só passo o v para o prox, para a proxima iteração
        v = v->prox_viz;
    }
    //Se tiver passado por tudo isso, não há caminho, retorne NULO.
    return NULL;
}

TLSE *caminho (TG *g, int x, int y){
    //Caso não haja grafo, destino ou origem, encerro
    if(!g || !TG_busca_no(g,x) || !TG_busca_no(g,y)) return NULL; 

    //Salvo meu no de origem
    TG* no_x = TG_busca_no(g,x);

    //Crio as listas que serão utilizadas
    TLSE* resp = NULL;
    TLSE* jp = NULL; //Lista auxiliar (já passsou)

    //Chamo a minha função recursiva para percorrer o grafo
    resp = acha_caminho_no(g,no_x,y,resp,jp);

    //Libero minha lista auxiliar dos nós já visitados
    free(jp);

    //Quando eu achar o dest, retorno inserindo, se retornar NULL, não há caminho
    if(!resp) return NULL;

    //Retorna inserindo a origem.
    return TLSE_insere(resp,x); 
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, y,ver,a,b;
    TG* grafo = NULL;
    TLSE* resp = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Acha caminho\n");
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
            printf("\n\tDigite o no que deseja usar como origem: ");
            scanf("%d", &a);
            printf("\n");
            printf("\n\tDigite o no que deseja usar como destino: ");
            scanf("%d", &b);
            printf("\n");
            resp = caminho(grafo,a,b);
            if(!resp) printf("\n\tNao ha caminho do no %d para o no %d",a,b);
            else printf("\n\tO caminho existe e eh: ");
            TLSE_imprime(resp);
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