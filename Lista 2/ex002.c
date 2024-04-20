#include"TABB.c"

TABB * menor_na_arv(TABB *a){
    if(!a) return a;
    if(a->esq) return menor_na_arv(a->esq);
    return a;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TABB* raiz = NULL;
    TABB* menor = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Achar o menor\n");
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
            raiz = TABB_insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            TABB_imp_sim(raiz);
            printf("\n");
            break;

        case 3:
            menor = menor_na_arv(raiz);
            if(menor){
                    printf("\n\tMenor encontrado com sucesso!!! ");
                    printf("\n");
                    printf("\n\tMenor valor: %d", menor->info);
            }
            else printf("\n\tOcorreu algum problema para obter o menor");
            printf("\n");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TABB_libera(raiz);
    TABB_libera(menor);
    return 0;
}
