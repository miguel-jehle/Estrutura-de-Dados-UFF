//APRENDENDO A CRIAR E INSERIR EM UMA ÁRVORE BINÁRIA

//Quero inicializar uma árvore que da seguinte forma
//              50 (raiz)
//        25         100
//            30

#include<stdio.h>
#include<stdlib.h>

//Precisamos criar uma struct que servirá como base para os nós da nossa árvore, onde ele possui um ponteiro para esquerda, um para direita e um valor

typedef struct no
{
    int valor;
    struct no *esquerda; 
    struct no *direita;      
    
}ArvNo;

//--------INSERÇÃO--------------------------------------------------------------------------------------------------------------
ArvNo *inserir(ArvNo *raiz, int num){
    if (!raiz){
        ArvNo *novo = malloc(sizeof(ArvNo));
        novo->valor = num;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo;
    }
    if (num > raiz->valor) raiz->direita = inserir(raiz->direita, num);
    if (num < raiz ->valor) raiz->esquerda = inserir(raiz->esquerda,num);
    return raiz;
}

//--------IMPRIMIR---------------------------------------------------------------------------------------------------------------
void imprimir(ArvNo *raiz){
    if (!raiz) return;
    imprimir(raiz->esquerda);
    printf("%d ",raiz->valor);
    imprimir(raiz->direita);
}

int main(void){

    ArvNo *raiz = NULL; //Crio um ponteiro que apontará para raiz, inicialmente nulo.

    int opcao,valor;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\n\t Digite um valor: ");
            scanf("%d",&valor);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf("\n\t A impressao ordenada eh: ");
            imprimir(raiz);
            printf("\n");
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);


    return 0;
}