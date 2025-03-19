#include <stdio.h>
#include <stdlib.h>

// A função malloc vai retornar um ponteiro para a região de memória alocada ou NULL caso não consiga alocar

int main() {
    int linhas, colunas;

    printf("Informe o tamanho (linhas x colunas) da matriz: ");
    scanf("%d", &linhas);
    scanf("%d", &colunas);

    // Ponteiro para ponteiro (alocação dinâmica da matriz)
    int **mat;
    mat = malloc(linhas * sizeof(int*));

    int i, j;

    for (i = 0; i < linhas; i++) {
        mat[i] = malloc(colunas * sizeof(int));
    }

    // Preenchimento da matriz
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("Digite o valor da posicao [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    // Exibindo a matriz
    printf("Matriz: \n");
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    // Liberação da memória alocada
    for (i = 0; i < linhas; i++) {
        free(mat[i]); 
    }
    free(mat);

    return 0;
}
