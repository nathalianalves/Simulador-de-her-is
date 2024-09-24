#include "eventos.h"

// Define o evento "CHEGA", adicionando os eventos necessários na LEF. Retorna 1 para sucesso e 0 para erro.
int evento_chega(cabeca_LEF *LEF, base lista_bases[], heroi lista_herois[], int tempo, int id_heroi, int id_base) {
	int quant_presentes, quant_espera, espera;
	
	quant_presentes = conta_elementos_int(lista_bases[id_base].presentes);
	quant_espera = conta_elementos_int(lista_bases[id_base].espera);
	
	// Atualiza a base do heroi
	lista_herois[id_heroi].base = id_base;
	
	// Verifica se tem vagas e se a fila de espera está vazia. Define se o herói vai esperar ou desistir de entrar.
	if ((quant_presentes < lista_bases[id_base].lotacao) && (quant_espera == 0))
		espera = 1;
	else
		espera = (lista_herois[id_heroi].paciencia > (10 * quant_espera));
	
	// Insere os eventos necessários, com base no valor de "espera". Imprime o que foi "decidido"
	if (espera) {
	
		printf("%6d: CHEGA HEROI %2d BASE %d (%2d/ %2d) ESPERA\n", tempo, id_heroi, id_base, quant_presentes, lista_bases[id_base].lotacao);
		if (insere_LEF(LEF, "ESPERA", tempo, id_heroi, id_base) == 0) {
			printf("Falha. Não foi possível adicionar evento na LEF.\n");
			return 0;
		}
		
	} else {
	
		printf("%6d: CHEGA HEROI %2d BASE %d (%2d/ %2d) DESISTE\n", tempo, id_heroi, id_base, quant_presentes, lista_bases[id_base].lotacao);
 		if (insere_LEF(LEF, "DESISTE", tempo, id_heroi, id_base) == 0) {
 			printf("Falha. Não foi possível adicionar evento na LEF.\n");
			return 0;
		}
	
	}
	
	return 1;
	
}


// Define o evento "ESPERA", adicionando os eventos necessários na LEF. Retorna 1 para sucesso e 0 para erro.
int evento_espera(cabeca_LEF *LEF, base lista_bases[], int tempo, int id_heroi, int id_base) {
	int quant_espera;
	
	quant_espera = conta_elementos_int(lista_bases[id_base].espera);

	// Coloca o heroi id_heroi na fila de espera da base id_base 
	if (insere_fim_int(lista_bases[id_base].espera, id_heroi) == 0) {
		printf("Falha. Não foi possível adicionar na fila de espera da base.\n");
		return 0;
	}
	
	// Imprime os dados do evento e insere AVISA na LEF
	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, id_heroi, id_base, quant_espera);
	if (insere_LEF(LEF, "AVISA", tempo, id_base, 0) == 0) {
		printf("Falha. Não foi possível adicionar evento na LEF.\n");
		return 0;
	}
	
	return 1;
	
}


// Define o evento "DESISTE", adicionando os eventos necessários na LEF. Retorna 1 para sucesso e 0 para erro.
int evento_desiste(cabeca_LEF *LEF, int tempo, int id_heroi, int id_base) {
	int destino;
	
	destino = sorteia_num(0, N_BASES-1);
	
	// Imprime os dados do evento
	printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, id_heroi, id_base);
	
	// Adiciona o evento necessário na LEF
	if (insere_LEF(LEF, "VIAJA", tempo, id_heroi, destino) == 0) {
		printf("Falha. Não foi possível adicionar evento na LEF.\n");
		return 0;
	}
	
	return 1;
	
}


// Define o evento "AVISA",  adicionando os eventos necessários na LEF. Retorna 1 para sucesso e 0 para erro.
int evento_avisa(cabeca_LEF *LEF, base lista_bases[], int tempo, int id_base) {
	int quant_presentes, quant_espera, quant_vagas, h_removido;
	
	quant_presentes = conta_elementos_int(lista_bases[id_base].presentes);
	quant_espera = conta_elementos_int(lista_bases[id_base].espera);
		
	// Calcula a quantidade de vagas restantes em id_base
	quant_vagas = lista_bases[id_base].lotacao - quant_presentes;
	
	// Imprime os dados do evento
	printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA ", tempo, id_base, quant_presentes, lista_bases[id_base].lotacao);
	imprime_lista_int(lista_bases[id_base].espera);
	printf("\n");
	
	// Enquanto ainda existem vagas, administra a fila de espera e permite a entrada do primeiro da fila
	while ((quant_vagas > 0) && (quant_espera > 0)) {
		
		// Armazena o id do primeiro heroi da fila de espera em h_removido	
		h_removido = (lista_bases[id_base].espera->inicio)->elemento;

		// Retira o primeiro heroi da fila e diminui a quantidade de herois na fila de espera
		if (remove_inicio_int(lista_bases[id_base].espera) == 0) {
			printf("Falha. Não foi possível remover da lista de espera.\n");
			return 0;
		}
		quant_espera--;
		
		// Insere o primeiro heroi da fila de espera nos presentes e diminui a quantidade de herois na lista de presentes
		if (insere_ordenado_int(lista_bases[id_base].presentes, h_removido) == 0) {
			printf("Falha. Não foi possível adicionar na lista de presentes.\n");
			return 0;
		}
		quant_vagas--;
		
		printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", tempo, id_base, h_removido);
		if (insere_LEF(LEF, "ENTRA", tempo, h_removido, id_base) == 0) {
			printf("Falha. Não foi possível adicionar evento na LEF.\n");
			return 0;
		}
		
	}
	
	return 1;
	
}


