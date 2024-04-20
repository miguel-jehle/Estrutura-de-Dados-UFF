/*
    VAMOS CRIAR AGORA UMA FUNÇÃO PARA RETIRAR TODOS OS NOS FOLHAS DA NOSSA ÁRVORE BINÁRIA!!!
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
    if(!raiz) return 0; 
    if(!raiz->direita && !raiz->esquerda) return 1; 
    int esq = calc_folhas(raiz->esquerda); 
    int dir = calc_folhas(raiz->direita); 
    return esq + dir; 
}

//--------REMOVE FOLHA ------------------------------------------------------------------------------------------------------------------------------------
ArvNo* remover(ArvNo *raiz, int num){
    if(!raiz){ //Verificando se o nó de fato existe
        printf("\tNo nao encontrada!!!\n");
        return NULL;
    }else { //Vamos realizar a busca pelo nó
        if (raiz->valor == num){ //Caso encontremos, vamos ver se ele é folha ou não
            if (!raiz->direita && !raiz->esquerda){ //Se for folha, basta dar free e retornar NULL
                free(raiz);
                printf("\tNo encontrado e removido!\n");
                return NULL;
            }else{ //Caso não seja folha, vemos se possui 1 ou 2 filhas
                if (raiz->direita && raiz->esquerda){ //Se tiver 2 filhos, faremos:

                //Próxima AUla!!

                }else{ //Caso não, tem somente 1 filho e faremos:
                    ArvNo *aux; //Crio um nó auxiliar que servirá como retorno após apagar o nó pai

                    //Verifico qual filho a raiz tem, a esquerda ou a direita e aponto o aux para o filho existente
                    if (raiz->direita) aux = raiz->direita;
                    else aux = raiz->esquerda;

                    //Com o aux apontando para o filho, podemos liberar a raiz
                    free(raiz);
                    printf("\tNo encontrado e removido!!!\n");

                    //Retornamos o aux, ele será substituido como direita ou esquerda de algum nó, visto que ele é o retorno da chamada recursiva das linhas abaixo
                    return aux;
                }
            }
        }else { //Caso não tenhamos encontrado, chamamos a função para o proximo nó, buscando baseado no valor do nó atual com relação ao número
            if (num < raiz->valor) raiz->esquerda = remover(raiz->esquerda, num); //O raiz seta algo, recebe o retorno da função remove
            if (num > raiz-> valor) raiz-> direita = remover(raiz->direita, num);
            return raiz;
        }

    }
    
}

//--------------------------------------------------------------------------------------------------------------------------------------------

int main(void){

    ArvNo *raiz = NULL;
    ArvNo *busca = NULL;

    int opcao,valor,altura, nos, folhas;
    
    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Buscar\n\t 4 - Altura\n\t 5 - Nos\n\t 6 -Folhas\n\t 7 - Remover\n");
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
        case 7:
            printf("\n\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            printf("\n");
            raiz = remover(raiz, valor);
            break;
        default:
            if (opcao != 0) printf("Opcao invalida!!!");
        }

    }while (opcao);

    libera(raiz);

    return 0;
}
