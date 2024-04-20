#include"TAB.c"
#include"TLSE.c"

int ver_zz(TAB* a){
    if(!a) return 1;
    if(a->esq && a->dir) return 0;
    return (ver_zz(a->esq) && ver_zz(a->dir));

    /* AQUI ESTÁ O CÓDIGO INICIAL, QUE DEPOIS REDUZI PARA LÓGICA ACIMA.
    int resp = ver_zz(a->esq);
    if(!resp) return 0;
    resp = ver_zz(a->dir);
    if(!resp) return 0;
    return 1;
    */
}

int zz(TAB* a){
    if(!a) return 0;
    return (ver_zz(a->esq) && ver_zz(a->dir));
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
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Verificar Zigue-Zague\n");
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
            ver = zz(raiz);
            if(ver) printf("\n\tA arvore eh zigue-zague!!!");
            else printf("\n\tA arvore nao eh zigue-zague :( ");
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
