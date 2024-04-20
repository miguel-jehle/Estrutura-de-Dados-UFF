#include "TABB.c"
#include<math.h>

int no_mn(TABB *a, int N){
    if(!a) return 0;
    if(a->info < N) return no_mn(a->esq,N) + no_mn(a->dir,N) + 1;
    else return no_mn(a->esq,N) + no_mn(a->dir,N);
}

void arv2vet_mn(TABB *a, int* vet, int* index, int N){ //Arvore, lista de inteiro, ponteiro de inteiro
    if(!a) return;
    arv2vet_mn(a->esq,vet,index, N); 
    if(a->info < N)vet[(*index)++] = a->info;
    arv2vet_mn(a->dir,vet,index, N);
}

int *mN(TABB* a , int N){
    int tam = no_mn(a, N);
    printf("%d",tam);
    int *resp = (int*)malloc(sizeof(int)*tam);
    int index = 0;
    arv2vet_mn(a,resp,&index,N);
    return resp;
}


int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, n, tam;
    TABB* raiz = NULL;
    int *resp;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista de valores menores que N\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf(" %d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite o valor a ser inserido na arvore: ");
            scanf(" %d", &x);
            printf("\n");
            raiz = TABB_insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            TABB_imp_sim(raiz);
            printf("\n");
            break;

        case 3:
            printf("\tDigite o valor de N: ");
            scanf("%d",&n);
            printf("\n");
            tam = no_mn(raiz,n);
            resp = mN(raiz,n);
            printf("\tAqui esta o vetor com valores menores que N: ");
            for(int i = 0; i < tam; i++) printf("%d ", resp[i]);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TABB_libera(raiz);
    return 0;
}


