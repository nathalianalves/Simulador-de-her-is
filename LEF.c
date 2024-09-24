#include "LEF.h"

// Cria uma lista
cabeca_LEF *cria_LEF() {
	cabeca_LEF *temp;
	
	temp = (cabeca_LEF*) malloc(sizeof(cabeca_LEF));
	temp->inicio = NULL;
	
	return temp;
};

// Desaloca uma lista
void libera_lista(cabeca_LEF *lista) {
	nodo_evento *per, *prox;
	
	per = lista->inicio;
	
	// Libera a memoria usada para per, guardando antes per->prox em prox para nao perder o resto da lista
	while (per != NULL) {
		prox = per->prox;
		
		free(per);
		
		per = prox;
	}
	
	// Libera o inicio da lista
	free(lista);
};

// Imprime uma LEF
void imprime_LEF(cabeca_LEF *lista) {
	nodo_evento *per;
	
	for (per = lista->inicio; per != NULL; per = per->prox) 
		printf("%d - %s\n\t info1 - %d, info2 - %d\n", (per->even).minuto, (per->even).nome, (per->even).info1, (per->even).info2);

};

// Cria um nodo para ser adicionado na lista
nodo_evento *cria_nodo_evento(evento *inserir) {
	nodo_evento *novo;
	
	novo = (nodo_evento*) malloc(sizeof(nodo_evento));
	
	// Copia as informações de "inserir" para o nodo novo
	strcpy((novo->even).nome, inserir->nome);
	(novo->even).minuto = inserir->minuto;
	(novo->even).info1 = inserir->info1;
	(novo->even).info2 = inserir->info2;
	
	novo->prox = NULL;
	
	return novo;
}

// Insere "inserir" de modo ordenado pelo minuto em lista
int insere_ordenado(cabeca_LEF *lista, evento *inserir) {
	nodo_evento *anterior, *per, *novo;
	
	per = lista->inicio;
	anterior = NULL;
	
	// Procura o lugar de "inserir", com base no minuto
	while ((per != NULL) && ((per->even).minuto <= inserir->minuto)) {
		anterior = per;
		per = per->prox;
	}

	novo = cria_nodo_evento(inserir);
	if (novo == NULL)
		return 0;
		
	// Insere "inserir" na posicao correta
	if (anterior == NULL) {
		novo->prox = lista->inicio;
		lista->inicio = novo;
	} else {
		novo->prox = anterior->prox;
		anterior->prox = novo;
	}
	
	return 1;
}

// Cria uma struct evento com os itens passados como parametro
evento cria_evento(char nome[], int minuto, int info1, int info2) {
	evento novo;
	
	strcpy(novo.nome, nome);
	novo.minuto = minuto;
	novo.info1 = info1;
	novo.info2 = info2;
	
	return novo;
}

// Usa as outras funcoes para inserir os parametros passados na LEF
int insere_LEF(cabeca_LEF *lista, char nome[], int minuto, int info1, int info2) {
	evento novo;
	
	novo = cria_evento(nome, minuto, info1, info2);
	return (insere_ordenado(lista, &novo));
}

// Retira o primeiro evento da LEF e retorna sua struct
evento retira_inicio_LEF(cabeca_LEF *LEF) {
  evento retirado;
  nodo_evento *temp;
  
  retirado = (LEF->inicio)->even;
  
  temp = LEF->inicio;
  LEF->inicio = LEF->inicio->prox;
  
  free(temp);
  
  return retirado;
}

// Retorna o campo minuto do evento e
int tira_tempo(evento e) {
	return e.minuto;
}

// Retorna o campo info1 do evento e
int tira_info1(evento e) {
	return e.info1;
}

// Retorna o campo info2 do evento e
int tira_info2(evento e) {
	return e.info2;
}

// Copia para a string nome (passada como parametro) o nome do evento e
void tira_nome(char nome[], evento e) {
	strcpy(nome, e.nome);
}
