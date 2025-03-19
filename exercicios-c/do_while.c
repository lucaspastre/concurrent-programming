#include <stdio.h>

//o do-while obrigatoriamente executa o bloco de comando pelo menos uma vez

int main() {
    float valor;
    do {
        printf("Insira um valor entre 1 e 10:");
        scanf("%f", &valor);

        if (valor < 1 || valor >10){
            printf("Valor inválido.\n");
        }

    }while (valor < 1 || valor >10);
}
