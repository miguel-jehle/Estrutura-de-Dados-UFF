//Em um grafo, crie uma fonte e um sumidouro, sendo uma fonte um nó que aponta para todos os outros e sumidouro um que é apontado para todos os outros.
//OBS: A fonte não aponta para o sumidouro!!!
//id da fonte: -inf
//id do sumidouro: +inf 
#include<limits.h>

#define fonte INT_MIN
#define sumidouro INT_MAX

#include"TG.c"

TG* cria_fs(TG* g){
   if(!g) return NULL;
   g = TG_ins_no(g, fonte);
   g = TG_ins_no(g, sumidouro);
   TG* f = TG_busca_no(g,fonte);
   TG* s = TG_busca_no(g,sumidouro);

   //Criação da fonte
   TG* aux = g;
   while(aux){
        if((aux->id_no != fonte) && (aux->id_no != sumidouro)) TG_ins_um_sentido(g,fonte,aux->id_no);
        aux = aux->prox_no;
   }

   //Criação do sumidouro
   aux = g;
   while(aux){
        if((aux->id_no != fonte) && (aux->id_no != sumidouro)) TG_ins_um_sentido(g,aux->id_no,sumidouro);
        aux = aux->prox_no;
   }
   return g;
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x, y,z;
    TG* grafo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Criar fonte e sumidouro\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("\n\tDigite o no a ser inserido no grafo: ");
            scanf("%d", &x);
            printf("\n");
            grafo = TG_ins_no(grafo,x);
            break;
        
        case 2:
            printf("\n\tDigite o no que deseja inserir a aresta: ");
            scanf("%d", &x);
            printf("\n");
            printf("\n\tDigite o no que deseja conectar com o no inserido: ");
            scanf("%d", &y);
            printf("\n");
            TG_ins_aresta(grafo,x,y);

        case 3:
            printf("\n\tO grafo eh: ");
            TG_imp_rec(grafo);
            printf("\n");
            break;
        case 4:
            grafo = cria_fs(grafo);
            printf("\n\tO grafo ficou: ");
            TG_imp_rec(grafo);
            printf("\n");
            break;

        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    TG_libera(grafo);
    return 0;
}