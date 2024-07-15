#include<stdio.h>
#include<stdlib.h>

int filho_i(int ind, int k, int i){
    return (ind*k) + (i*sizeof(int));
}

int pai(int ind, int k){
    if(ind > 0) return (ind/sizeof(int))/k *sizeof(int);
}

void maxheapfy(char* entrada, int tam,int ind, int k){
    int aux, maior = ind, maior_ele;
    FILE* fp = fopen(entrada,"rb+");
    if(!fp) exit(1);
    fseek(fp,ind,SEEK_SET);
    fread(&maior_ele,sizeof(int),1,fp);

    for(int i = 1; i <= k; i++){
        int filho = filho_i(ind,k,i);
        if(filho < tam){
            fseek(fp,filho,SEEK_SET);
            fread(&aux,sizeof(int),1,fp);
            if(aux > maior_ele){
                maior_ele = aux;
                maior = filho;
            }
        }
    }

    if(ind != maior){
        int tmp;

        fseek(fp,ind,SEEK_SET);
        fread(&tmp,sizeof(int),1,fp);

        fseek(fp,maior,SEEK_SET);
        fwrite(&tmp,sizeof(int),1,fp);

        fseek(fp,ind,SEEK_SET);
        fwrite(&maior_ele,sizeof(int),1,fp);
        fclose(fp);

        maxheapfy(entrada,tam,maior,k);
    }
    else fclose(fp);
}

void build_max_heap(char* entrada, int tam, int k){
    int ult_pai = pai(tam-sizeof(int),k);
    for(int i = ult_pai; i >= 0; i -= sizeof(int)){
        maxheapfy(entrada,tam,i,k);
    }
}

void heapsort(char* entrada,int k){
    FILE* fp = fopen(entrada,"rb");
    if(!fp) exit (1);
    fseek(fp,0L,SEEK_END);
    int tam = ftell(fp);
    fclose(fp);

    build_max_heap(entrada,tam,k);
    for(int i = tam - sizeof(int); i >= 0; i -= sizeof(int)){
        fp = fopen(entrada,"rb+");
        if(!fp) exit(1);

        int prim, ult;

        fread(&prim,sizeof(int),1,fp);
        fseek(fp,i,SEEK_SET);
        fread(&ult,sizeof(int),1,fp);
        fseek(fp,0L,SEEK_SET);
        fwrite(&ult,sizeof(int),1,fp);
        fseek(fp,i,SEEK_SET);
        fwrite(&prim,sizeof(int),1,fp);

        fclose(fp);
        maxheapfy(entrada,i,0,k);
    }
}

int main(void){
  char* nome_arq = "entrada.bin";
  int nvet, i = 0, aux,k;
  printf("Digite o numero de elementos distintos do arquivo: ");
  scanf("%d", &nvet);
  int vet[nvet];
  while (i < nvet){
    scanf("%d", &aux);
    if(aux >= 0){
      int j;
      for(j = 0; j < i; j++) if (vet[j] == aux) break;
      if (j == i) vet[i++] = aux;
    }
  }

  FILE *fp = fopen(nome_arq, "wb");
  if(!fp) exit(1);
  fwrite(&vet, sizeof(int), nvet, fp);
  fclose(fp);
 
  printf("Digite o k: ");  
  scanf("%d", &k);
  heapsort(nome_arq,k);
  int resp[nvet];
  fp = fopen(nome_arq, "rb");
  if(!fp) exit(1);
  fread(&resp, sizeof(int), nvet, fp);
  fclose(fp);

  printf("\nVerificacao da ordenacao...\n");
  for(i = 0; i < nvet; i++) printf("(%d):\t%d\t%d\n", i + 1, vet[i], resp[i]);

  return 0;
}