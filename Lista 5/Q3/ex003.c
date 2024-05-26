/*
(Q3) Escreva um procedimento que receba o nome de um arquivo texto, cujo conteúdo são valores
inteiros e imprima na tela o número de vezes que cada elemento aparece e em quais linhas – void
resumo(char *Arq).
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct linhas{
    int id_linha;
    struct linhas* prox_linha;;
}TL;

typedef struct dados{
    int id;
    int cont;
    TL* lista_linhas;
    struct dados* prox;
}TD;

void libera_linhas(TL* p){
    if(!p) return;
    libera_linhas(p->prox_linha);
    free(p);
    return;
}

void libera_elem(TD* l){
    if(!l) return;
    libera_linhas(l->lista_linhas);
    libera_elem(l->prox);
    free(l);
    return;
}

void print_linhas(TL* p){
    if(!p) return;
    printf("%d ",p->id_linha);
    print_linhas(p->prox_linha);
    return;
}

void print_elem(TD* l){
    if(!l) return;
    printf("O elemento %d apareceu %d vez(es) na(s) linha(s): ",l->id, l->cont);
    print_linhas(l->lista_linhas);
    puts("\n");
    print_elem(l->prox);
    return;
}

TL* insere_linha(TL* p, int linha){
    if(!p){
        TL* novo = (TL*)malloc(sizeof(TL*));
        novo->id_linha = linha;
        novo->prox_linha = NULL;
        p = novo;
        return p;
    }
    p->prox_linha = insere_linha(p->prox_linha,linha);
    return p;
}

TD* insere_elem(TD* l,int n, int linha){
    if(!l){
        TD* novo = (TD*)malloc(sizeof(TD));
        novo->cont = 1;
        novo->id = n;
        novo->prox = NULL;
        l = novo;
        novo->lista_linhas = NULL;
        novo->lista_linhas = insere_linha(novo->lista_linhas,linha);
        return l;
    }
    if(l->id != n) l->prox = insere_elem(l->prox,n,linha);
    if(l->id == n){
        l->lista_linhas = insere_linha(l->lista_linhas,linha);
        l->cont++;
    } 
    return l;
}

void resumo(char *Arq){
    FILE* fp = fopen(Arq,"r");
    if(!fp) exit(1);
    TD* l = NULL;
    int num, cont = 1;
    int r = fscanf(fp,"%d",&num);
    while(r == 1){
        l = insere_elem(l,num,cont);
        r = fscanf(fp,"%d",&num);
        cont++;
    }
    print_elem(l);
    libera_elem(l);
    fclose(fp);
}

int main(void){
    resumo("entrada.txt");
    return 0;
}