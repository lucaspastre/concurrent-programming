#include <stdio.h>
#include <string.h>

#define N 20

int main() {
    char s1[N] = {"Concurrent"};
    char s2[N] = {"Programming"};
    int tamanho;

    strcat(s1, s2);

    puts(s1);

    tamanho = strlen(s1); 
    

    printf("Tamanho da string: %d", tamanho);

}