//Retorne todos os elementos de TAB em um vetor, ordenado, sem usar metodos de ordenação ou estruturas auxiliares.

#include "TAB.c"

TAB* insere(TAB* a, int x){
    if(!a){
        TAB* novo = (TAB*)malloc(sizeof(TAB));
        novo ->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } 
    if(x > a->info) a->dir = insere(a->dir,x);
    if(x < a->info) a->esq = insere(a->esq,x);
    return a;
}

int acha_menor(TAB*a, int* v,int *menor_ant, int menor_local){
    if(!a) return __INT_MAX__;
    menor_local = acha_menor(a->esq,v,menor_ant,menor_local);
    menor_local = acha_menor(a->dir,v,menor_ant,menor_local);
    if(a->info < menor_local && a->info > (*menor_ant)) return a->info;
    return menor_local;
}

void percorre(TAB* a, int* v, int n){
    int menor = -1;
    int menor_local;
    for(int i = 0; i<n;i++){
        menor_local = __INT_MAX__;
        menor_local = acha_menor(a,v,&menor,menor_local); //Este menor é o menor local
        menor = menor_local;
        v[i] = menor_local;
    }
    return;
}

int tam(TAB* a){
    if(!a) return 0;
    return (tam(a->esq) + tam(a->dir) + 1);
}

int* TAB2vet_ord(TAB* a){
    int n = tam(a);
    int* v = (int*)malloc(sizeof(int)*n);
    percorre(a,v,n);
    return v;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x,n;
    TAB* raiz = NULL;
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
            TAB_imp_sim(raiz);
            printf("\n");
            break;
        
        case 3:
            n = tam(raiz);
            int * resp;
            //int *resp = (int *) malloc(sizeof(int) * n);
            resp = TAB2vet_ord(raiz);
            printf("\n\tA lista ordenada com os elementos da arvore eh: \n");
            for(int i = 0; i < n; i++) printf("Elemento %d: %d\n",i,resp[i]);
            printf("\n");
            free(resp);
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    return 0;
}