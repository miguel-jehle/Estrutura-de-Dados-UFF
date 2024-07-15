// (Q4) Dados dois arquivos texto que representam conjuntos inteiros (isto é, não há elementos repetidos nos arquivos),
// um elemento por linha, e fazendo SOMENTE uma leitura em cada arquivo, faça cada uma das questões utilizando 
// tabelas hash em memória secundária:
// (a) interseção dos conjuntos: void inter(char* arq1, char* arq2, char* saida);


// typedef struct num{
//   int num, prox, qtde;
// }TNUM;

// int TH_hash(int mat, int tam);
// void TH_inicializa(char *tabHash, int tam);
// TNUM* TH_busca(char *tabHash, char *dados, int tam, int num);
// void TH_retira(char *tabHash, char *dados, int tam, int num);
// void TH_insere(char *tabHash, char *dados, int tam, int num);
// void TH_imprime (char *tabHash, char *dados, int tam);

#include "../TH.c"

void inter(char* arq1, char* arq2, char* saida){
    FILE * fp1 = fopen(arq1, "rt");
    FILE * fp2 = fopen(arq2, "rt");
    if(!fp1 || !fp2) exit(1);
    int tam;
    printf("Qual o tamanho da hash? ");
    scanf("%d", &tam);
    TH_inicializa("HashA.bin", 5);
    //FILE * fs = fopen(saida, "wt");
    int tmp;
    while(fscanf(fp1, "%d", &tmp) == 1){
        TH_insere("HashA.bin", "dadosA.bin", tam, tmp);
    }
    while(fscanf(fp2, "%d", &tmp) == 1){
        TH_insere("HashA.bin", "dadosA.bin", tam, tmp);
    }
    //hash preenchida
    //analisa a qtd, se for maior que 1, é pq repetiu. ent escreve em saída
    int i=0;
    FILE * hash = fopen("HashA.bin", "rb");
    while(i<tam){
        //vendo cada idice da hash
        TNUM aux;
        int end;
        fread(&end, sizeof(int), 1, hash);
        if(end != -1){
            FILE * dados = fopen("dadosA.bin", "rb");
            fseek(dados, end, SEEK_SET); //a partir do inicio
            fread(&aux, sizeof(TNUM), 1, dados);
            if(aux.qtde > 1){
                FILE * fs = fopen(saida, "at");
                fprintf(fs, "%d\n", aux.num);
                fclose(fs);
            }
            while(aux.prox != -1){
                fseek(dados, aux.prox, SEEK_SET);
                fread(&aux, sizeof(TNUM), 1, dados);
                if(aux.qtde > 1){
                    FILE * fs = fopen(saida, "at");
                    fprintf(fs, "%d\n", aux.num);
                    fclose(fs);
                }

            }
            fclose(dados);
        }
        i++;
    }
    fclose(hash);


}

int main(){
    remove("saida.txt");
    inter("arq1.txt", "arq2.txt", "saida.txt");
    return 0;
}