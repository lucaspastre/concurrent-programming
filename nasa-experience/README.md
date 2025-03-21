## 1 Introdução
Uma atração da NASA (NASA Experiences) foi construída em Balneário Camboriú. Ao entrar na atração, os
turistas passam por uma experiência incrível, com tela em gigante em alta resolução, som de alta qualidade e diversos
efeitos sensoriais. O NASA Experiences pode possuir uma ou mais experiências, cada uma com características de
video, som e efeitos sensoriais diferentes. As regras de funcionamento são:
1. Cada pessoa tem direito a assistir uma única experiência escolhida por ela;
2. Uma única fila fora da atração é utilizada para organizar as pessoas em ordem de chegada;
3. Existe somente uma única experiência em curso na NASA Experiences;
4. Quando a primeira pessoa ingressa na atração, ela inicia automaticamente a experiência de sua escolha;
5. Quando a atração está funcionando para uma experiência x, ele permanence recebendo pessoas que desejam
assistir x na ordem de chegada na fila até que uma outra pessoa que deseja assistir uma outra experiência
diferente x′
seja a primeira da fila. Quando isso acontecer, esta pessoa aguarda que todas as pessoas que estejam
assistindo a experiência x saiam da NASA Experiences;
6. A experiência é automaticamente pausada somente quando não há ninguém na NASA Experiences e não existem
pessoas aguardando na fila;
7. Existe um número limitado de vagas (N_VAGAS) na atração, portanto, nunca haverá mais do que N_VAGAS pessoas
simultaneamente na atração;
8. Após entrar na atração, cada pessoa permanece nela por PERMANENCIA unidades de tempo.
   
## 2 Definição do Trabalho
O trabalho consiste em desenvolver um programa multithread em Python que simula o comportamento da atração
da NASA Experiences. A sua solução deverá, obrigatoriamente, considerar os seguintes requisitos:
1. A sua solução deverá rodar com Python v3.10.12 ou superior;
2. Cada pessoa deverá ser representada por uma thread na simulação;
3. Mecanismos de sincronização deverão ser empregados para que as regras definidas anteriormente sejam respeitadas (não será permitido fazer uso da técnica de espera ocupada para fins de sincronização);
4. Uma thread especial deverá ser responsável pela criação das threads que representam as pessoas;
5. O tempo de chegada das pessoas na atração assim como a experiência que desejam assistir deverão ser escolhidos
de maneira aleatória (considere que quando uma pessoa é criada na simulação ela já sabe a atração de sua
escolha). Porém, deverá ser respeitado um intervalo máximo de tempo MAX_INTERVALO entre a chegada de
quaisquer duas pessoas na simulação. O método random.randint(a, b) deverá obrigatoriamente ser utilizado
para esses fins;
6. A simulação acaba quando a última pessoa sai da atração.
Além das threads que representam pessoas e da thread especial que cria as pessoas, é permitido utilizar outras
threads para realizar atividades específicas na sua simulação, se necessário.