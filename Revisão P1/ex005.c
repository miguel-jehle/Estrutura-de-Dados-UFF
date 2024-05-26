/*
Retornar uma lista entre dois numeros (M e N), de uma TAB, onde possui tais valores contidos da árvore. Sendo este vetor, ordenado, sem metodos de ordenacao disponiveis (nao pode usar, ou implementar o proprio).
*/
#include"TLSE.c"
#include"TAB.c"

TAB* insere(TAB* a, int x){
    if(!a){
        TAB* novo = (TAB*)malloc(sizeof(TAB));
        novo ->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } 
    if(x > a->info) a->dir = insere(a->dir,x);
    if(x < a->info) a->esq = insere(a->esq,x);
    return a;
}

TLSE* insere_ordenado(TLSE* l, int x){
    if(!l || l->info > x) return TLSE_insere(l,x);
    l->prox = insere_ordenado(l->prox,x);
    return l;
}

TLSE* percorre(TAB*a, TLSE* l,int m, int n){
    if(!a) return l;
    l = percorre(a->esq,l,m,n);
    if(a->info > m && a->info < n) l = insere_ordenado(l,a->info);
    l = percorre(a->dir,l,m,n);
    return l;
}

TLSE* lista_mn(TAB* a, int m, int n){
    TLSE* l =  NULL;
    l = percorre(a,l,m,n);
    return l;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x,n,na,ma,t,m;
    TAB* raiz = NULL;
    TLSE* lista = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista ordenada\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao){
        case 1:
            printf("\n\tDigite o valor a ser inserido na arvore: ");
            scanf("%d", &x);
            printf("\n");
            raiz = insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            TAB_imp_sim(raiz);
            printf("\n");
            break;
        
        case 3:
            printf("\n\tDigite o valor do limite inferior: ");
            scanf("%d", &ma);
            printf("\n");
            printf("\n\tDigite o valor do limite superior: ");
            scanf("%d", &na);
            lista = lista_mn(raiz,ma,na);
            printf("\n\tA lista dos valores maiores que m e menores que n eh: \n");
            TLSE_imp_rec(lista);
            printf("\n");
            TLSE_lib_rec(lista);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    return 0;
}

