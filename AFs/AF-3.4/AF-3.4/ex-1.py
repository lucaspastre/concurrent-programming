from time import sleep
from random import randint
from threading import Thread, Lock, Condition

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    with lock:
      while len(buffer) == tam_buffer:
        print('>>> Buffer cheio. Produtor ira aguardar.')
        lugar_no_buffer.wait()    # aguarda que haja lugar no buffer
      buffer.append(item)
      print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
      item_no_buffer.notify()

""" o uso do while faz-se necessário pois a condição é reavaliada
    após a thread acordar e adquirir o lock, garantindo que ela só
    prossiga se o buffer ainda estiver no estado esperado
"""

def consumidor():
  global buffer
  for i in range(10):
    with lock:
      while len(buffer) == 0:
        print('>>> Buffer vazio. Consumidor ira aguardar.')
        item_no_buffer.wait()   # aguarda que haja um item para consumir 
      item = buffer.pop(0)
      print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
      lugar_no_buffer.notify()
    sleep(randint(0,2))         # fica um tempo consumindo...

buffer = []
tam_buffer = 5
lock = Lock()
lugar_no_buffer = Condition(lock)
item_no_buffer = Condition(lock)

# crio duas listas para as threads produtores e consumidoras
produtores = []
consumidores = []

# faço um laço para criar 2 threads produtoras e 2 threads consumidoras e inicio elas com start()
for i in range(2):
  produtores.append(Thread(target=produtor))
  produtores[i].start()
  consumidores.append(Thread(target=consumidor))
  consumidores[i].start()

# faço um laço para aguardar o fim das 2 threads produtoras e 2 threads consumidoras
for i in range(2):
  produtores[i].join()
  consumidores[i].join()
