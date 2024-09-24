// Biblioteca de funções relacionadas ao mundo e entidades de "The Boys"
// Nathália Nogueira Alves - GRR20232349 - 2023

#ifndef MUNDO_H
#define MUNDO_H

#include "conjuntos.h" 
#include "lista_encadeada.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 6
#define N_MISSOES T_FIM_DO_MUNDO / 100

typedef struct herois heroi;
typedef struct bases base;
typedef struct missoes missao;

struct herois {
	int id;
	int experiencia;
	int paciencia;
	int velocidade;
	cabeca_int *habilidades;
	int base;
};

struct missoes {
	int id;
	int local[2];
	cabeca_int *habilidades;
	int realizada;
	int tentativas;
};

struct bases {
	int id;
	int local[2];
	int lotacao;
	cabeca_int *presentes;
	cabeca_int *espera;
};


// Retorna um numero aleatorio entre min e max, inclusive
int sorteia_num(int min, int max);

/* FUNÇÕES COM HEROIS */

// Inicializa os atributos de um heroi (todos aleatoriamente, com exceção de EXP, que começa zerado) e os retorna no ponteiro *novo. Retorna 1 para sucesso e 0 para erro.
int inicializa_heroi(int id, heroi *novo);

// Imprime a lista de herois passada como parâmetro
void imprime_herois(heroi lista_herois[], int tamanho);

/* FUNÇÕES COM MISSÕES */

// Inicializa os atributos de uma missao e a retorna no ponteiro *novo. Retorna 1 para sucesso e 0 para erro.
int inicializa_missao(int id, missao *novo);

// Imprime uma missao
void imprime_missao(missao m);

/* FUNÇÕES COM BASES */

// Inicializa os atributos de uma base e a retorna no ponteiro *novo. Retorna 1 para sucesso e 0 para erro.
int inicializa_base(int id, base *novo);

// Imprime uma base
void imprime_base(base b);

#endif
