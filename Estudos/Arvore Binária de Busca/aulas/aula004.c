/*
    VAMOS CRIAR AGORA UMA FUNÇÃO PARA CALCULAR QUANTOS NOS TEM NA NOSSA ÁRVORE BINÁRIA!
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
    if(dir > esq) return dir + 1; //Ambos os "+ 1" são colocados aqui pois queremos contar com a chamada que foi realizada para chegar no nó analisado, para isso precisamos considerar o + 1
}

//---------cALCULO DE NOS-----------------------------------------------------------------------------------------------------------------------
int calc_no (ArvNo *raiz){
    if(!raiz) return 0;
    if(raiz->direita == NULL && raiz->esquerda == NULL) return 1;
    int esq = calc_no(raiz->esquerda);
    int dir = calc_no(raiz->direita);
    return 1 + dir + esq; //O 1 nesse caso foi colocado para que contemos tambem o nó responsável pela chamada, para contabilizarmos sempre o nó , sua esquerda e sua direita

    /*
        Uma versão alternativa vista em uma video aula, seria utilizando o operador ternário e uma lógica mais simples
        
        return (raiz == NULL) ? 0 : 1 + calc_no (raiz-> direita) + calc_no (raiz->esquerda);

       - O ternário (?) consiste em fazer uma afirmação, caso seja verdadeira ocorre oque está antes do ":" e caso falsa oque está depois.
       - Note que a lógica também é mais simples, caso o nó não exista, 0, caso exista, calculamos tudo a sua esquerda e direita + ele mesmo.
    */
}

//--------------------------------------------------------------------------------------------------------------------------------------------

int main(void){

    ArvNo *raiz = NULL; //Crio um ponteiro que apontará para raiz, inicialmente nulo.
    ArvNo *busca = NULL;
    int opcao,valor,altura, nos;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Buscar\n\t 4 - Altura\n\t 5 - Nos\n");
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
            printf("\n\tDigite um valor a ser encontrado: \n");
            scanf("%d", &valor);
            busca = buscar(raiz, valor);
            if(busca) printf("\tValor encontrado: %d \n", busca->valor);
            else printf("\tValor nao encontrado\n");
            break;
        case 4:
            altura = calc_altura(raiz);
            printf("\n\tA altura da arvore inserida eh: %d\n", altura);
            break;
        case 5:
            nos = calc_no(raiz);
            printf("\n\tA quantidade de nos da arvore inserida eh: %d\n", nos);
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);

    return 0;
}
