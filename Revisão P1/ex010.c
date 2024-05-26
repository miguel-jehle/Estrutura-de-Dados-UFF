//Verifique se uma TABB é AVL, 1 caso sim e 0 caso não.

#include"TABB.c"

int fb(TABB* a);
int ver_AVL(TABB* a);
int alt(TABB* a);
int maior(int x, int y);

int ver_AVL(TABB* a){
    if(!a) return 1;
    if((fb(a) > 1) || (fb(a) < -1)) return 0;
    return (ver_AVL(a->esq) && ver_AVL(a->dir));
}

int fb(TABB* a){
    if(!a) return 0;
    return (alt(a->esq) - alt(a->dir));
}

int alt(TABB* a){
    if(!a) return -1;
    return (maior(alt(a->esq),alt(a->dir)) + 1);
}

int maior(int x, int y){
    if (x > y) return x;
    return y;
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
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Verificar se eh AVL\n");
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
            x = ver_AVL(raiz);
            if(!x) printf("\n\tNAO eh AVL");
            else printf("\n\tEh AVL");
            printf("\n");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TABB_libera(raiz);
    return 0;
}