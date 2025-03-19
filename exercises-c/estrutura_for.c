#include <stdio.h>

int main() {
    int i;

    for (i=1; i <= 10; i++){
        
        if (i == 5) {
            continue; // em caso de condição verdadeira, o continue pula essa iteração
        }
        printf("%d\n", i);
    }

    }
