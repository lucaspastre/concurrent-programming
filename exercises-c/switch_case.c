#include <stdio.h>

#define titulo "SWITCH CASE"

//somente para comparação de igualdades
int main() {
    printf("%s\n", titulo);

    int numero;

    printf("Digite um número: ");
    scanf("%d", &numero);

    switch(numero) {
        case 1:
        printf("Verdadeiro\n");
        break;

        case 0:
        printf("Falso\n");
        break;

        default:
        printf("Inválido\n");
        break;

    }

}