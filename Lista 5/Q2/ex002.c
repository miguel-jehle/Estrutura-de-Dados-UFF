/*
    (Q2) Implemente um algoritmo que receba como parâmetro de entrada, o nome de um arquivo
texto, cujo conteúdo são o nome do aluno e as duas notas dos alunos do curso, uma em cada linha, e
que ordene o arquivo de saída em ordem crescente pela média do aluno. Isto é, se eu tiver como
entrada o arquivo: "P C/10.0/10.0-J J/3.0/4.0-G G/7.0/7.0-A A/0.5/1.5-I I/5.0/6.0", a
saída será um arquivo com o seguinte texto: "A A/1.0-J J/3.5-I I/5.5-G G/7.0-P C/10.0" -
void media(char *ArqEnt, char *ArqSaida).
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct aluno{
    char nome[31];
    float nota1;
    float nota2;
    float media;
}TA;

int compara(const void *a, const void *b){
    TA* pa = (TA*)a;
    TA* pb = (TA*)b;

    if(pa->media < pb->media) return -1;
    else return 1;
}

void media(char *ArqEnt, char *ArqSaida){
    FILE* fp = fopen(ArqEnt,"r");
    if(!fp) exit(1);

    TA aluno;
    int r,cont = 0;
    while(!feof(fp)){
        fscanf(fp,"%30[^/]/%f/%f",aluno.nome,&aluno.nota1,&aluno.nota2);
        cont++; 
    } 

    TA *vet = (TA*)malloc(sizeof(TA)*cont);
    rewind(fp);

    int i = 0;
    while(fscanf(fp,"%30[^/]/%f/%f",aluno.nome,&aluno.nota1,&aluno.nota2) == 3){
        strcpy(vet[i].nome, aluno.nome);
        vet[i].nota1 = aluno.nota1;
        vet[i].nota2 = aluno.nota2;
        vet[i].media = (aluno.nota1 + aluno.nota2)/2;
        i++;        
    }
    qsort(vet,cont,sizeof(TA),compara);
    FILE* fout = fopen(ArqSaida, "w");
    if(!fout) exit(1);
    for(int i = 0; i < cont; i++){
        fprintf(fout,"%s teve media: %.1f\n", vet[i].nome, vet[i].media);
    }
    fclose(fout);
    fclose(fp);
    free(vet);
}

int main(void){
    media("Alunos.txt","AlunosSaida.txt");
    return 0;
}