//Percorra uma TAB e retorne um vetor contendo os valores menores que n.

#include"TABB.c"

int tamanho(TABB* a){
    if(!a) return 0;
    return tamanho(a->esq) + tamanho(a->dir) + 1;
}

int* mn_aux(TABB* a, int* v, int* pos, int n){
    if(!a) return v;
    v = mn_aux(a->esq,v,pos,n);
    if(a->info < n) v[(*pos)++] = a->info;
    v = mn_aux(a->dir,v,pos,n);
    return v;
}

int* mn(TABB* a, int n){
    if(!a) return NULL;
    int pos = 0;
    int t = tamanho(a);
    int* vet = (int*)malloc(sizeof(int)*t);
    vet = mn_aux(a,vet,&pos,n);
    vet = realloc(vet,sizeof(int)*pos);
    for(int i = 0; i < pos; i++) printf("\t%d\n",vet[i]);
    return vet;
}

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

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x,n,na,ma,t,m;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Vetor de valores menores que n\n");
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
            printf("\n\tDigite o valor de n: ");
            scanf("%d", &ma);
            printf("\n");
            int * resp;
            resp = mn(raiz,ma);
            if(resp) printf("\n\tOK!");
            else printf("\n\tDeu ruim!");
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

