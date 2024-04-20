/*
-> Escrever uma função em C que, dada uma árvore binária qualquer, retorne, num vetor, todos os elementos maiores que N. A função deve ter o seguinte protótipo: int* mN(TABB*a, int N, int *tam);
*/
#include"TABB.c"

void insere_in_vet(TABB*a, int* resp,int* tam){
    for(int i = 0; i < (*tam); i++){
        resp[i] = a->info;
        a = a->dir;
    }
}

int conta_no(TABB*a){
    int cont = 0;
    while(a->dir){
        a = a->dir;
        cont++;
    }
    return cont;
}

int* mN(TABB*a, int N, int *tam){
    if(!a) return 0;
    TABB *no_N = TABB_busca(a,N);
    if(!no_N) return 0;
    (*tam) = conta_no(no_N);
    int* resp = (int*)malloc(sizeof(int*)*(*tam));
    insere_in_vet(no_N->dir,resp, tam);
    return resp;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, n, tam;
    TABB* raiz = NULL;
    int *resp;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista de valores maiores que N\n");
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
            resp = mN(raiz,n,&tam);
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