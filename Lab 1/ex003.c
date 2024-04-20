#include"TLSE.c"
#include"TABB.c"

TLSE* insere_ancestrais(TABB* a, int elem, TLSE* l){
    if(!a) return NULL;
    if(!a->esq && !a->dir && a->info != elem){
        TLSE_libera(l);
        return NULL;
    }
    l = TLSE_insere(l,a->info);
    if(a->info == elem) return l;
    if(elem > a->info) return insere_ancestrais(a->dir,elem,l);
    if(elem< a->info) return insere_ancestrais(a->esq,elem,l);
}

TLSE* ancestrais(TABB *a, int elem){
    TLSE* resp = TLSE_inicializa();
    if(elem > a->info) return insere_ancestrais(a->dir,elem,resp);
    if(elem < a->info) return insere_ancestrais(a->esq,elem,resp);
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
    int opcao, x,elem;
    TABB* raiz = NULL;
    TLSE* lista = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista de Ancestrais\n");
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
            printf("\n\tDigite o valor que voce deseja os ancestrais: ");
            scanf("%d", &elem);
            printf("\n");
            lista = ancestrais(raiz,elem);
            printf("\n\tA lista de ancestrais eh: ");
            TLSE_imprime(lista);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TABB_libera(raiz);
    TLSE_libera(lista);
    return 0;
}

