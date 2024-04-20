/*
    VAMOS CRIAR AGORA UMA FUNÇÃO PARA CALCULAR QUANTOS NOS FOLHA TEM NA NOSSA ÁRVORE BINÁRIA!
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

//---------cALCULO DE NOS-----------------------------------------------------------------------------------------------------------------------
int calc_no (ArvNo *raiz){
    if(!raiz) return 0;
    if(raiz->direita == NULL && raiz->esquerda == NULL) return 1;
    int esq = calc_no(raiz->esquerda);
    int dir = calc_no(raiz->direita);
    return 1 + dir + esq;
}

//---------CALCULO DE FOLHAS-----------------------------------------------------------------------------------------------------------------
int calc_folhas(ArvNo *raiz){
    if(!raiz) return 0; //Caso não exista raiz, é zero
    if(!raiz->direita && !raiz->esquerda) return 1; //Se um nó não tiver nada nem a esquerda nem a direita, ele é uma folha e retorno 1 para contabiliza-lo 
    int esq = calc_folhas(raiz->esquerda); //Se chegamos aqui, o nó existe e não é folha, então chamo para a esquerda para verificar se o da sua esquerda é folha
    int dir = calc_folhas(raiz->direita); // Aplico a mesma lógica para a direita
    return esq + dir; //Somando a quantidade de nós folha da esquerda e da direita da raiz da chamada, mas diferente do calculo de nos, não queremos contar nó resposável pela chamada, portanto não temos o "+ 1".
}

//--------------------------------------------------------------------------------------------------------------------------------------------

int main(void){

    ArvNo *raiz = NULL;
    ArvNo *busca = NULL;
    int opcao,valor,altura, nos, folhas;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Buscar\n\t 4 - Altura\n\t 5 - Nos\n\t 6 -Folhas\n");
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
        case 6:
            folhas = calc_folhas(raiz);
            printf("\n\tA quantidade de nos folha da arvore inserida eh: %d\n", folhas);
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);

    return 0;
}
