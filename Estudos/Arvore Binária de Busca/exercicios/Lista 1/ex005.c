// Q1 - ESCREVA UMA FUNÇÃO QUE VERIFICA SE AS ARVORES SÃO IDÊNTICAS COM A CHAMADA ArvNo* maior(ArvNo* raiz)

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

//--------ACHA MAIOR -----------------------------------------------------------------------------------------------------------------------
int compara (ArvNo* raiz, ArvNo*raiz_2){
    
    
    
}   


int main(void){

    ArvNo *raiz = NULL;
    ArvNo *maior = NULL;
    

    int opcao,valor,altura, nos, folhas;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Achar maior\n");
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
            maior = acha_maior(raiz);
            if(maior) printf("\n\tO maior valor foi encontrado: %d\n",maior->info);
            else printf("\n\tO maior não foi encontrado!\n");
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);

    return 0;
}

