#include"TAB.c"

int estbin(TAB *a){
    if(!a || (!a->esq && !a->dir)) return 1;
    if((!a->esq && a->dir) || (a->esq && !a->dir)) return 0;
    return (estbin(a->esq) && estbin(a->dir));
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
    int opcao, x,ver;
    TAB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Verificar Estritamente Binaria\n");
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
            ver = estbin(raiz);
            if(ver) printf("\n\tA arvore eh estritamente binaria!!!");
            else printf("\n\tA arvore nao eh estritamente binaria :( ");
            printf("\n");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    return 0;
}