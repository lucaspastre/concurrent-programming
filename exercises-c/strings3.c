#include <stdio.h>
#include <string.h>

#define N 50
int main() {
    
    char senha[N] = {"teste12345"};
    char entrada_usr[N];
    int igual;

    printf("Digite sua senha: ");
    gets(entrada_usr);

    igual = strcmp(senha, entrada_usr);

    if (igual == 0) {
        printf("Bem-vindo!\n");
    } else {
        printf("Senha incorreta.\n");
    }

}