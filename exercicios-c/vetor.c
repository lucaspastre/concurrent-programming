#include <stdio.h>

int main() {
    int vet[5] = {10, 20, 20, 30, 50};
    
    int i;
    float soma = 0;
    float media;
    
    for (i=0; i<5; i++) {
        soma += vet[i];
    }

    media = soma/5;

    printf("%.2f\n", media);

    return 0; //boa prática

}