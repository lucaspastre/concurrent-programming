#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

// Lê o conteúdo do arquivo filename e retorna um vetor E o tamanho dele
// Se filename for da forma "gen:%d", gera um vetor aleatório com %d elementos
double* load_vector(const char* filename, int* out_size);

// Avalia se o prod_escalar é o produto escalar dos vetores a e b.
void avaliar(double* a, double* b, int size, double prod_escalar);

typedef struct {
    double* a;
    double* b;
    int begin;
    int end;
    double result;
} th;

void* Thread(void* data) {
    th* info = (th*)data;
    info->result = 0;

    for (int i = info->begin; i < info->end; ++i) {
        info->result += info->a[i] * info->b[i];
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // Tem argumentos suficientes?
    if (argc < 4) {
        printf("Uso: %s n_threads a_file b_file\n"
               "    n_threads    número de threads a serem usadas na computação\n"
               "    *_file       caminho de arquivo ou uma expressão com a forma gen:N,\n"
               "                 representando um vetor aleatório de tamanho N\n",
               argv[0]);
        return 1;
    }

    // Quantas threads?
    int n_threads = atoi(argv[1]);
    if (n_threads <= 0) {
        printf("Número de threads deve ser > 0\n");
        return 1;
    }

    // Lê números de arquivos para vetores alocados com malloc
    int a_size = 0, b_size = 0;
    double* a = load_vector(argv[2], &a_size);
    if (!a) {
        printf("Erro ao ler arquivo %s\n", argv[2]);
        return 1;
    }
    double* b = load_vector(argv[3], &b_size);
    if (!b) {
        printf("Erro ao ler arquivo %s\n", argv[3]);
        return 1;
    }

    // Garante que entradas são compatíveis
    if (a_size != b_size) {
        printf("Vetores a e b têm tamanhos diferentes! (%d != %d)\n", a_size, b_size);
        return 1;
    }

    // Calcula produto escalar. Paralelize essa parte
    double result = 0;
    pthread_t threads[n_threads];
    th th_[n_threads];
    int elementos = a_size / n_threads;
    int resto = a_size % n_threads;

    // Cria threads para calcular o produto escalar em paralelo
    for (int i = 0; i < n_threads; ++i) {
        th_[i].a = a;
        th_[i].b = b;
        th_[i].begin = i * elementos;
        th_[i].end = (i + 1) * elementos;

        if (i == n_threads - 1 && resto != 0) {
            th_[i].end += resto;
        }

        pthread_create(&threads[i], NULL, Thread, (void*)&th_[i]);
    }

    // Junta as threads e acumula o resultado
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
        result += th_[i].result;
    }

    // Avalia o resultado
    avaliar(a, b, a_size, result);

    // Libera memória
    free(a);
    free(b);

    return 0;
}