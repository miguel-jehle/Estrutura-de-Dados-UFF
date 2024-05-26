#include"TAB.c"

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

TAB* maior_in_arv(TAB *a){
    if(!a) return NULL;
    int esq, dir;
    TAB *p_esq, *p_dir, *teste;

    //Verifico se existe algo a esquerda, para não fazer chamada recursiva e ter um "NULL->info" quebrando meu código
    if(!a->esq) esq = 0;
    else{
        p_esq = maior_in_arv(a->esq); //Como existe posso chamar tranquilamente
        esq = p_esq->info; //Salvo nesta variável, para na comparação sempre comparar duas variveis existentes.
    } 

    //Mesmo processo para direita.
    if(!a->dir) dir = 0;
    else{
        p_dir = maior_in_arv(a->dir);
        dir = p_dir->info;
    }

    //Caso não exista esquerda nem direita, retorno logo a raiz.
    if(esq == 0 && dir == 0) return a;

    //Como um deles existe, preciso pegar o maior para comparar com a raiz.
    if(esq > dir) teste = p_esq;
    else teste = p_dir;
    
    //Então comparo o maior deles com a raiz.
    if (teste->info > a->info) return teste;
    else return a;
}

TAB* maior_2(TAB*a){
    if(!a) return NULL;
    TAB* Esq, *Dir, *Aux;
    Esq->info = 0;
    Dir->info 
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TAB* raiz = NULL;
    TAB* maior = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Achar o maior\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
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
            maior = maior_in_arv(raiz);
            if(maior) printf("\n\tMaior encontrado com sucesso!!! ");
            else printf("\n\tOcorreu algum problema para obter o maior");
            printf("\n");
            printf("\n\tMaior valor: %d", maior->info);
            printf("\n");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    TAB_libera(maior);
    return 0;
}