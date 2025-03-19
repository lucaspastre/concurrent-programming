#include <stdio.h>

int main() {
    int vet[5];
    
    int i;
    
    for (i=0; i<5; i++) {
        printf("Insira um valor para a posicao %d do vetor: ", i);
        scanf("%d", &vet[i]);
    }

    printf("Valores:\n");
    for (i=0; i<5; i++) {
        printf("%d ", vet[i]);

    }
    return 0; 

}