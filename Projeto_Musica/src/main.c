/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************/
/* includes                                                             */
/************************/

#include "asf.h"
#include "musicas.h"

/************************/
/* defines                                                              */
/************************/

#define LED_PIO           PIOC                 // periferico que controla o LED
#define LED_PIO_ID        12                  // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED  

#define BUZ_PIO           PIOA                 // periferico que controla o BUZZER
#define BUZ_PIO_ID        ID_PIOA                  // ID do periférico PIOA (controla BUZZER)
#define BUZ_PIO_IDX       3               // ID do BUZZER no PIO
#define BUZ_PIO_IDX_MASK  (1 << BUZ_PIO_IDX)   // Mascara para CONTROLARMOS o BUZZER

#define BUT_PIO           PIOA
#define BUT_PIO_ID        ID_PIOA
#define BUT_PIO_IDX       11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)
#define PIOA   ((Pio    *)0x400E0E00U) /**< \brief (PIOA  ) Base Address */

#define BUT1_PLACA_PIO PIOA
#define BUT1_PLACA_PIO_ID ID_PIOA
#define BUT1_PLACA_IDX 2u
#define BUT1_PLACA_MASK (1u<< BUT1_PLACA_IDX)

#define BUT2_PLACA_PIO PIOD
#define BUT2_PLACA_PIO_ID ID_PIOD
#define BUT2_PLACA_IDX 30u
#define BUT2_PLACA_MASK (1u<< BUT2_PLACA_IDX)

#define BUT3_PLACA_PIO PIOC
#define BUT3_PLACA_PIO_ID ID_PIOC
#define BUT3_PLACA_IDX 13u
#define BUT3_PLACA_MASK (1u<< BUT3_PLACA_IDX)


#define LED1_PLACA_PIO PIOC
#define LED1_PLACA_PIO_ID ID_PIOC
#define LED1_PLACA_IDX 19u
#define LED1_PLACA_MASK (1u<< LED1_PLACA_IDX)

#define LED2_PLACA_PIO PIOD
#define LED2_PLACA_PIO_ID ID_PIOD
#define LED2_PLACA_IDX 26u
#define LED2_PLACA_MASK (1u<< LED2_PLACA_IDX)

#define LED3_PLACA_PIO PIOD
#define LED3_PLACA_PIO_ID ID_PIOD
#define LED3_PLACA_IDX 11u
#define LED3_PLACA_MASK (1u<< LED3_PLACA_IDX)


/************************/
/* constants                                                            */
/************************/

/************************/
/* variaveis globais                                                    */
/************************/

/************************/
/* prototypes                                                           */
/************************/

void init(void);
void play(int notas[],int duracao[],int tamanho,int velocidade);
/************************/
/* interrupcoes                                                         */
/************************/

/************************/
/* funcoes                                                              */
/************************/

void play(int notas[],int duracao[],int tamanho,int velocidade){

	for (int i=0; i<tamanho;i++){
		for (int x=0; x < duracao[i]; x++){
			int wait = 1000000/(2*notas[i]);
			pio_set(PIOA,BUZ_PIO_IDX_MASK);
			pio_set(LED_PIO,LED_PIO_IDX_MASK);
			delay_us(wait);
			pio_clear(PIOA,BUZ_PIO_IDX_MASK);
			pio_clear(LED_PIO,LED_PIO_IDX_MASK);
			delay_us(wait);
		}
		pio_set(LED_PIO,LED_PIO_IDX_MASK);
		delay_us(velocidade*duracao[i]);
	}
}









