// Main do projeto "The Boys" 
// Nathália Nogueira Alves - GRR20232349 - 2023

#include "LEF.h"
#include "eventos.h"

int main() {
	int i, base_inicial, tempo, relogio, evento_info1, evento_info2, fim;
	char evento_nome[MAX_CHAR];
	heroi lista_herois[N_HEROIS];
	base lista_bases[N_BASES];
	missao lista_missoes[N_MISSOES];
	cabeca_LEF *LEF;
	evento evento_atual;
	
	srand(0);
	
	// Inicializa a LEF, tratando erros.
	LEF = cria_LEF();
	if (LEF == NULL) {
		printf("Falha. Não foi possível alocar memória para a LEF.\n");
		return 1;
	}
	
	// Inicializa todos os herois	
	for (i = 0; i < N_HEROIS; i++) 
		if (inicializa_heroi(i, &lista_herois[i]) == 0) {
			printf("Falha. Não foi possível criar herói.\n");
			return 1;
		}
	
	// Inicializa todas as bases
	for (i = 0; i < N_BASES; i++)
		if (inicializa_base(i, &lista_bases[i]) == 0) {
			printf("Falha. Não foi possível criar base.\n");
			return 1;
		}
	
	// Inicializa todas as missoes
	for (i = 0; i < N_MISSOES; i++)
		if (inicializa_missao(i, &lista_missoes[i]) == 0) {
			printf("Falha. Não foi possível criar missão.\n");
			return 1;
		}

	// Sorteia o tempo em que o heroi i chegará na sua base inicial, também sorteada. Insere o evento CHEGA com essas informações, tratando erros.
	for (i = 0; i < N_HEROIS; i++) {
		base_inicial = sorteia_num(0, N_BASES-1);
		tempo = sorteia_num(0, 4320);
		if (insere_LEF(LEF, "CHEGA", tempo, i, base_inicial) == 0) {
			printf("Falha. Não foi possível adicionar evento na LEF.\n");
			return 1;
		}
	}
	
	// Sorteia o tempo para o qual a missão i será agendada. Insere o evento MISSAO, tratando erros.
	for (i = 0; i < N_MISSOES; i++) {
		tempo = sorteia_num(0, T_FIM_DO_MUNDO);
		if (insere_LEF(LEF, "MISSAO", tempo, i, 0) == 0) {
			printf("Falha. Não foi possível adicionar evento na LEF.\n");
			return 1;
		}
	}
		
	// Insere o evento FIM na LEF, tratando erros.
	tempo = T_FIM_DO_MUNDO;
	if (insere_LEF(LEF, "FIM", tempo, 0, 0) == 0) {
		printf("Falha. Não foi possível adicionar evento na LEF.\n");
		return 1;
	}
	
	fim = 0;
	relogio = 0;
	// O loop para quando o relogio ultrapassar o tempo final OU quando o fim acontecer
	while ((relogio <= T_FIM_DO_MUNDO) && (fim == 0)) {
	
		// Retira as informações necessárias da LEF. 
		evento_atual = retira_inicio_LEF(LEF);
		relogio = tira_tempo(evento_atual);
		evento_info1 = tira_info1(evento_atual);
		evento_info2 = tira_info2(evento_atual);
		tira_nome(evento_nome, evento_atual);
			
		// Se evento_atual for o evento CHEGA, realiza o evento e trata erros
		if (strcmp(evento_nome, "CHEGA") == 0)
			if (evento_chega(LEF, lista_bases, lista_herois, relogio, evento_info1, evento_info2) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;
			}
		
		// Se evento_atual for o evento ESPERA, realiza o evento e trata erros
		if (strcmp(evento_nome, "ESPERA") == 0)
			if (evento_espera(LEF, lista_bases, relogio, evento_info1, evento_info2) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;
		}
		
		// Se evento_atual for o evento DESISTE, realiza o evento e trata erros
		if (strcmp(evento_nome, "DESISTE") == 0)
			if (evento_desiste(LEF, relogio, evento_info1, evento_info2) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;
			}
			
		// Se evento_atual for o evento AVISA, realiza o evento e trata erros
		if (strcmp(evento_nome, "AVISA") == 0)
			if (evento_avisa(LEF, lista_bases, relogio, evento_info1) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;
		}
		
		// Se evento_atual for o evento ENTRA, realiza o evento e trata erros
		if (strcmp(evento_nome, "ENTRA") == 0)
			if (evento_entra(LEF, lista_bases, lista_herois, relogio, evento_info1, evento_info2) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;
			}
			
		// Se evento_atual for o evento SAI, realiza o evento e trata erros
		if (strcmp(evento_nome, "SAI") == 0)
			if (evento_sai(LEF, lista_bases, relogio, evento_info1, evento_info2) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;	
			}
			
		// Se evento_atual for o evento VIAJA, realiza o evento e trata erros
		if (strcmp(evento_nome, "VIAJA") == 0)
			if (evento_viaja(LEF, lista_herois, lista_bases, relogio, evento_info1, evento_info2) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;
			}
			
		// Se evento_atual for o evento MISSAO, realiza o evento e trata erros
		if (strcmp(evento_nome, "MISSAO") == 0)
			if (evento_missao(LEF, lista_bases, lista_herois, lista_missoes, relogio, evento_info1) == 0) {
				printf("Falha. Não foi possível realizar evento.\n");
				return 1;
			}
			
		// Se evento_atual for o evento FIM, realiza o evento 
		if (strcmp(evento_nome, "FIM") == 0) { 
			evento_fim(LEF, lista_herois, lista_bases, lista_missoes, relogio);
			fim = 1;
		}
	}
	
	return 0;
}
