#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int valor;
    struct no *esquerdo, *direito;
    short altura;
}No;

/*
    Função para criar um novo nó
*/
No* novoNo(int x){
    No *novo = (No*)malloc(sizeof(No));
    if(novo){
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }else printf("\nERRO ao alocar no em novoNo!\n");
    return novo;
}

/*
    Retorna o maior de dois valores
*/
short maior (short a, short b){
    return (a > b) ? a : b;
}

/*
    Retorna a altura de um nó ou -1 caso ele não exista
*/
short alturaDoNo(No *no){
    if(!no) return -1;
    else return no ->altura;
}

/*
    Calcula e retorna o fator de balanceamento de um nó
*/
short fatorDebalanceamento(No *no){
    if(!no) return 0;
    else return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
}

//-----ROTACAO A ESQUERDA-------------------------------------------------------------------
No* rotacaoEsquerda(No *r){
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

//------ROTACAO A DIREITA--------------------------------------------------------------------
No* rotacaoDireita(No *r){
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

//-------ROTACAO ESQUERDA-DIREITA---------------------------------------------------------
No* rotacaoEsquerdaDireita(No *r){
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

//--------ROTACAO DIREITA-ESQUERDA----------------------------------------------------------------
No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

//-------BALANCEAR--------------------------------------------------------------------------
No* balancear(No *raiz){
    short fb = fatorDebalanceamento(raiz);

    //Roda esquerda
    if(fb < -1 && fatorDebalanceamento(raiz->direito) <= 0) raiz = rotacaoEsquerda(raiz);

    //Roda direita
    else if(fb > 1 && fatorDebalanceamento(raiz->esquerdo) >= 0) raiz = rotacaoDireita(raiz);

    //Roda esquerda-direita
    else if (fb > 1 && fatorDebalanceamento(raiz->esquerdo) < 0) raiz= rotacaoEsquerdaDireita(raiz);

    else if (fb < -1 && fatorDebalanceamento(raiz->direito) > 0) raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}
//--------LIBERA-------------------------------------------------------------------------------------------------------------------
void libera(No *raiz){
    if(!raiz) return;
    libera(raiz->esquerdo);
    libera(raiz->direito);
    free(raiz);
}


//-------INSERIR---------------------------------------------------------------------
No* inserir(No *raiz, int x){
    if(!raiz) return novoNo(x);
    else{
        if(x < raiz->valor) raiz->esquerdo = inserir(raiz->esquerdo, x);
        else if (x > raiz->valor) raiz->direito = inserir(raiz->direito,x);
        else printf("\nInsercao nao realizada! O elemento ja existe!!!\n");
    }
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

//-------REMOVER--------------------------------------------------------------------------
No *remover(No *raiz, int chave){
    if(!raiz){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if(raiz->valor == chave){
            if(!raiz->esquerdo && !raiz->direito){
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            } else {
                if(raiz->esquerdo && raiz->direito){
                    No *aux = raiz->esquerdo;
                    while(aux->direito) aux = aux -> direito;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n",chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                } else{
                    No *aux;
                    if(!raiz-> esquerdo) aux = raiz->esquerdo;
                    else aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido!\n");
                    return aux;
                }
            } 
        } else {
            if (chave < raiz->valor) raiz-> esquerdo = remover(raiz->esquerdo, chave);
            else raiz->direito = remover(raiz->direito, chave);
        }

        raiz->altura = maior(alturaDoNo(raiz->esquerdo),alturaDoNo(raiz->direito)) + 1;

        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++){
            printf("\t");
        }
        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}

int main(){

    int opcao, valor;
    No *raiz = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch (opcao){
        case 0:
            printf("\tSaindo!!!");
            break;
        case 1:
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = inserir(raiz,valor);
            break;
        case 2:
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        default:
            printf("\tOpcao invalida!!!\n");
            break;
        }
    }while(opcao != 0);

    libera(raiz);

    return 0;
}

