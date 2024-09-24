#include "lista_encadeada.h"

// Cria um nodo de inteiro com o elemento passado como parametro
nodo_int *cria_nodo_int(int elemento) {
	nodo_int *novo;
	
	novo = (nodo_int*) malloc(sizeof(nodo_int));
	novo->elemento = elemento;
	novo->prox = NULL;
	
	return novo;
};

// Imprime lista de inteiros
void imprime_lista_int(cabeca_int *lista) {
	nodo_int *per;
	
	printf("[ ");
	for (per = lista->inicio; per != NULL; per = per->prox) 
		printf("%2d ", per->elemento);
	printf("]");
};

// Inicializa uma lista, retornando um ponteiro para ela
cabeca_int *cria_lista_int () {
	cabeca_int *novo;
	
	novo = (cabeca_int*) malloc(sizeof(cabeca_int));
	novo->inicio = NULL;
	
	return novo;
}

// Insere elemento no comeco da lista inicio
int insere_inicio_int(cabeca_int *lista, int elemento) {
	nodo_int *novo;
	
	novo = cria_nodo_int(elemento);
	if (novo == NULL)
		return 0;
		
	novo->prox = lista->inicio;
	lista->inicio = novo;
	
	return 1;
};

// Insere a variavel elemento no final de uma lista de inteiros
int insere_fim_int(cabeca_int *lista, int elemento) {
	nodo_int *novo, *per;
	
	novo = cria_nodo_int(elemento);
	if (novo == NULL)
		return 0;
	
	if (lista->inicio == NULL) 
		lista->inicio = novo;
	else {
		per = lista->inicio;
		while (per->prox != NULL)
			per = per->prox;
		per->prox = novo;
	}
	
	return 1;
};

// Insere elemento na lista inicio de forma ordenada
int insere_ordenado_int(cabeca_int *lista, int elemento) {
	nodo_int *anterior, *per, *novo;
	
	per = lista->inicio;
	anterior = NULL;
	
	novo = cria_nodo_int(elemento);
	if (novo == NULL)
		return 0;
		
	while ((per != NULL) && (per->elemento < elemento)) {
		anterior = per;
		per = per->prox;
	}
	
	if (anterior == NULL) {
		novo->prox = lista->inicio;
		lista->inicio = novo;
	} else {
		novo->prox = anterior->prox;
		anterior->prox = novo;
	}
	
	return 1;
};

// Retira o elemento dos parametros da lista, retornando 1 se der certo e 0 caso contrario
int remove_elemento_int(cabeca_int *lista, int elemento) {
	nodo_int *anterior, *per;
	
	anterior = NULL;
	per = lista->inicio;
	
	// Usa per para saber se o elemento foi encontrado, e anterior para guardar qual ponteiro deverá ser mudado
	while ((per != NULL) && (per->elemento != elemento)) {
		anterior = per;
		per = per->prox;
	}
	
	// Confere se o elemento foi encontrado. Se foi, muda o ponteiro de "anterior"
	if (per != NULL) {
		if (anterior == NULL) 
			lista->inicio = per->prox;
		else
			anterior->prox = per->prox;
	
		free(per);
		
		return 1;
	}
	
	return 0;
};

// Remove o primeiro elemento de uma lista de inteiros
int remove_inicio_int(cabeca_int *lista) {
	nodo_int *temp;
	
	if (lista->inicio == NULL)
		return 0;
		
	temp = lista->inicio;
	lista->inicio = (lista->inicio)->prox;
	
	free(temp);
	
	return 1;
};

// Retorna a quantidade de elementos presentes na lista
int conta_elementos_int(cabeca_int *lista) {
	int quantidade;
	nodo_int *per;
	
	// Percorre a lista
	quantidade = 0;
	for (per = lista->inicio; per != NULL; per = per->prox)
		quantidade++;
	
	return quantidade;
}
	
// Ordena a lista passada como parametro por selection sort
void selection_sort_int(cabeca_int *lista) {
	nodo_int *selec, *menor, *per, *temp; 
	
	// "Selec" é usado para definir o elemento que está sendo decidido
	for (selec = lista->inicio; selec != NULL; selec = selec->prox) {
		menor = selec;
		
		// "Per" percorre a lista procurando o menor elemento e o guardando em "Menor"
		for (per = selec; per != NULL; per = per->prox) 
			if (per->elemento < menor->elemento)
				menor = per;
		
		// Troca o menor valor achado pelo menor valor encontrado
		temp = menor->prox;
		menor->prox = selec->prox;
		selec->prox = temp;
   }
};

// Desaloca uma lista
void libera_lista_int(cabeca_int *lista) {
	nodo_int *per, *prox;
	
	per = lista->inicio;
	
	// Libera a memoria usada para per, guardando antes per->prox em prox para nao perder o resto da lista
	while (per != NULL) {
		prox = per->prox;
		
		free(per);
		
		per = prox;
	}
	
	// Libera o inicio da lista
	free(lista);
}
