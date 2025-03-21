#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Anotacões:
// getpid() para retornar o processid de determinado processo
// wait() serve para aguardar o termino de um processo filho
// getppid() retorna o processid de seu processo pai
// para fazer o processo aguardar determinados segundos, usar sleep()
// o processo pai não pode terminar até que os processos filhos terminem

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar


int main(int argc, char** argv) {
    pid_t processo_filho, processo_neto;
    int i;

    for (i = 0; i < 2; i++) {
        processo_filho = fork();

        if (processo_filho == 0) {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            fflush(stdout);
            for (int j = 0; j < 3; j++) {
                processo_neto = fork();

                if (processo_neto == 0) {
                    printf("Processo %d, filho de %d\n", getpid(), getppid());
                    fflush(stdout);
                    sleep(5);
                    printf("Processo %d finalizado.\n", getpid());
                    fflush(stdout);
                    exit(0);
                }
            }

            while (wait(NULL) > 0);
            printf("Processo %d finalizado.\n", getpid());
            fflush(stdout);
            exit(0);
        }
    }

    while (wait(NULL) > 0);
    printf("Processo principal %d finalizado\n", getpid());
    return 0;
}

    
    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/
