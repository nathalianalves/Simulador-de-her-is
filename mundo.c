#include "mundo.h"

// Retorna um numero entre min e max, inclusive
int sorteia_num(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

// Inicializa os atributos do heroi passado como parametro. Retorna 1 para sucesso e 0 para erro.
int inicializa_heroi(int id, heroi *novo) {
	int i, quant_habilidades, habilidade;
	cabeca_int *cjto_habilidades;
	
	cjto_habilidades = cria_lista_int();
	if (cjto_habilidades == NULL) {
		printf("Falha. Não foi possível alocar memória para lista de habilidades do herói.\n");
		return 0;
	}
	
	quant_habilidades = sorteia_num(1, 3);
	
	// Usa a quantidade de habilidades sorteada para controlar o loop
	for (i = 0; i < quant_habilidades; i++) {
		habilidade = sorteia_num(0, N_HABILIDADES-1);
		
		// Se a habilidade for igual a alguma das já sorteadas, sorteia de novo
		while (existe (cjto_habilidades, habilidade))
			habilidade = sorteia_num(0, N_HABILIDADES-1);
			
		if (insere_ordenado_int(cjto_habilidades, habilidade) == 0) {
			printf("Falha. Não foi possível inserir habilidade na lista do herói.\n");
			return 0;
		};
	}
	
	// Atribui os valores definidos ao heroi
	novo->habilidades = cjto_habilidades;
	novo->id = id;
	novo->experiencia = 0;
	novo->paciencia = sorteia_num(0, 100);
	novo->velocidade = sorteia_num(50, 5000);
	novo->base = -1;
	
	return 1;
}

// Imprime os herois e seus atributos
void imprime_herois(heroi lista_herois[], int tamanho) {
	int i;
	
	for (i = 0; i < tamanho; i++) {
		printf("HEROI %2d PAC %3d VEL %4d EXP %4d HABS ", lista_herois[i].id, lista_herois[i].paciencia, lista_herois[i].velocidade, lista_herois[i].experiencia);
		imprime_lista_int(lista_herois[i].habilidades);
		printf("\n");
	}
}


// Inicializa os atributos da missao passada como parametro. Retorna 1 para sucesso e 0 para erro.
int inicializa_missao(int id, missao *novo) {
	int i, quant_habilidades, habilidade;
	cabeca_int *cjto_habilidades;

	cjto_habilidades = cria_lista_int();
	if (cjto_habilidades == NULL) {
		printf("Falha. Não foi possível alocar memória para o conjunto de habilidades necessárias para a missão.\n");
		return 0;
	}
	quant_habilidades = sorteia_num(6, 10);
	
	for (i = 0; i < quant_habilidades; i++) {
		habilidade = sorteia_num(0, N_HABILIDADES-1);
		
		while (existe(cjto_habilidades, habilidade))
			habilidade = sorteia_num(0, N_HABILIDADES-1);
		
		if (insere_ordenado_int(cjto_habilidades, habilidade) == 0) {
			printf("Falha. Não foi possível inserir habilidade na lista de habilidades necessárias para a missão.\n");
			return 0;
		}
	}
	
	novo->habilidades = cjto_habilidades;
	novo->id = id;
	novo->local[0] = sorteia_num(0, N_TAMANHO_MUNDO-1);
	novo->local[1] = sorteia_num(0, N_TAMANHO_MUNDO-1);
	novo->realizada = 0;
	novo->tentativas = 0;
	
	return 1;
}

// Imprime uma missao
void imprime_missao(missao m) {
	printf("MISSAO %2d (%5d, %5d) HAB REQ: ", m.id, m.local[0], m.local[1]);
	imprime_lista_int(m.habilidades);
}

// Inicializa os atributos da base passada como ponteiro. Retorna 1 para sucesso e 0 para erro.
int inicializa_base(int id, base *novo) {
	cabeca_int *lista_presentes, *fila_espera;
	
	lista_presentes = cria_lista_int();
	if (lista_presentes == NULL) {
		printf("Falha. Não foi possível alocar memória para a lista de presentes da base.\n");
		return 0;
	}
	
	fila_espera = cria_lista_int();
	if (fila_espera == NULL) {
		printf("Falha. Não foi possível alocar memória para a fila de espera da base.\n");
		return 0;
	}
	
	novo->id = id;
	novo->local[0] = sorteia_num(0, N_TAMANHO_MUNDO-1);
	novo->local[1] = sorteia_num(0, N_TAMANHO_MUNDO-1);
	novo->lotacao = sorteia_num(3, 10);
	novo->presentes = lista_presentes;
	novo->espera = fila_espera;
	
	return 1;
}

// Imprime uma base
void imprime_base(base b) {
	printf("BASE %2d LOCAL (%5d, %5d) LOTACAO %2d\n", b.id, b.local[0], b.local[1], b.lotacao);
	printf("\tPresentes: ");
	imprime_lista_int(b.presentes);
	printf("\n");
	printf("\tEspera: ");
	imprime_lista_int(b.espera);
	printf("\n");
}	
	
