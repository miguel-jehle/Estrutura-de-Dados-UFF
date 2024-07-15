#include <stdio.h>
#include <stdlib.h>

int filho_1(int ind){
    return (3*ind) + sizeof(int);
}

int filho_2(int ind){
    return (3*ind) + (2*sizeof(int));
}

int filho_3(int ind){
    return (3*ind)+ (3*sizeof(int));
}

int pai(int ind){
    if(ind) return ((ind/sizeof(int))/3)*sizeof(int);
    return -1;
}

void maxheapfy(char* entrada, int tam, int ind){
    int f1 = filho_1(ind); 
    int f2 = filho_2(ind);
    int f3 = filho_3(ind);
    int maior_elem, aux, maior = ind;

    FILE* fp = fopen(entrada,"rb+");
    if(!fp) exit (1);
    fseek(fp,maior,SEEK_SET);
    fread(&maior_elem,sizeof(int),1,fp);

    if(f1 < tam){
        fseek(fp,f1,SEEK_SET);
        fread(&aux,sizeof(int),1,fp);
        if(aux > maior_elem){
            maior_elem = aux;
            maior = f1;
        }
    }
    if(f2 < tam){
        fseek(fp,f2,SEEK_SET);
        fread(&aux,sizeof(int),1,fp);
        if(aux > maior_elem){
            maior_elem = aux;
            maior = f2;
        }
    }
    if(f3 < tam){
        fseek(fp,f3,SEEK_SET);
        fread(&aux,sizeof(int),1,fp);
        if(aux > maior_elem){
            maior_elem = aux;
            maior = f3;
        }
    }
    if(maior != ind){
        int temp;
        fseek(fp,ind,SEEK_SET);
        fread(&temp,sizeof(int),1,fp);
        
        fseek(fp,maior,SEEK_SET);
        fwrite(&temp,sizeof(int),1,fp);

        fseek(fp,ind,SEEK_SET);
        fwrite(&maior_elem,sizeof(int),1,fp);

        fclose(fp);
        maxheapfy(entrada,tam,maior);
    }
    else fclose(fp);
}

void build_max_heap(char* entrada, int tam){
    int ult_pai = pai(tam - sizeof(int));
    for(int i = ult_pai; i >= 0; i = i -sizeof(int)){
        maxheapfy(entrada,tam,i);
    }
}

void heapsort(char* entrada){
    FILE* fp = fopen(entrada, "rb");
    if(!fp) exit(1);
    fseek(fp,0L,SEEK_END);
    int tam = ftell(fp);
    fclose(fp);

    build_max_heap(entrada,tam);
    for(int i = tam - sizeof(int); i >= 0; i = i - sizeof(int)){
        FILE* fp = fopen(entrada, "rb+");
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

        maxheapfy(entrada,i,0);
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

