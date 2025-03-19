#include <stdio.h>

#define titulo "Operações Lógicas"
// ou lógico -> ||
// e lógico -> &&
// negação -> !

int main(void) {

    float nota;

    printf("Digite sua nota: ");
    scanf("%f", &nota);

    if (nota < 3) {
        printf("Reprovado\n");
    }
    else if (nota >= 3 && nota < 6) {
        printf("Recuperação\n");
    } else {
        printf("Aprovado\n");
    }

}