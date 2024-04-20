#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int info;
    struct no *esq, *dir;
}ArvNo;

//(Q2) menor elemento da árvore: TABB* menor(TAB *a);

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
 ArvNo* menor(ArvNo *a){
    ArvNo* aux = a;
    while(aux->esq) aux = aux->esq;
    return aux; 
 }

int main(void){

    ArvNo *raiz = NULL;
    ArvNo *small = NULL;

    int opcao,info;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Achar o menor\n");
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
            small = menor(raiz);
            printf("\n\tO menor valor encontrado eh: %d\n", small->info);
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);
    libera(small);

    return 0;
}