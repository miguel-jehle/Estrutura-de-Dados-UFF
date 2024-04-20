#include"TAB.c"

/*CASO QUEBRADO: 20
                    22
                        13

Ou caso tenha somente pares, por algum motivo o código quebra, não pude identificar
*/

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

TAB* removedor_nos(TAB *a, int x){
    if(!a) return NULL;
    if(a->info == x){
        //Caso seja folha
        if(!a->dir && !a->esq){ 
            free(a);
            return NULL;
        }//Caso tenha 2 filhos
        if(a->esq && a->dir){
            TAB* aux = a->esq;
            while(aux->esq) aux = aux->esq;
            a->info = aux->info;
            aux->info = x;
            removedor_nos(a->esq,x);
            return a;
        }else{ // Caso tenha um filho
            TAB* f;
            if(a->esq) f = a->esq;
            else f =a->dir;
            free(a);
            if(f->info % 2 == 0) f = removedor_nos(f,f->info);
            return f;
        }
    }else{
        if(a->esq) a->esq = removedor_nos(a->esq,x);
        if(a->dir) a->dir = removedor_nos(a->dir,x);
        return a;
    }
}

TAB* retira_pares(TAB* a){
    if(!a) return a;
    //Faço a verificação de baixo para cima, ou seja, vou até os nós filhos antes de fazer a verificação
    if(a->esq) a ->esq = retira_pares(a->esq);
    if(a->dir) a->dir = retira_pares(a->dir);
    if(a->info % 2 == 0) a = removedor_nos(a,a->info);
    return a;
}


int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TAB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Retirar todos os pares\n");
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
            raiz = insere(raiz,x);
            break;
        
        case 2:
            printf("\tA arvore eh: ");
            TAB_imp_sim(raiz);
            printf("\n");
            break;

        case 3:
            raiz = retira_pares(raiz);
            printf("\tPares retirados com sucesso!!!");
            printf("\n");
            if(raiz){
                printf("\tA arvore agora sem pares eh: ");
                TAB_imp_sim(raiz);
                printf("\n");

            }else{
                printf("\tTodos os nos foram apagados!");
                printf("\n");
            }
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TAB_libera(raiz);
    return 0;
}