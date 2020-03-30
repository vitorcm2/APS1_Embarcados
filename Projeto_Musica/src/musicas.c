
/*
 * musicas.c
 *
 * Created: 30/03/2020 11:00:34
 *  Author: vitor
 */ 

#include "musicas.h"

musica musicapiratas,musicamario;

//MUSICA PIRATAS DO CARIBE
for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++){
	musicapiratas.notas[i] = notes[i];
	musicapiratas.duracao[i] = duration[i];
}
musicapiratas.tamanho = sizeof(notes) / sizeof(notes[0];

//MUSICA MARIO
for (int i = 0; i < sizeof(melodia) / sizeof(melodia[0]); i++){
	musicamario.notas[i] = melodia[i];
	musicamario.duracao[i] = duracaodasnotas[i];
}
musicamario.tamanho = sizeof(melodia) / sizeof(melodia[0];

