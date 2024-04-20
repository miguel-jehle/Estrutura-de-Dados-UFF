// Q1 - ESCREVA UMA FUNÇÃO QUE COPIE UMA ÁRVORE COM A CHAMADA ArvNo* copia(ArvNo* A)

#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int info;
    struct no *esq, *dir;
}ArvNo;

//--------INSERÇÃO--------------------------------------------------------------------------------------------------------------
ArvNo *inserir(ArvNo *raiz, int num){
    if (!raiz){
        ArvNo *novo = malloc(sizeof(ArvNo));
        novo->info = num;
        novo->dir = NULL;
        novo->esq = NULL;
        return novo;
    }
    if (num > raiz->info) raiz->dir = inserir(raiz->dir, num);
    if (num < raiz ->info) raiz->esq = inserir(raiz->esq,num);
    return raiz;
}

//--------IMPRIMIR---------------------------------------------------------------------------------------------------------------
void imprimir(ArvNo *raiz){
    if (!raiz) return;
    imprimir(raiz->esq);
    printf("%d ",raiz->info);
    imprimir(raiz->dir);
}

//--------LIBERA-------------------------------------------------------------------------------------------------------------------
void libera(ArvNo *raiz){
    if(!raiz) return;
    libera(raiz->esq);
    libera(raiz->dir);
    free(raiz);
}

//--------COPIA-----------------------------------------------------------------------------------------------------------------------
ArvNo* copia(ArvNo* a){
    if (!a) return NULL;
    ArvNo *c = (ArvNo*)malloc(sizeof(ArvNo));
    c->info = a->info;
    c -> esq = copia(a->esq);
    c->dir = copia(a->dir);
    return c;
}


int main(void){

    ArvNo *raiz = NULL;
    ArvNo *copiada = NULL;

    int opcao,valor,altura, nos, folhas;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Copiar\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite um valor: ");
            scanf("%d",&valor);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf("\n\tA impressao ordenada eh: ");
            imprimir(raiz);
            printf("\n");
            break;
        case 3:
            copiada = copia(raiz);
            if(copia) printf("\n\tArvore copiada com sucesso!!! ");
            else printf("\n\tOcorreu algum problema na copia");
            printf("\n");
            printf("\n\tArvore original: ");
            imprimir(raiz);
            printf("\n");
            printf("\n\tArvore copiada: ");
            imprimir(copiada);
            printf("\n");
            break;
        
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);
    libera(copiada);

    return 0;
}

