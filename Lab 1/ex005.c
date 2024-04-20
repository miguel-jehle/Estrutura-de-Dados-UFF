#include"TAB.c"

int confere(TAB *a1, TAB* a2){
    if(!a2) return 1;
    if(TAB_busca(a1,a2->info)) return (confere(a1,a2->esq) && confere(a1,a2->dir));
    else return 0;
}

int mi(TAB *a1, TAB *a2){
    if(!a1 && !a2) return 1;
    return(confere(a1,a2) && confere(a2,a1)); 
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
    TAB* outra = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir na primeira\n\t2 - Imprimir\n\t3 - Inserir na segunda\n\t4 - Imprimir a segunda\n\t5 - Verificar infos\n");
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
            printf("\n\tDigite o valor a ser inserido na arvore: ");
            scanf("%d", &x);
            printf("\n");
            outra = insere(outra,x);
            break;

        case 4:
            printf("\tA arvore eh: ");
            TAB_imp_sim(outra);
            printf("\n");
            break;

        case 5:
            ver = mi(raiz,outra);
            if(ver) printf("\n\tAs infos sao iguais");
            else printf("\n\tAs infos NAO sao iguais");
            printf("\n");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    TAB_libera(outra);
    return 0;
}