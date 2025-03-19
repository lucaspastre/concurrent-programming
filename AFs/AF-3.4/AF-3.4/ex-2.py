from time import sleep
from random import randint
from threading import Thread, Semaphore

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    # verifica se há lugar no buffer
    vazio.acquire() # se não houver espaço no buffer (semáforo está em 0) a thread espera
    buffer.append(item)
    print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
    cheio.release()

def consumidor():
  global buffer
  for i in range(10):
    # aguarda que haja um item para consumir
    cheio.acquire() # se não houver itens no buffer (semáforo está em 0) a thread espera
    item = buffer.pop(0)
    print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
    vazio.release()
    sleep(randint(0,2))         # fica um tempo consumindo...

buffer = []
tam_buffer = 3
# cria semáforos
cheio = Semaphore(0)
vazio = Semaphore(tam_buffer)

produtor = Thread(target=produtor) 
consumidor = Thread(target=consumidor) 
produtor.start()
consumidor.start()
produtor.join()
consumidor.join() 