//Fazer uma minheapfy para heap binária em memória secundária.

#include<stdio.h>
#include<stdlib.h>

int esq(int ind){
    return 2*ind + sizeof(int);
}

int dir(int ind){
    return 2*(ind + sizeof(int));
}

int pai(int ind){
    if(ind> 0)return ((ind/sizeof(int))/2)*sizeof(int);
    return -1;
}

void minheapfy(char* entrada, int tam, int ind){
    FILE* fp = fopen(entrada,"rb+");
    if(!fp) exit(1);

    int e = esq(ind), d = dir(ind), menor = ind, aux, menor_elem;
    fseek(fp,menor,SEEK_SET);
    fread(&menor_elem,sizeof(int),1,fp);

    if(e < tam){
        fseek(fp,e,SEEK_SET);
        fread(&aux,sizeof(int),1,fp);
        if(aux < menor_elem){
            menor_elem = aux;
            menor = e;
        }
    }

    if(d < tam){
        fseek(fp,d,SEEK_SET);
        fread(&aux,sizeof(int),1,fp);
        if(aux < menor_elem){
            menor_elem = aux;
            menor = e;
        }
    }

    if(menor != ind){
        int temp;

        fseek(fp,ind,SEEK_SET);
        fread(&temp,sizeof(int),1,fp);

        fseek(fp,menor,SEEK_SET);
        fwrite(&temp,sizeof(int),1,fp);

        fseek(fp,ind,SEEK_SET);
        fwrite(&menor_elem,sizeof(int),1,fp);

        fclose(fp);
        minheapfy(entrada,tam,menor);
    } 
    else fclose(fp);
}

void build_min_heap(char* entrada, int tam){
    int ult_pai = pai(tam - sizeof(int));
    for(int i = ult_pai; i >=0; i -=sizeof(int)){
        minheapfy(entrada,tam,i);
    }
}

void heapsort(char* entrada){
    FILE* fp = fopen(entrada,"rb");
    if(!fp) exit(1);
    fseek(fp,0L,SEEK_END);
    int tam = ftell(fp);
    fclose(fp);

    build_min_heap(entrada,tam);
    for(int i = tam - sizeof(int); i >= 0; i-=sizeof(int)){
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

        minheapfy(entrada,i,0);
    }
}

int main(void){
  char* nome_arq = "entrada.bin";
  int nvet, i = 0, aux;
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

  heapsort(nome_arq);
  int resp[nvet];
  fp = fopen(nome_arq, "rb");
  if(!fp) exit(1);
  fread(&resp, sizeof(int), nvet, fp);
  fclose(fp);

  printf("\nVerificacao da ordenacao...\n");
  for(i = 0; i < nvet; i++) printf("(%d):\t%d\t%d\n", i + 1, vet[i], resp[i]);

  return 0;
}