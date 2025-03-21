from threading import Thread, Lock, Condition
from queue import Queue
import time

# Classe que representa a experiência da NASA
class NASAExperience:
    def __init__(self, N_ATRACOES, N_VAGAS, PERMANENCIA, UNID_TEMPO):
        # Inicializando o número de atrações e vagas disponíveis
        self.n_atracoes = N_ATRACOES
        self.n_vagas = N_VAGAS
        self.permanencia = PERMANENCIA
        self.unid_tempo = UNID_TEMPO

        # Fila para organizar as pessoas
        self.fila = Queue()

        # Contadores de vagas ocupadas e pessoas atendidas
        self.vagas_ocupadas = 0
        self.total_pessoas = 0
        self.pessoas_atendidas = 0

        # A experiência atual em execução
        self.experiencia_atual = None

        # Lock para sincronização de threads
        self.lock = Lock()

        # Condição para pausar ou continuar a execução
        self.cond = Condition(self.lock)

        # Estatísticas
        self.tempo_espera = {f"AT-{i}": [] for i in range(1, N_ATRACOES + 1)}
        self.tempo_ocupacao = {f"AT-{i}": 0 for i in range(1, N_ATRACOES + 1)}
        self.tempo_inicio_simulacao = None
        self.tempo_fim_simulacao = None
        self.tempo_inicio_experiencia = None

    # Método para adicionar uma pessoa na fila
    def entrar_fila(self, pessoa_id, experiencia):
        # uso do lock para garantir exclusão mútua e proteger o acesso compartilhado a fila
        with self.lock:
            print(f"[Pessoa {pessoa_id} / {experiencia}] Aguardando na Fila.")

            # Adicionando a pessoa na fila
            self.fila.put((pessoa_id, experiencia, time.time()))

            # Notificando as threads
            self.cond.notify_all()

    # Método principal que gerencia a execução das Experiências
    def iniciar_experiencia(self):
        self.tempo_inicio_simulacao = time.time()
        while True:
            with self.lock:
                # Esperando até que haja pessoas na fila ou pessoas na experiência
                while self.fila.empty() and self.vagas_ocupadas == 0:
                    if self.pessoas_atendidas == self.total_pessoas:
                        # Pegando o tempo em que a simulação finalizou
                        self.tempo_fim_simulacao = time.time()
                        return  # Todas as pessoas foram atendidas, encerramos a thread
                    self.cond.wait()

                # Iniciando uma nova experiência se nenhuma estiver ativa
                if not self.fila.empty() and self.experiencia_atual is None:
                    pessoa_id, experiencia, _ = self.fila.queue[0]
                    self.experiencia_atual = experiencia
                    self.tempo_inicio_experiencia = time.time()
                    print(f"[NASA] Iniciando a experiência {experiencia}.")

                # Permite a entrada de pessoas na experiência atual se houver vagas
                while (not self.fila.empty() and self.experiencia_atual == self.fila.queue[0][1] and self.vagas_ocupadas < self.n_vagas):
                    pessoa_id, experiencia, tempo_chegada = self.fila.get()  # Remove a pessoa da fila
                    self.vagas_ocupadas += 1
                    self.pessoas_atendidas += 1  # Incrementando o número de pessoas atendidas

                    tempo_espera = (time.time() - tempo_chegada) * 1000 # conversão de segundos para milisegundos
                    self.tempo_espera[experiencia].append(tempo_espera)
                    print(f"[Pessoa {pessoa_id} / {experiencia}] Entrou na NASA Experiences (quantidade = {self.vagas_ocupadas}).")

                    # Criando uma Thread para gerenciar a saída da pessoa após a permanência
                    Thread(target=self.sair_da_experiencia, args=(pessoa_id, experiencia)).start()

                # Pausa a experiência atual se não houver mais vagas ocupadas
                if self.vagas_ocupadas == 0 and self.experiencia_atual:
                    tempo_total_experiencia = time.time() - self.tempo_inicio_experiencia
                    self.tempo_ocupacao[self.experiencia_atual] += tempo_total_experiencia
                    print(f"[NASA] Pausando a experiencia {self.experiencia_atual}. ")
                    self.experiencia_atual = None
                    self.cond.notify_all()  # uso do notify_all() para notificar as outras threads sobre a mudança
                    # Notificando todas as threads garante que qualquer uma que possa continuar sua execução seja despertada.


    # Método para gerenciar a saída de uma pessoa após o tempo de permanência
    def sair_da_experiencia(self, pessoa_id, experiencia):
        time.sleep(self.permanencia * self.unid_tempo / 1000.0)  # Ajusta o tempo baseado na unidade de tempo
        with self.lock:
            # vagas_ocupadas é um recurso compartilhado, logo usa-se lock para garantir exclusão mútua
            self.vagas_ocupadas -= 1
            print(f"[Pessoa {pessoa_id} / {experiencia}] Saiu da NASA Experiences (quantidade = {self.vagas_ocupadas}).")

            # Notificando as Threads que estão esperando mudanças
            self.cond.notify_all()

    def gerar_relatorio(self):
        tempo_ocupado_total = 0

        print("Tempo medio de espera:")
        for experiencia, tempos in self.tempo_espera.items():
            media = sum(tempos) / len(tempos) if tempos else 0
            print(f"Experiencia {experiencia}: {media:.2f}")

        # Calculando o tempo total da simulação
        tempo_total_simulacao = self.tempo_fim_simulacao - self.tempo_inicio_simulacao

        # Somando os tempos de ocupação das atrações, garantindo que não ultrapasse o tempo total da simulação
        tempo_ocupado_total = sum(min(tempo, tempo_total_simulacao) for tempo in self.tempo_ocupacao.values())

        # Calculando a taxa total de ocupação
        taxa_total = (tempo_ocupado_total / tempo_total_simulacao) if tempo_total_simulacao > 0 else 0
        print(f"\nTaxa de ocupacao: {taxa_total:.2f}")