from threading import Thread
import random
import time

# Classe para criar as Threads que representam as Pessoas
class CriaPessoas(Thread):
    def __init__(self, N_PESSOAS, MAX_INTERVALO, UNID_TEMPO, nasa_experience):
        super().__init__()
        # Número de pessoas a serem criadas
        self.n_pessoas = N_PESSOAS

        # Intervalo máximo entre a chegada de pessoas
        self.max_intervalo = MAX_INTERVALO

        # Referência à instância da experiência
        self.nasa_experience = nasa_experience

        self.unid_tempo = UNID_TEMPO

    # Método principal que executa a criação das Pessoas
    def run(self):
        for i in range(1, self.n_pessoas + 1):
            # Escolhendo aleatoriamente uma experiência para a pessoa
            experiencia = f"AT-{random.randint(1, self.nasa_experience.n_atracoes)}"

            # Adicionando a pessoa na fila
            self.nasa_experience.entrar_fila(i, experiencia)

            # Esperando um intervalo aleatório antes de criar a próxima pessoa
            time.sleep(random.randint(0, self.max_intervalo) * self.unid_tempo / 1000.0)