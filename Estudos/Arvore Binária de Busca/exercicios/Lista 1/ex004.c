// Q1 - ESCREVA UMA FUNÇÃO QUE ENCONTRA O MENOR ELEMENTO DA ARVORE COM A CHAMADA ArvNo* maior(ArvNo* raiz)

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
ArvNo* acha_menor(ArvNo* raiz){

    //Não pude colocar um "if(!raiz) return NULL" pois isso me daria um retorno NULL em algumas ocasiôes, e então não seria capaz de fazer comparações numéricas, por isso me previno

    if(raiz->dir){ //Não permito que a função tenha uma chamada que vá para NULL, senão minha comparação dará ruim. Por isso verifico se existe antes de chamar
        if(raiz->info > acha_menor(raiz->dir)->info) return raiz->dir; //Comparo a raiz atual com o retorno da sua a direita e caso a da direita seja maior, ela que será retornada
    }
    if(raiz->esq){ //Mesmo esquema da parte de cima
        if(raiz->info > acha_menor(raiz->esq)->info) return raiz->esq;
    }
    else return raiz;//Caso nenhum desses casos ocorra, retorno a raiz como a maior mesmo.
}   

int main(void){

    ArvNo *raiz = NULL;
    ArvNo *menor = NULL;
    

    int opcao,valor,altura, nos, folhas;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Achar menor\n");
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
            menor = acha_menor(raiz);
            if(menor) printf("\n\tO menor valor foi encontrado: %d\n",menor->info);
            else printf("\n\tO maior não foi encontrado!\n");
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);

    return 0;
}