// Define o evento "ENTRA", adicionando os eventos necessários na LEF. Retorna 1 para sucesso e 0 para erro.
int evento_entra(cabeca_LEF *LEF, base lista_bases[], heroi lista_herois[], int tempo, int id_heroi, int id_base) {
	int tempo_permanencia, quant_presentes;
		
	quant_presentes = conta_elementos_int(lista_bases[id_base].presentes);	
	
	// Calcula o tempo que o heroi id_heroi ficará na base id_base e adiciona o evento de saída
	tempo_permanencia = 15 + lista_herois[id_heroi].paciencia * sorteia_num(1, 20);
	if (insere_LEF(LEF, "SAI", tempo + tempo_permanencia, id_heroi, id_base) == 0) {
		printf("Falha. Não foi possível adicionar evento na LEF.\n");
		return 0;
	}
	
	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, id_heroi, id_base, quant_presentes, lista_bases[id_base].lotacao, tempo+tempo_permanencia);
	
	return 1;
	
}


// Define o evento "SAI", adicionando os eventos necessários na LEF. Retorna 1 para sucesso e 0 para erro.
int evento_sai(cabeca_LEF *LEF, base lista_bases[], int tempo, int id_heroi, int id_base) {
	int destino, quant_presentes;
	
	if (remove_elemento_int(lista_bases[id_base].presentes, id_heroi) == 0) {
		printf("Falha. Não foi possível retirar herói da lista de presentes.\n");
		return 0;
	}
	 
	destino = sorteia_num(0, N_BASES-1);
	
	quant_presentes = conta_elementos_int(lista_bases[id_base].presentes);
	
	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, id_heroi, id_base, quant_presentes, lista_bases[id_base].lotacao);

	if (insere_LEF(LEF, "VIAJA", tempo, id_heroi, destino) == 0) {
		printf("Falha. Não foi possível adicionar evento na LEF.\n");
		return 0;
	}
	
	if (insere_LEF(LEF, "AVISA", tempo, id_base, 0) == 0) {
		printf("Falha. Não foi possível adicionar evento na LEF.\n");
		return 0;
	}
	
	return 1;
	
};


// Retorna a distancia entre os dois locais.
int calcula_distancia(int local1[], int local2[]) {
	int x1, x2, y1, y2;
	
	x1 = local1[0];
	x2 = local2[0];
	y1 = local1[1];
	y2 = local2[1];
	
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


// Define o evento "VIAJA", adicionando os eventos necessários na LEF. Retorna 1 para sucesso e 0 para erro.
int evento_viaja(cabeca_LEF *LEF, heroi lista_herois[], base lista_bases[], int tempo, int id_heroi, int b_destino) {
	int distancia, b_atual, duracao;
	
	b_atual = lista_herois[id_heroi].base;
	
	// Calcula a distancia entre as duas bases e, com base no resultado, define a duracao da viagem
	distancia = calcula_distancia(lista_bases[b_atual].local, lista_bases[b_destino].local);
	duracao = distancia / lista_herois[id_heroi].velocidade;
	
	printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, id_heroi, b_atual, b_destino, distancia, lista_herois[id_heroi].velocidade, tempo + duracao);

	if (insere_LEF(LEF, "CHEGA", tempo + duracao, id_heroi, b_destino) == 0) {
		printf("Falha. Não foi possível adicionar evento na LEF.\n");
		return 0;
	}
	
	return 1;
	
}


// Troca, em v[], os elementos de ind1 e ind2
void troca(int v[], int ind1, int ind2) {
	int temp;
	
	temp = v[ind1];
	v[ind1] = v[ind2];
	v[ind2] = temp;
}


