#include <stdio.h>

int main(){
    char a[10];

    printf("Digite algo:\n");
    scanf("%s", a); // nesse caso não é necessário utilizar "&".
    fflush(stdin); // fflush garante descarga no teclado para o próximo scanf funcionar corretamente.

    printf("Resultado: %s\n", a);

    printf("Digite algo novamente: \n");
    scanf("%9[^\n]s", a);
    fflush(stdin);

    printf("Resultado: %s\n", a);

    return 0;
}