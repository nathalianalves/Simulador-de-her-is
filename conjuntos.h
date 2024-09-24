// Biblioteca de funções relacionadas a conjuntos
// Nathália Nogueira Alves - GRR20232349 - 2023

#ifndef CONJUNTOS_H
#define CONJUNTOS_H

#include "lista_encadeada.h"

// Retorna na lista ini_uniao a uniao de lista1 com lista2
void uniao_conj(cabeca_int *lista1, cabeca_int *lista2, cabeca_int *ini_uniao);

// Retorna em ini_inter a interseccao de lista1 com lista2
void interseccao_conj(cabeca_int *lista1, cabeca_int *lista2, cabeca_int *ini_inter);

// Verifica se elemento está na lista 
int existe(cabeca_int *lista, int elemento);

// Verifica se lista2 esta contida em lista1
int contem(cabeca_int *lista1, cabeca_int *lista2);

// Verifica se lista1 e lista2 sao iguais
int iguais(cabeca_int *lista1, cabeca_int *lista2);

#endif
