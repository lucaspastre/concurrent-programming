import random
import sys
from threading import Thread
from pessoas import CriaPessoas
from experience import NASAExperience

if __name__ == "__main__":
    # Verificando os argumentos
    if len(sys.argv) != 8:
        print("Uso: python programa.py <N_ATRACOES> <N_PESSOAS> <N_VAGAS> <PERMANENCIA> <MAX_INTERVALO> <SEMENTE> <UNID_TEMPO>")
        sys.exit(1)

    try:
        # Lendo os argumentos da linha de comando
        N_ATRACOES, N_PESSOAS, N_VAGAS, PERMANENCIA, MAX_INTERVALO, SEMENTE, UNID_TEMPO = map(int, sys.argv[1:])

        # Validando dos parâmetros
        if N_ATRACOES <= 0 or N_PESSOAS <= 0 or N_VAGAS <= 0 or PERMANENCIA <= 0 or MAX_INTERVALO < 0 or SEMENTE < 0 or UNID_TEMPO <= 0:
            raise ValueError("Todos os parâmetros devem ser números inteiros positivos.")

        # Configurando a semente para números aleatórios
        random.seed(SEMENTE)

        # Criando a instância da experiência
        nasa_experience = NASAExperience(N_ATRACOES, N_VAGAS, PERMANENCIA, UNID_TEMPO)
        nasa_experience.total_pessoas = N_PESSOAS

        print("[NASA] Simulação iniciada.")

        # Criando a thread responsável por adicionar pessoas à fila
        criador_pessoas = CriaPessoas(N_PESSOAS, MAX_INTERVALO, UNID_TEMPO, nasa_experience)
        criador_pessoas.start()

        # Criando a thread responsável pela execução das experiências
        experiencia_thread = Thread(target=nasa_experience.iniciar_experiencia)
        experiencia_thread.start()

        # Aguardando a finalização das threads
        criador_pessoas.join()
        experiencia_thread.join()

        print("[NASA] Simulação finalizada.")

        nasa_experience.gerar_relatorio()

    except ValueError as e:
        print(f"Erro nos parâmetros: {e}")
        sys.exit(1)