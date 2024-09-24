// Biblioteca de funções relacionadas à Lista de Eventos Futuros (LEF)
// Nathália Nogueira Alves - GRR20232349 - 2023

#ifndef LEF_H
#define LEF_H

#define MAX_CHAR 50

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mundo.h"

typedef struct eventos evento;
typedef struct n_evento nodo_evento;
typedef struct c_LEF cabeca_LEF;

struct eventos {
	char nome[MAX_CHAR];
	int minuto;
	int info1;
	int info2;
};

struct c_LEF {
	nodo_evento *inicio;
};

struct n_evento {
	evento even;
	nodo_evento *prox;
};


/* FUNÇÕES DE LISTA DE EVENTOS FUTUROS */

// Cria uma lista e retorna o ponteiro para seu início
cabeca_LEF *cria_LEF();

// Desaloca uma lista
void libera_lista(cabeca_LEF *lista);

// Imprime uma lista
void imprime_LEF(cabeca_LEF *lista);

// Cria struct com os parametros passados e a insere de modo ordenado na lista passada como parametro
int insere_LEF(cabeca_LEF *lista, char nome[], int minuto, int info1, int info2);

// Retira o primeiro evento da LEF e retorna sua struct
evento retira_inicio_LEF(cabeca_LEF *LEF);

/* FUNÇÕES COM STRUCT EVENTO */

// Retorna o campo minuto do evento e
int tira_tempo(evento e);

// Retorna o campo info1 do evento e
int tira_info1(evento e);

// Retorna campo info2 do evento e
int tira_info2(evento e);

// Copia para a string nome (passada como parametro) o nome do evento e
void tira_nome(char nome[], evento e);

#endif
