/*
(Q1) Escreva um programa em C que leia dois arquivos binários “a.bin” e “b.bin” contendo
palavras distintas descritas por 10 caracteres e produza um terceiro arquivo c.bin. No arquivo
“c.bin”, cada um de seus registros contém um par ordenado de palavras, onde a primeira palavra é
proveniente de “a.bin” e a segunda de “b.bin”. Como resultado do processamento, o arquivo
“c.bin” deve conter todos os pares ordenados formados por palavras dos dois arquivos de entrada
(o resultado é o produto cartesiano dos dois conjuntos). Obs.: todo processamento deve ser feito em
memória secundária.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void pares_ordenados(char* ArqA, char* ArqB, char* ArqC){
    FILE* fa = fopen(ArqA, "rb");
    FILE* fb = fopen(ArqB,"rb");
    FILE* fc = fopen(ArqC, "wb");
    char br = '\n';
    if((!fa)||(!fb)||(!fc)) exit(1);
    int ra,rb;
    char na[10], nb[10];

    ra = fread(na,sizeof(char),10,fa);
    rb = fread(nb,sizeof(char),10,fb);
    
    while(ra && rb){
        fwrite(na, sizeof(char), 10, fc);
        fwrite(nb, sizeof(char),10, fc);
        fputc('\n', fc);
        ra = fread(na,sizeof(char),10,fa);
        rb = fread(nb,sizeof(char),10,fb);
    }
    fclose(fa);
    fclose(fb);
    fclose(fc);
}

int main(void){
    pares_ordenados("ArqA.bin","ArqB.bin","ArqC.bin");
    return 0;
}