void init(void)
{
  // Initialize the board clock
  sysclk_init();
  
  // Desativa WatchDog Timer
  WDT->WDT_MR = WDT_MR_WDDIS;
  
  // Ativa o PIO na qual o LED foi conectado
  // para que possamos controlar o LED.
  pmc_enable_periph_clk(BUT_PIO_ID);
  pmc_enable_periph_clk(LED_PIO_ID);
  pmc_enable_periph_clk(BUZ_PIO_ID);
  pmc_enable_periph_clk(BUT1_PLACA_PIO_ID);
  pmc_enable_periph_clk(BUT2_PLACA_PIO_ID);
  pmc_enable_periph_clk(BUT3_PLACA_PIO_ID);
  pmc_enable_periph_clk(LED1_PLACA_PIO_ID);
  pmc_enable_periph_clk(LED2_PLACA_PIO_ID);
  pmc_enable_periph_clk(LED3_PLACA_PIO_ID);
  
  //Inicializa PC8 como saída
  pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
  pio_set_output(BUZ_PIO, BUZ_PIO_IDX_MASK, 0, 0, 0);
  pio_set_output(LED1_PLACA_PIO, LED1_PLACA_MASK, 1, 0, 0);
  pio_set_output(LED2_PLACA_PIO, LED2_PLACA_MASK, 1, 0, 0);
  pio_set_output(LED3_PLACA_PIO, LED3_PLACA_MASK, 1, 0, 0);
  
  // Inicializa PIO do botao
  pmc_enable_periph_clk(BUT_PIO_ID);
  
  pio_pull_up(BUT_PIO, BUT_PIO_IDX_MASK, 1);
  
  pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_DEFAULT); 
  pio_set_input(BUT1_PLACA_PIO, BUT1_PLACA_MASK, PIO_DEFAULT | PIO_PULLUP);
  pio_set_input(BUT2_PLACA_PIO, BUT2_PLACA_MASK, PIO_DEFAULT | PIO_PULLUP);
  pio_set_input(BUT3_PLACA_PIO, BUT3_PLACA_MASK, PIO_DEFAULT | PIO_PULLUP); 
  
}


/************************/
/* Main                                                                 */
/************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
	// inicializa sistema e IOs
	init();
	
	musica musicapiratas;
	musica musicamario;

	//MUSICA PIRATAS DO CARIBE
	for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++){
		musicapiratas.notas[i] = notes[i];
		musicapiratas.duracao[i] = duration[i];
	}
	musicapiratas.tamanho = sizeof(notes) / sizeof(notes[0]);

	//MUSICA MARIO
	for (int i = 0; i < sizeof(melodia) / sizeof(melodia[0]); i++){
		musicamario.notas[i] = melodia[i];
		musicamario.duracao[i] = duracaodasnotas[i];
	}
	musicamario.tamanho = sizeof(melodia) / sizeof(melodia[0]);


	
	
	int musica1,musica2,musica3;

	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1)
	{
		musica1 = pio_get(BUT1_PLACA_PIO, PIO_INPUT, BUT1_PLACA_MASK);
		musica2 = pio_get(BUT2_PLACA_PIO, PIO_INPUT, BUT2_PLACA_MASK);
		musica3 = pio_get(BUT3_PLACA_PIO, PIO_INPUT, BUT3_PLACA_MASK);
		
		if (musica1 != 1){
			pio_clear(LED1_PLACA_PIO, LED1_PLACA_MASK);
			pio_set(LED2_PLACA_PIO,LED2_PLACA_MASK);
			pio_set(LED3_PLACA_PIO,LED3_PLACA_MASK);
			
			//MUSICA PIRATAS DO CARIBE
			play(musicapiratas.notas,musicapiratas.duracao,musicapiratas.tamanho,500);
			pio_set(LED1_PLACA_PIO, LED1_PLACA_MASK);
			
		}
		else if (musica2 != 1){
			pio_set(LED1_PLACA_PIO, LED1_PLACA_MASK);
			pio_clear(LED2_PLACA_PIO,LED2_PLACA_MASK);
			pio_set(LED3_PLACA_PIO,LED3_PLACA_MASK);
			
			//MUSICA MARIO BROS
			play(musicamario.notas,musicamario.duracao,musicamario.tamanho,1000);
			pio_set(LED2_PLACA_PIO,LED2_PLACA_MASK);
		}
		else if (musica3 != 1){
			pio_set(LED1_PLACA_PIO, LED1_PLACA_MASK);
			pio_set(LED2_PLACA_PIO,LED2_PLACA_MASK);
			pio_clear(LED3_PLACA_PIO,LED3_PLACA_MASK);
			
		}
	}
	return 0;
}