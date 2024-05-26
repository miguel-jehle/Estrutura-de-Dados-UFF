/*
Retornar um vetor entre dois numeros (M e N), de uma AVL, onde possui tais valores contidos da árvore. Sendo este vetor, ordenado, sem metodos de ordenacao disponiveis (nao pode usar, ou implementar o proprio).
*/

//Neste caso estou fazendo considerando que a chamada recebe um ponteiro para 
#include"TABB.c"
TABB* insere(TABB* a, int x){
    if(!a){
        TABB* novo = (TABB*)malloc(sizeof(TABB));
        novo ->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } 
    if(x > a->info) a->dir = insere(a->dir,x);
    if(x < a->info) a->esq = insere(a->esq,x);
    return a;
}

int tam(TABB* a){
    if(!a) return 0;
    return tam(a->dir) + tam(a->esq) + 1;
}

void percorre(TABB* a, int* v, int m, int n, int* pos){
    if(!a) return;
    percorre(a->esq,v,m,n,pos);
    if(a->info > m && a->info < n){
        v[(*pos)] = a->info;
        (*pos)++;
    }
    percorre(a->dir,v,m,n,pos);
    return;
}

int* vet_mn(TABB* a, int m, int n, int* pos){
    int t = tam(a);
    int *vet = (int*)malloc(sizeof(int)*t);
    percorre(a,vet,m,n,pos);
    vet = realloc(vet,sizeof(int) * (*pos));
    return vet;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x,n,na,ma,t,m;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista ordenada\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao){
        case 1:
            printf("\n\tDigite o valor a ser inserido na arvore: ");
            scanf("%d", &x);
            printf("\n");
            raiz = insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            TABB_imp_sim(raiz);
            printf("\n");
            break;
        
        case 3:
            printf("\n\tDigite o valor do limite inferior: ");
            scanf("%d", &ma);
            printf("\n");
            printf("\n\tDigite o valor do limite superior: ");
            scanf("%d", &na);
            printf("\n");
            t = tam(raiz);
            m = 0;
            int * resp;
            resp = vet_mn(raiz,ma,na,&m);
            printf("\n\tO vetor dos valores maiores que m e menores que n eh: \n");
            for(int i = 0; i < m; i++) printf("\tElemento %d: %d\n",i,resp[i]);
            printf("\n");
            free(resp);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TABB_libera(raiz);
    return 0;
}