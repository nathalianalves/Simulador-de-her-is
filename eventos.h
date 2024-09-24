// Biblioteca de funções relacionadas aos eventos ocorridos no mundo "The Boys"
// Nathália Nogueira Alves - GRR20232349 - 2023

#ifndef EVENTOS_H
#define EVENTOS_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mundo.h"
#include "LEF.h"

/* Trata a chegada do heroi id_heroi na base id_base. Pode deixá-lo entrar, deixá-lo na lista de espera ou marcar sua desistência.
   Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */ 
int evento_chega(cabeca_LEF *LEF, base lista_bases[], heroi lista_herois[], int tempo, int id_heroi, int id_base);

/* Insere o heroi id_heroi na lista de espera da base id_base
	 Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */
int evento_espera(cabeca_LEF *LEF, base lista_bases[], int tempo, int id_heroi, int id_base);

/* Trata a desistência da entrada do heroi id_heroi na base id_base. Agenda outra viagem para id_heroi.
 	Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */
int evento_desiste(cabeca_LEF *LEF, int tempo, int id_heroi, int id_base);

/* "Avisa" o porteiro da base id_base sobre alguma mudança nos herois presentes. Trata a lista de espera e de presentes de id_base
	 Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */
int evento_avisa(cabeca_LEF *LEF, base lista_bases[], int tempo, int id_base);

/* Trata a entrada do heroi id_heroi na base id_base, agendando sua saída
 	Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */
int evento_entra(cabeca_LEF *LEF, base lista_bases[], heroi lista_herois[], int tempo, int id_heroi, int id_base);

/* Trata a saída do heroi id_heroi da base id_base
 	Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */
int evento_sai(cabeca_LEF *LEF, base lista_bases[], int tempo, int id_heroi, int id_base);

/* Trata a viagem do heroi id_heroi até a base b_destino, agendando sua chegada
	 Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */
int evento_viaja(cabeca_LEF *LEF, heroi lista_herois[], base lista_bases[], int tempo, int id_heroi, int b_destino);

/* Trata a missao, verificando se existe uma BMP
 	Retorna 1 para sucesso e 0 se existir algum erro com listas encadeadas na função. */
int evento_missao(cabeca_LEF *LEF, base lista_bases[], heroi lista_herois[], missao lista_missoes[], int tempo, int id_missao);

// Trata o final da simulação. Imprime estatísticas e desaloca todas as listas encadeadas usadas.
void evento_fim(cabeca_LEF *LEF, heroi lista_herois[], base lista_bases[], missao lista_missoes[], int tempo);

#endif
