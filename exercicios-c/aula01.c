#include <stdio.h>

#define texto "PROGRAMA TESTE"

int main (void) {
    printf("%s\n", texto);
    
    char nome[20] = "";
 
    printf("Nome informado: ");
    scanf("%s", nome);
    printf("Olá, %s\n", nome);

}

