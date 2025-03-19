#include <stdio.h>

#define titulo "Atribuicões Aritméticas"
// ++ incremento de 1
// -- decremento de 1
// += incremento genérico
// -= decremento genérico
// *= atribuição com multiplicação
// /= atribuição com divisão

int main(void) {
    printf("Digite um número: ");

    int num;

    scanf("%d", &num);

    num++;

    printf("O número após incremento de 1 é: %d\n", num);

}