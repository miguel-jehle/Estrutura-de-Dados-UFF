/*
    VAMOS CRIAR AGORA UMA FUNÇÃO PARA REALIZAR UMA BUSCA NA NOSSA ÁRVORE BINÁRIA!
*/

#include<stdio.h>
#include<stdlib.h>

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

//--------LIBERA-------------------------------------------------------------------------------------------------------------------
void libera(ArvNo *raiz){
    if(!raiz) return;
    free(raiz->esquerda);
    free(raiz->direita);
    free(raiz);
}

//-------BUSCA--------------------------------------------------------------------------------------------------------------------------
ArvNo *buscar (ArvNo *raiz, int num){
if(!raiz) return NULL;
if (raiz->valor == num) return raiz;
if (num < raiz->valor) return buscar(raiz->esquerda, num);
if(num > raiz->valor) return buscar(raiz->direita, num);
}

//---------CALCULO DA ALTURA-----------------------------------------------------------------------------------------------------------------
int calc_altura(ArvNo *raiz){
    if(!raiz) return -1;
    if(raiz->direita == NULL && raiz->esquerda == NULL) return 0;
    int esq = calc_altura(raiz->esquerda);
    int dir = calc_altura(raiz->direita);
    if(esq > dir) return esq + 1;
    if(dir > esq) return dir + 1;
}


//--------------------------------------------------------------------------------------------------------------------------------------------

int main(void){

    ArvNo *raiz = NULL; //Crio um ponteiro que apontará para raiz, inicialmente nulo.
    ArvNo *busca = NULL;
    int opcao,valor,altura;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Buscar\n\t 4 - Altura\n");
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
        case 3: 
            printf("\n\t Digite um valor a ser encontrado: \n");
            scanf("%d", &valor);
            busca = buscar(raiz, valor);
            if(busca) printf("\tValor encontrado: %d \n", busca->valor);
            else printf("\tValor nao encontrado\n");
            break;
        case 4:
            altura = calc_altura(raiz);
            printf("\n\tA altura da arvore inserida eh: %d\n", altura);
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);

    return 0;
}
