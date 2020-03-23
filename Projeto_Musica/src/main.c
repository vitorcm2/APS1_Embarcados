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


const int buzzer = 10; //Define pin 10, can use other PWM pins  (5,6 or 9)
//Note pins 3 and 11 can't be used when using the tone function in Arduino Uno
const int songspeed = 1.5; //Change to 2 for a slower version of the song, the bigger the number the slower the song

//melodia do MARIO THEME
int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
 
//duraçao de cada nota do mario
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};
 

//*****************************************
#define NOTE_C4  262   //Defining note frequency MUSICA PIRATAS DO CARIBE
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
//*****************************************

int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
//*****************************************
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};


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

/************************/
/* interrupcoes                                                         */
/************************/

/************************/
/* funcoes                                                              */
/************************/

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
#define BUT3_PLACA_PIO PIOC
#define BUT3_PLACA_PIO_ID ID_PIOC
#define BUT3_PLACA_IDX 13u
#define BUT3_PLACA_MASK (1u<< BUT3_PLACA_IDX)
// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
	// inicializa sistema e IOs
	init();
	int musica1,musica2,musica3,pause;
	int musica = 0;
	int pausou = 0;
	int lugardamusica =0;
	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1)
	{
		musica1 = pio_get(BUT1_PLACA_PIO, PIO_INPUT, BUT1_PLACA_MASK);
		musica2 = pio_get(BUT2_PLACA_PIO, PIO_INPUT, BUT2_PLACA_MASK);
		musica3 = pio_get(BUT3_PLACA_PIO, PIO_INPUT, BUT3_PLACA_MASK);
		
		if (musica1 != 1){
			musica = 1;
			pio_clear(LED1_PLACA_PIO, LED1_PLACA_MASK);
			pio_set(LED2_PLACA_PIO,LED2_PLACA_MASK);
			pio_set(LED3_PLACA_PIO,LED3_PLACA_MASK);
		}
		else if (musica2 != 1){
			musica = 2;
			pio_set(LED1_PLACA_PIO, LED1_PLACA_MASK);
			pio_clear(LED2_PLACA_PIO,LED2_PLACA_MASK);
			pio_set(LED3_PLACA_PIO,LED3_PLACA_MASK);
		}
		else if (musica3 != 1){
			musica = 3;
			pio_set(LED1_PLACA_PIO, LED1_PLACA_MASK);
			pio_set(LED2_PLACA_PIO,LED2_PLACA_MASK);
			pio_clear(LED3_PLACA_PIO,LED3_PLACA_MASK);
			
		}
		
		// MUSICA PIRATAS DO CARIBE
		if (musica == 1){
			int tamanho = sizeof(notes)/sizeof(notes[0]);
			for (int i=0; i<tamanho;i++){
				pause = pio_get(BUT_PIO,PIO_INPUT,BUT_PIO_IDX_MASK);
				if (pause != 1){
					musica = 0;
					pausou = 4;
					lugardamusica = i;
					break;
				}
				if (pausou == 4){
					i = lugardamusica;
					lugardamusica = 0;
					pausou = 0;
				}
				for (int x=0; x < duration[i]; x++){
					int wait = 1000000/(2*notes[i]);
					pio_set(PIOA,BUZ_PIO_IDX_MASK);
					pio_set(LED_PIO,LED_PIO_IDX_MASK);
					delay_us(wait);
					pio_clear(PIOA,BUZ_PIO_IDX_MASK);
					pio_clear(LED_PIO,LED_PIO_IDX_MASK);
					delay_us(wait);
				}
				pio_set(LED_PIO,LED_PIO_IDX_MASK);
				delay_us(500*duration[i]);
			}
		}


		if (musica == 2){
			//MUSICA MARIO BROS
			int tamanho = sizeof(melodia)/sizeof(melodia[0]);
			for (int i=0; i<tamanho;i++){
				pause = pio_get(BUT_PIO,PIO_INPUT,BUT_PIO_IDX_MASK);
				if (pause != 1){
					musica = 0;
					pausou = 5;
					lugardamusica = i;
					break;
				}
				if (pausou == 5){
					i = lugardamusica;
					lugardamusica = 0;
					pausou = 0;
				}
				for (int x=0; x < duracaodasnotas[i]; x++){
					int wait = 1000000/(2*melodia[i]);
					pio_set(PIOA,BUZ_PIO_IDX_MASK);
					pio_clear(LED_PIO,LED_PIO_IDX_MASK);
					delay_us(wait);
					pio_clear(PIOA,BUZ_PIO_IDX_MASK);
					
					delay_us(wait);
				}
				pio_set(LED_PIO,LED_PIO_IDX_MASK);
				delay_us(1000*duracaodasnotas[i]);
			}
		}

		
		
		
			
	
		

		
		//else{
		//	_pio_set(PIOC, LED_PIO_IDX_MASK);
		//}
	}
	return 0;
}