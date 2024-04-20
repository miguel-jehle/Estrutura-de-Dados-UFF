/*
    (Q3) uma função em C que, dada uma árvore binária de busca qualquer, retire todos os elementos
    ímpares da árvore original. A função deve ter o seguinte protótipo: ArvNo*
    retira_impares(ArvNo* a);
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int info;
    struct no *esq, *dir;
}ArvNo;

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

//------RETIRA IMPARES----------------------------------------------------------------------------------------------------------------------
 ArvNo* retira_impares(ArvNo* a){
    if(!a) return NULL;

    if(a->info % 2 != 0){

//************NÓ FOLHA
        if(!a->dir && !a->esq){
            free(a);
            return NULL;

//************COM DOIS FILHOS
        }else if(a->dir && a->esq){
            ArvNo *aux = a->esq;
            while(aux->dir) aux = aux->dir;
            int novo = a->info;
            a->info = aux->info;
            aux->info = novo;
            a = retira_impares(a);

//************COM UM FILHO
        }else{
            ArvNo *aux = a;
            if(aux->dir) aux = aux->dir;
            else aux = aux->esq;
            free(a);
            return aux;
        }

    }else{
        a->dir = retira_impares(a->dir);
        a->esq = retira_impares(a->esq);
        return a;
    }

 }

int main(void){

    ArvNo *raiz = NULL;
    ArvNo *sem_impar = NULL;

    int opcao,info;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Retira Impares\n");
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
            sem_impar = retira_impares(raiz);
            printf("\n\tImpares retirados com sucesso !!!\n");
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);
    libera(sem_impar);

    return 0;
}