# APS1_Embarcados
Projeto Musical de Embarcados

## Introdução
A entrega final deste projeto consiste em um sistema embarcado que reproduz músicas de forma monofônica via adição de um buzzer ao uC do mesmo. Além do buzzer, será necessário adicionar alguns botões ao kit. Esses botões serão utilizados para:
- `mudar de música`
- `parar / iniciar a música`

## Materiais
- `1x Microcontrolador Atmel SAME70 Xplained`
- `1x Periférico OLED1 Xplained`
- `1x Buzzer 5V`
- `2x Jumpers macho-fêmea`

## Configurações e Esquema
O Periférico`OLED1 Xplained` deve ser conectado ao Microcontrolador `Atmel SAME70 Xplained` por meio da entrada `EXT2`. O `Buzzer` deve ser conectado ao Microcontrolador `Atmel SAME70 Xplained` por meio dos Jumpers Macho-Fêmea. O polo positivo (fio vermelho) do `Buzzer` foi conectado ao pino `PA 3` do conector `EXT1`, enquanto o polo negativo (fio preto) do `Buzzer` foi conectado ao pino `GND` do POWER.

Vide imagem a seguir:

## Botões e LED's
- Botões:
  - O `Button 1` do periférico `OLED1 Xplained` seleciona a música 1.
  - O `Button 2` do periférico `OLED1 Xplained` seleciona a música 2.
  - O `Button 3` do periférico `OLED1 Xplained` seleciona a música 3.
  - O `Button SW0` do microcontrolador `Atmel SAME70 Xplained` pausa ou continua a música que estiver tocando.
- LED's:
  - O `LED 1` do periférico `OLED1 Xplained` acende se a música 1 estiver tocando.
  - O `LED 2` do periférico `OLED1 Xplained` acende se a música 2 estiver tocando.
  - O `LED 3` do periférico `OLED1 Xplained` acende se a música 3 estiver tocando.
  - O `LED` do Microcontrolador `Atmel SAME70 Xplained` pisca no ritmo da música que estiver tocando.
  
## Estrutura:
- [`musicas.h`](/Projeto_Musica/src/musicas.h): Contém as notas das músicas, a duração dessas notas e como foi feita a struct musica.

- [`musicas.c`](/Projeto_Musica/src/musicas.c): 

- [`main.c`](/Projeto_Musica/src/main.c): utiliza o `musicas.h` para criar as músicas em formato de struct. Inicializa a placa e os pinos que vão ser utilizados ,há a criação da função de tocar música, o código de pause, e toda a estrutura para ascender e apagar as leds conforme o usuario aperta os botões.

## Funções:
- `void play(int notas[],int duracao[],int tamanho,int velocidade)`: recebe os vetores de notas,duração que essas notas vão tocar, tamanho desses vetores e velocidades que as notas vão ser tocadas. Com esses argumentos ativa e desativa o buzzer em variações de tempo necessarias para gerar a nota esperada.

## Rúbrica
- A (1 item embarcado + 1 item C)
  - Embarcado
    - [ ] Utiliza dois falantes (para fazer uma música mais complexa);
    - [x] Utiliza interrupção nos botões;
  - C
    - [x] Cria um arquivo .c .h com as funções de reprodução musical;
    - [x] Músicas organizadas em vetores de structs (ponteiros);

- B+
  - [ ] Uma terceira música

- B
  - [x] README.md explica o que é o projeto e como o software foi estruturado;
  - [x] Música separada em .h;
  - [x] Utiliza struct para organizar as músicas;
  - [x] Código organizado em funções e que recebem struct contendo música;
  - [x] Utiliza #define sempre que necessário;
  - [ ] Fecha todos os issues que forem abertos no repositório (pelo professor);

- C
  - [x] Repositório contém [README.md](/README.md) com ligações elétrica e passos de como usar o projeto, assim como link para o vídeo;
  - [x] Funcionalidade de PAUSE/ PLAY;
  - [x] Botão de seleção musical;
  - [x] Reproduz duas músicas (de forma inteligível);
  - [x] LED piscando de acordo com a música;
  - [x] Indicação visual de qual música foi selecionada;

- D
  - [ ] Faltando um item de C

- I
  - [ ] Mais que dois itens de C faltando
