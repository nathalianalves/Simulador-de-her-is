// Biblioteca de funções relacionadas a listas encadeadas
// Nathália Nogueira Alves - GRR20232349 - 2023

#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct n_int nodo_int;
typedef struct c_int cabeca_int;

struct n_int {
	int elemento;
	nodo_int *prox;
};

struct c_int {
	nodo_int *inicio;
}; 	

// Imprime lista de inteiros
void imprime_lista_int(cabeca_int *lista);

// Inicializa uma lista, retornando o um ponteiro para ela
cabeca_int *cria_lista_int ();

// Insere elemento no comeco da lista 
int insere_inicio_int(cabeca_int *lista, int elemento);

// Insere a variavel elemento no final de uma lista de inteiros
int insere_fim_int(cabeca_int *lista, int elemento);

// Insere elemento na lista de forma ordenada
int insere_ordenado_int(cabeca_int *lista, int elemento);

// Retira o elemento dos parametros da lista, retornando 1 se der certo e 0 caso contrario
int remove_elemento_int(cabeca_int *lista, int elemento);

// Remove o primeiro elemento de uma lista de inteiros
int remove_inicio_int(cabeca_int *lista);

// Retorna a quantidade de elementos presentes na lista passada como parametro
int conta_elementos_int(cabeca_int *lista);

// Ordena a lista passada como parametro por selection sort
void selection_sort_int(cabeca_int *lista);

// Desaloca lista de inteiros
void libera_lista_int(cabeca_int *lista);

#endif
