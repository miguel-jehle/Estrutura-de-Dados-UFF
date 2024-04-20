/*
    Nesta aula , farei uma função de inserção sem retorno, e para isso, será necessário utilizar um ponteiro que aponta para o ponteiro que aponta para a raiz
    Sendo neste caso um ponteiro de ponteiro, necessitando ter todo o cuidado com relação aos conteúdos e endereços.

    Esse tipo de inserção é mais eficiente, além de sevir para me acostumar ao uso de ponteiro de ponteiro, não muito utilizado por mim até então
*/
          
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
void inserir(ArvNo **raiz, int num){
    if(*raiz == NULL){
        *raiz = malloc(sizeof(ArvNo)); //Como estamos acessando a raiz por meio de ponteiro de ponteiro, basta alocarmos o valor de memória para ela diretamente, ao em vez de criar um aux(novo)
        (*raiz)->direita = NULL;
        (*raiz)->esquerda = NULL; //Repare a necessidade dos parênteses nestas três linhas para que tenhamos acesso ao conteúdo de raiz e então as informações do struct, caso não houvesse, ele tentaria acessar o conteúdo de raiz->direita
        (*raiz)->valor = num;
    }
    //Aqui a maior dúvida pode ser relacionada à chamada no inserir dentro dos if. Para ficar mais intuitivo, basta olhar a chamada na main, na qual por ser PDP colocamos o endereço da raiz, mas aqui essa necessidade se soma a anterior anotada acima, de acessar o conteudo da raiz e então as infos da struct
    if(num < (*raiz)->valor) inserir(&((*raiz)->esquerda), num);
    if(num > (*raiz)->valor) inserir(&((*raiz)->direita), num);
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

int main(void){

    ArvNo *raiz = NULL;

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
            inserir(&raiz, valor); //Como estamos utilizando ponteiro de ponteiro na função, precisamos agora passar o endereço do ponteiro raiz para ela
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

    libera(raiz);

    return 0;
}