// Ordena o vetor distancias[] e repete o que foi feito nele em bases[]. Assim, o vetor bases[] ficará com a lista de ids de bases ordenados por distância.
void ordena_por_distancia(int distancias[], int bases[]) {
	int i, j, menor;
	
	// Faz selection sort
	for (i = 0; i < N_BASES; i++) {
		menor = i;
		
		for (j = i+1; j < N_BASES; j++)
			if (distancias[j] < distancias[menor])
				menor = j;
		
		troca(distancias, i, menor);
		troca(bases, i, menor);
	}
}	
	
		
// Define o evento "MISSAO", ajustando o que for necessário. Retorna 1 para sucesso e 0 para erro.
int evento_missao(cabeca_LEF *LEF, base lista_bases[], heroi lista_herois[], missao lista_missoes[], int tempo, int id_missao) {
	int i, distancia, BMP, distancias[N_BASES], bases_proximidade[N_BASES];
	cabeca_int *uniao_habilidades;
	nodo_int *per;
	
	printf("%6d: MISSAO %4d HAB REQ: ", tempo, id_missao);
	imprime_lista_int(lista_missoes[id_missao].habilidades);
	printf("\n");
	
	(lista_missoes[id_missao].tentativas)++;
	 
	// Calcula as distâncias e adiciona elas e os ids de base em seus vetores
	for (i = 0; i < N_BASES; i++) {
		distancia = calcula_distancia(lista_missoes[id_missao].local, lista_bases[i].local);
		distancias[i] = distancia;
		bases_proximidade[i] = i;
	}
	
	// Ordena o vetor bases[] para que fique com a lista de bases ordenada por distância
	ordena_por_distancia(distancias, bases_proximidade);
	
	i = 0;
	BMP = 0;
	// Percorre a lista de bases ordenada por distancia, verificando se a missão pode ou não ser feita com os herois presentes
	while ((i < N_BASES) && (BMP == 0)) {
		
		uniao_habilidades = cria_lista_int();
		if (uniao_habilidades == NULL) {
			printf("Falha. Não foi possível alocar memória para conjunto de união de habilidades.\n");
			return 0;
		}
		
		// Faz a união de todas as habilidades dos herois presentes em na base bases_proximidade[i]
		for (per = (lista_bases[bases_proximidade[i]].presentes)->inicio; per != NULL; per = per->prox) 
			uniao_conj(uniao_habilidades, lista_herois[per->elemento].habilidades, uniao_habilidades);
		
		printf("%6d: MISSAO %4d HAB BASE %d: ", tempo, id_missao, bases_proximidade[i]);
		imprime_lista_int(uniao_habilidades);
		printf("\n");

		// Verifica se a união de habilidades contêm as habilidades necessárias para a missão
		if (contem (uniao_habilidades, lista_missoes[id_missao].habilidades))
			BMP = 1;
		
		libera_lista_int(uniao_habilidades);
		
		i++;
	}
	
	if (BMP) {
		i--;
		
		// Aumenta em uma unidade a experiência de todos os herois presentes na BMP
		for (per = lista_bases[bases_proximidade[i]].presentes->inicio; per != NULL; per = per->prox)
			lista_herois[per->elemento].experiencia++;
		
		printf("%6d: MISSAO %4d CUMPRIDA BASE %d HEROIS: ", tempo, id_missao, bases_proximidade[i]);
		imprime_lista_int(lista_bases[bases_proximidade[i]].presentes);
		printf("\n"); 

		lista_missoes[id_missao].realizada = 1;
		
	} else {
	
		printf("%6d: MISSAO %4d IMPOSSIVEL\n", tempo, id_missao);
		if (insere_LEF(LEF, "MISSAO", tempo + 24*60, id_missao, 0) == 0) {
			printf("Falha. Não foi possível adicionar evento na LEF.\n");
			return 0;
		}
	}
	
	return 1;
	
}		

// Trata o final da simulação. Imprime estatísticas e desaloca todas as listas encadeadas usadas.
void evento_fim(cabeca_LEF *LEF, heroi lista_herois[], base lista_bases[], missao lista_missoes[], int tempo) {
	int i;
	float num_cumpridas, num_tentativas, porcent_missoes;
	
	// num_cumpridas armazena o número de missões finalizadas
	num_cumpridas = 0;
	// num_tentativas armazena a soma do número de tentativas das missões finalizadas
	num_tentativas = 0;
	
	// Percorre o vetor de missões, somando o necessário nas variáveis num_cumpridas e num_tentativas
	for (i = 0; i < N_MISSOES; i++) 
		if (lista_missoes[i].realizada == 1) {
			num_cumpridas++;
			num_tentativas = num_tentativas + lista_missoes[i].tentativas;
		}
		
	porcent_missoes = (num_cumpridas / (N_MISSOES * 1.0) * 100);
		
	printf("%6d: FIM\n", tempo);
	imprime_herois(lista_herois, N_HEROIS); // Imprime todos os heróis e seus atributos finais
	printf("%.0f/%d MISSOES CUMPRIDAS (%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO\n", num_cumpridas, N_MISSOES, porcent_missoes, num_tentativas/num_cumpridas); // Imprime as estatísticas das missões
	
	// Desaloca as listas de habilidade dos heróis
	for (i = 0; i < N_HEROIS; i++)
		libera_lista_int(lista_herois[i].habilidades);
	
	// Desaloca as listas de presentes e as filas de espera das bases
	for (i = 0; i < N_BASES; i++) {
		libera_lista_int(lista_bases[i].presentes);
		libera_lista_int(lista_bases[i].espera);
	}
	
	// Desaloca as listas de habilidades necessárias das missões
	for (i = 0; i < N_MISSOES; i++)
		libera_lista_int(lista_missoes[i].habilidades);
		
	// Desaloca a LEF
	libera_lista(LEF);
}
	
