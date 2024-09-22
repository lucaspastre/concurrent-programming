#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


//       (pai)      
//         |        
//    +----+----+
//    |         |   
// filho_1   filho_2


// ~~~ printfs  ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!

int main (int argc, char** argv) {
    pid_t processo;
    int i;

    for (i = 0; i < 2; i++) {
        processo = fork();

        if (processo == 0) {
            printf("Processo filho %d criado\n", getpid());
            fflush(stdout);
            exit(0);
        }
        printf("Processo pai criou %d\n", processo);
        fflush(stdout);
    }

    while (wait(NULL) > 0);
    
    printf("Processo pai finalizado!\n");
    fflush(stdout);

    return 0;

}
  
    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/

