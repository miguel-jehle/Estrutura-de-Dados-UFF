/*
Questão sugerida verbalmente em sala pela professora Isabel

A questão se trata de, percorrer uma TABB e buscar um valor x. No processo de encontrar o x, devemos obter o antecessor
e o sucessor do nó que estamos no momento, até obtermos x. Entendemos que a informação anterior e sucessor são referentes 
a informação imediatamente menor e a imediatamente maior. Então, deve-se colocar essas informações (ant e suc) em uma struct
própria, e então printar uma lista simplismente encadeada dessa strutc própria, que nomeei de TLAS.

Neste programa, por sugestão da professora, utilizei uma TLSE para auxiliar a encontrar o ant e suc, para tornar a excução
mais barata.
*/

#include"TABB.c"
#include"TLSE.c"

typedef struct lista_a_s{
    int antecessor, sucessor;
    struct lista_a_s *prox;
}TLAS;

void TLAS_imprime(TLAS* l){
    if(!l) return;
    if(l->antecessor == -(__INT_MAX__)) printf("ANT: -infinito / SUC: %d --> ",l->sucessor);
    else if(l->sucessor == __INT_MAX__) printf("ANT: %d / SUC: +infinito --> ", l->antecessor);
    else printf("ANT: %d / SUC: %d --> ", l->antecessor,l->sucessor);
    TLAS_imprime(l->prox);
}

void TLAS_libera(TLAS* l){
    if(!l) return;
    TLAS_libera(l->prox);
    free(l);
}

TLSE* cria_lista(TABB* a, TLSE* l){
    if(!a) return l;
    l = cria_lista(a->dir,l);
    l = TLSE_insere(l,a->info);
    l = cria_lista(a->esq,l);
    return l;
}

int find_suc(int x, TLSE* lista){
    TLSE* atual = lista;
    while((atual->prox) && (atual->info != x)) atual = atual->prox;
    if(!atual || atual->info != x) return -1;
    if(!atual->prox) return __INT_MAX__;
    return atual->prox->info;
}

int find_ant(int x, TLSE* lista){
    TLSE* ant = NULL, *atual = lista;
    while((atual)&&(atual->info != x)){
        ant = atual;
        atual = atual->prox;
    }
    if(!atual) return -1;
    if(!ant) return -(__INT_MAX__);
    return ant->info;
}

TLAS* TLAS_insere(int x, TLSE* lista, TLAS* l){
    TLAS* novo = (TLAS*)malloc(sizeof(TLAS));
    novo->sucessor = find_suc(x,lista);
    novo->antecessor = find_ant(x,lista); 
    novo->prox = NULL;
    if(!l) l = novo;
    else{
        TLAS* p = l;
        while(p->prox) p = p->prox;
        p->prox = novo;
    }
    return l;
}

TLAS* percorre(TABB*a, int x, TLSE* lista, TLAS* l){
    if(!a){
        TLAS_libera(l);
        return NULL;
    }
    l = TLAS_insere(a->info,lista,l);
    if(a->info == x) return l;
    if(x > a->info) l = percorre(a->dir,x,lista,l);
    if(x < a->info) l = percorre(a->esq,x,lista,l);
    return l;
}

TLAS* misc(TABB* a, int x){
    TLSE* lista = NULL;
    lista = cria_lista(a,lista);
    printf("\tLista criada: ");
    TLSE_imprime(lista);
    printf("\n");
    TLAS* l = NULL;
    l = percorre(a,x,lista,l);
    return l;    
}

TABB* insere(TABB* a, int x){
    if(!a){
        TABB* novo = (TABB*)malloc(sizeof(TABB));
        novo ->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } 
    if(x > a->info) a->dir = insere(a->dir,x);
    if(x < a->info) a->esq = insere(a->esq,x);
    return a;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TABB* raiz = NULL;
    TLAS* lista = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Encontra x com ANT e SUC dos nos\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite o valor a ser inserido na arvore: ");
            scanf("%d", &x);
            printf("\n");
            raiz = insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            TABB_imp_sim(raiz);
            printf("\n");
            break;
        
        case 3:
            printf("\n\tDigite o valor a ser buscado na arvore: ");
            scanf("%d",&x);
            printf("\n");
            lista = misc(raiz,x);
            printf("\n\tLista de ant e suc dos nos do caminho ate %d: ",x);
            TLAS_imprime(lista);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TABB_libera(raiz);
    TLAS_libera(lista);
    return 0;
}
