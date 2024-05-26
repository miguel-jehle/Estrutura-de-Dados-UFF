/*
(Q2) Escreva um programa em C que receba como entrada um arquivo binário de clientes
“clientes.bin” e, sem ler todos os registros para memória, permita a consulta dos dados de um
cliente em função do seu CPF. Considere que o formato de cada registro é dado pelos seguintes
campos: nome – char (40), CPF – char(11), conta_corrente (int), agencia
(int), saldo (float).
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct pessoa{
    char nome[41];
    char cpf[12];
    int conta_corrente;
    int agencia;
    float saldo;
}TP;


void ver_CPF(char* ArqEnt, char* CPF){
    FILE* fp = fopen(ArqEnt, "rb");
    if(!fp) exit(1);
    TP ver;
    int r = fread(&ver,sizeof(TP),1,fp);    
    while(r == 1){
        if(strcmp(CPF,ver.cpf)== 0) break;
        r = fread(&ver,sizeof(TP),1,fp);
        printf("%d\n", ver.cpf);
    }
    if(r != 1){
        printf("Este cliente nao consta nos nossos bancos");
        exit(1);
    }
    printf("O cliente de CPF: %s possui:\n",CPF);
    printf("Nome: %s\n",ver.nome);
    printf("Conta corrente: %d\n", ver.conta_corrente);
    printf("Agencia: %d\n", ver.agencia);
    printf("Saldo: %.2f\n", ver.saldo);
    fclose(fp);
}

void cria_binario(char* Arq_Saida){
    FILE* fs = fopen(Arq_Saida,"wb");
    if(!fs) exit(1);
    int ver = 1;
    TP pessoa;
    do{
        printf("Digite o nome: ");
        scanf("%s",pessoa.nome);
        printf("Digite o CPF: ");
        scanf("%s", pessoa.cpf);
        printf("Digite o numero da conta corrente: ");
        scanf("%d", &pessoa.conta_corrente);
        printf("Digite o numero da agenica: ");
        scanf("%d", &pessoa.agencia);
        printf("Digite o saldo da conta");
        scanf("%f",&pessoa.saldo);
        fwrite(&pessoa,sizeof(TP),1,fs);
        printf("Deseja inserir mais uma pessoa? Digite 1 para sim e 0 para nao: ");
        scanf("%d",&ver);
        if(!ver) break;
    }while(ver == 1);
    fclose(fs);
}

int main(void){
    //cria_binario("clientes.bin");
    FILE *fp = fopen("clientes.bin", "rb");
    if(!fp) exit(1);
    TP ver;
    ver_CPF("clientes.bin","56789012345");
    fclose(fp);
    return 0;
}