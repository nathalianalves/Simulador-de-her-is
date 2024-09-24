#include "conjuntos.h"

// Retorna em ini_uniao a uniao dos dois conjuntos
void uniao_conj(cabeca_int *lista1, cabeca_int *lista2, cabeca_int *ini_uniao) {
	nodo_int *per;
	
	// Adiciona todos os elementos da 1ª lista em ini_uniao
	for (per = lista1->inicio; per != NULL; per = per->prox) 
		if (!existe(ini_uniao, per->elemento))
			insere_ordenado_int(ini_uniao, per->elemento);
		
	// Adiciona os elementos da 2ª lista que ainda nao foram adicionados em ini_uniao
	for (per = lista2->inicio; per != NULL; per = per->prox) 
		if (!existe(ini_uniao, per->elemento))
			insere_ordenado_int(ini_uniao, per->elemento);
}

// Retorna em ini_inter a intersecção dos dois conjuntos
void interseccao_conj(cabeca_int *lista1, cabeca_int *lista2, cabeca_int *ini_inter) {
	nodo_int *per;
	
	// Percorre a 1ª lista, adicionando no conjunto de insterseccao os elementos que estao, tambem, na 2ª lista
	for (per = lista1->inicio; per != NULL; per = per->prox) 
		if (existe(lista2, per->elemento))
			if (!existe(ini_inter, per->elemento))
				insere_ordenado_int(ini_inter, per->elemento);			
			
}

// Retorna 1 se elemento estiver na lista 
int existe(cabeca_int *lista, int elemento) {
	nodo_int *per;
	
	// Percorre a lista até o final OU até encontrar o elemento
	per = lista->inicio;
	while ((per != NULL) && (per->elemento != elemento))
		per = per->prox;
	
	// Verifica qual foi o motivo de saída do while
	if (per == NULL)
		return 0;
	return 1;
}

// Retorna 1 se lista1 contem lista2
int contem(cabeca_int *lista1, cabeca_int *lista2) {
	nodo_int *per;
	
	// Percorre lista2, verificando se todos os elementos estao em lista1
	for (per = lista2->inicio; per != NULL; per = per->prox) 
		if (!existe(lista1, per->elemento))
			return 0;
	
	return 1;
}

// Retorna 1 se lista1 for igual lista2
int iguais(cabeca_int *lista1, cabeca_int *lista2) {
	
	// Os dois conjuntos sao iguais se os dois se contem simultaneamente
	if ((contem(lista1, lista2)) && (contem(lista2, lista1)))
		return 1;
	return 0;	
	
}
