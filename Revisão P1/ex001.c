//Faça uma questão que recebe uma TAB e retorna uma lista simplismente encadeada ordenada

#include"TAB.c"
#include"TLSE.c"

TLSE* insere_ordenado(TLSE*l, int x){
    if(!l || l->info > x) l = TLSE_insere(l,x);
    if(l->info < x) l->prox = insere_ordenado(l->prox,x);
    return l;
}

void percorre(TAB* a, TLSE **l){
    if(!a) return; 
    percorre(a->esq,l);
    (*l) = insere_ordenado((*l),a->info);
    percorre(a->dir,l);
}

TLSE* lista_ord(TAB *a){
    if(!a) return NULL;
    TLSE* resp = NULL;
    percorre(a,&resp);
    return resp;
}

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

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TAB* raiz = NULL;
    TLSE* lista = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista ordenada\n");
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
            TAB_imp_sim(raiz);
            printf("\n");
            break;
        
        case 3:
            lista = lista_ord(raiz);
            printf("\n\tA lista ordenada com os elementos da arvore eh: ");
            if(!lista) printf("se fudeu");
            TLSE_imp_rec(lista);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    TLSE_libera(lista);
    return 0;
}
