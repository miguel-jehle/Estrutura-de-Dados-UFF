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

TAB* espelha(TAB* a){
    if(!a) return NULL;
    TAB* b = (TAB*)malloc(sizeof(TAB));
    b->info = a->info;
    b->esq = espelha(a->dir);
    b->dir = espelha(a->esq);
    return b;
}



int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TAB* raiz = NULL;
    TAB* espelhada = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Espelhar\n\t4 - Imprime espelhada\n");
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
            espelhada = espelha(raiz);
            if(espelhada) printf("\n\tArvore espelhada com sucesso!!! ");
            else printf("\n\tOcorreu algum problema na copia");
            printf("\n");
            printf("\n\tArvore original: ");
            TAB_imp_sim(raiz);
            printf("\n");
            printf("\n\tArvore espelhada: ");
            TAB_imp_sim(espelhada);
            printf("\n");
            break;
        
        case 4:
            printf("\t\nA arvore espelhada eh: \n");
            TAB_imp_sim(espelhada);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    TAB_libera(espelhada);
    return 0;
}