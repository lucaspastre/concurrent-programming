#include <stdio.h>
#include <stdlib.h> // Para rand()

int main() {
    int data[3][3];
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i <= j) {
                data[i][j] = rand() % 100 + 1;
            } else {
                data[i][j] = 0; 
            }
        }
    }

    printf("Matriz triangular superior: \n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }

    return 0;
}
