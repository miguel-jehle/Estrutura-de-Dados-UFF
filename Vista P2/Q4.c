void min_heapfy(int * vet, int n, int k, int pos){
    int menor = pos;

    for(int i =1; i < k; i++){
        int filho = filho_i(pos,k,i);
        if(filho < n && vet[filho] < vet[menor]) menor = filho;
        if(filho >= n) break;
    }
    if( menor != pos){
        int temp = vet[menor];
        vet[menor] = vet[pos];
        vet[pos] = temp;
        min_heapfy(vet,n,k,menor);
    }
}