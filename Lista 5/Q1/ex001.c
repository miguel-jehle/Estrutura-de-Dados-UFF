/*
(Q1) Desenvolva um procedimento que receba o nome de um arquivo texto e retire deste texto
palavras consecutivas repetidas. O seu programa deve retornar, no arquivo de saída, informado
como parâmetro dessa função, a resposta desta questão. Por exemplo, se o conteúdo de um arquivo
texto for: "Isto e um texto texto repetido repetido repetido . Com as repeticoes
repeticoes fica fica sem sem sentido . Sem elas elas elas melhora melhora um um
pouco .", a saída do seu programa será um arquivo com o seguinte texto: "Isto e um texto
repetido . Com as repeticoes fica sem sentido . Sem elas melhora um um pouco ."
- void RetRepet(char *ArqEnt, char *ArqSaida).
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void RetRepet(char *ArqEnt, char *ArqSaida){
    char atual[30];
    char proximo[30];
    int r1, r2;
    FILE* fp1 = fopen(ArqEnt, "r");
    FILE* fp2 = fopen(ArqEnt, "r");
    FILE* fout = fopen(ArqSaida, "w");
    if(!fp1 || !fp2 || !fout) exit(1);
    r1 = fscanf(fp1,"%s",atual);
    r2 = fscanf(fp2,"%s",proximo);
    r2 = fscanf(fp2,"%s",proximo);
    while(1){
        if(r2 != 1){
            fprintf(fout,"%s",atual);
            break;
        }
        if(strcmp(atual,proximo) != 0) fprintf(fout,"%s ",atual);
        r1 = fscanf(fp1,"%s",atual);
        r2 = fscanf(fp2,"%s",proximo);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fout);
    return;
}

int main(void){
    RetRepet("entrada.txt","saida.txt");
    return 0;
}
