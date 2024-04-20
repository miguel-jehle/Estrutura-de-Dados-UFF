#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin_cor{
    int info;
    struct arvbin_cor *esq, *dir;
    int cor;
}TAB_cor;

#define BRANCO 0
#define PRETO 1
#define VERMELHO 2

void colore(TAB_cor* a){
    if(!a) return;
    if(a->cor == BRANCO) a->cor = PRETO;
    if(a->cor == PRETO){
        if(a->esq) a->esq->cor = VERMELHO;
        if(a->dir) a->dir->cor = VERMELHO;
    }else{
        if(a->esq) a->esq->cor = PRETO;
        if(a->dir) a->dir->cor = PRETO;
    }
    /*
    Nao preciso verificar antes de chamar, pois existe o "if(!a) return",
    caso não tivesse, deveria verificar se existe esq e dir antes de chamar
    recursivamente.
    */
    colore(a->esq);
    colore(a->dir);
    return;
}

TAB_cor* insere(TAB_cor* a, int x){
    if(!a){
        TAB_cor* novo = (TAB_cor*)malloc(sizeof(TAB_cor));
        novo ->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->cor = BRANCO;
        return novo;
    } 
    if(x > a->info) a->dir = insere(a->dir,x);
    if(x < a->info) a->esq = insere(a->esq,x);
    return a;
}

void imprime_colorido(TAB_cor* a){
    if(!a) return;
    imprime_colorido(a->esq);
    printf("No: %d pintado de %d",a->info,a->cor);
    printf("\n");
    imprime_colorido(a->dir);
}

void imprime(TAB_cor*a){
    if(!a) return;
    imprime(a->esq);
    printf("%d",a->info);
    imprime(a->dir);
    return;
}

void libera(TAB_cor*a){
    if(!a) return ;
    libera(a->esq);
    free(a);
    libera(a->dir);
    return;
}


int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x,ver;
    TAB_cor* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir na primeira\n\t2 - Imprimir a primeira\n\t3 - Colorir\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf(" %d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite o valor a ser inserido na primeira arvore: ");
            scanf(" %d", &x);
            printf("\n");
            raiz = insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            imprime(raiz);
            printf("\n");
            break;

        case 3:
            colore(raiz);
            imprime_colorido(raiz);
            break;


        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    libera(raiz);
    return 0;
}

