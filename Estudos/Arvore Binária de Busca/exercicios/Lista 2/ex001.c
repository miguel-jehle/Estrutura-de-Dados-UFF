#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int info;
    struct no *esq, *dir;
}ArvNo;

//(Q1) maior elemento da árvore: TABB* maior(TAB *a);

//--------INSERÇÃO--------------------------------------------------------------------------------------------------------------
void inserir(ArvNo **raiz, int num){
    if(*raiz == NULL){
        *raiz = malloc(sizeof(ArvNo)); 
        (*raiz)->dir = NULL;
        (*raiz)->esq = NULL; 
        (*raiz)->info = num;
    }
    if(num < (*raiz)->info) inserir(&((*raiz)->esq), num);
    if(num > (*raiz)->info) inserir(&((*raiz)->dir), num);
}

//--------IMPRIMIR---------------------------------------------------------------------------------------------------------------
void imprimir(ArvNo *raiz){
    if (!raiz) return;
    printf("%d ",raiz->info);
    imprimir(raiz->esq);
    imprimir(raiz->dir);
}
 

//--------LIBERA-------------------------------------------------------------------------------------------------------------------
void libera(ArvNo *raiz){
    if(!raiz) return;
    libera(raiz->esq);
    libera(raiz->dir);
    free(raiz);
}

//------MAIOR----------------------------------------------------------------------------------------------------------------------
 ArvNo* maior(ArvNo *a){
    ArvNo* aux = a;
    while(aux->dir) aux = aux->dir;
    return aux; 
 }

int main(void){

    ArvNo *raiz = NULL;
    ArvNo *The_big_one = NULL;

    int opcao,info;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Achar o Maior\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite um info: ");
            scanf("%d",&info);
            inserir(&raiz, info);
            break;
        case 2:
            printf("\n\t A impressao ordenada eh: ");
            imprimir(raiz);
            printf("\n");
            break;
        case 3:
            The_big_one = maior(raiz);
            printf("\n\tO maior valor encontrado eh: %d\n", The_big_one->info);
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);
    libera(The_big_one);

    return 0;
}