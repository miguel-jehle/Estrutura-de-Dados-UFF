#include"TABB.c"

TABB *retira_impares(TABB* a){
    if(!a) return a;
    if(a->esq) a->esq = retira_impares(a->esq);
    if(a->dir) a->dir = retira_impares(a->dir);
    if(a->info % 2 != 0) return TABB_retira(a,a->info);
    return a;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Retirar todos os impares\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf(" %d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite o valor a ser inserido na arvore: ");
            scanf(" %d", &x);
            printf("\n");
            raiz = TABB_insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            TABB_imp_sim(raiz);
            printf("\n");
            break;

        case 3:
            raiz = retira_impares(raiz);
            printf("\tImpares retirados com sucesso!!!");
            printf("\n");
            if(raiz){
                printf("\tA arvore agora sem impares eh: ");
                TABB_imp_sim(raiz);
                printf("\n");

            }else{
                printf("\tTodos os nos foram apagados!");
                printf("\n");
            }
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TABB_libera(raiz);
    return 0;
}