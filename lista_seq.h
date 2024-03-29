#define FALSE 0
#define TRUE 1


typedef int Boolean;
extern int tamanho_da_palavra;
extern int quantidade_linha;
double* search_time;
extern char** ponteiros_linha;


typedef struct aux_modulo {

	char* word;
	int count;
	int* linha;
	int sentinela;

} Modulo;


typedef struct aux_matriz {

	int livre;
	int tamanho;
	Modulo** lista_de_modulos;

} Matriz;


Matriz* cria_matriz(int tamanho_matriz) {

	Matriz* matriz = malloc(sizeof(Matriz)*tamanho_matriz);

	matriz->tamanho = tamanho_matriz;
	matriz->livre = 0;
	matriz->lista_de_modulos = (Modulo**) malloc(sizeof(Modulo*)*tamanho_matriz);

	for(int i=0; i<tamanho_matriz; i++) {
		
		matriz->lista_de_modulos[i] = (Modulo*) malloc(sizeof(Modulo));
		matriz->lista_de_modulos[i]->word = (char*) malloc(sizeof(char)*tamanho_da_palavra);
		matriz->lista_de_modulos[i]->count = 0;
		matriz->lista_de_modulos[i]->linha = (int*) malloc(sizeof(int)*quantidade_linha);
		matriz->lista_de_modulos[i]->sentinela = 0;
		// prevenir lixo de memoria
		for(int j=0; j<quantidade_linha; j++) matriz->lista_de_modulos[i]->linha[j] = -1;
	}

	return matriz;
}


Boolean busca_matriz(Matriz* matriz, char* palavra) {

	int ini = 0;
	int fim = matriz->livre - 1;
	int meio;
	struct timespec strt, stp;

	clock_gettime(CLOCK_REALTIME, &strt);

	while(ini <= fim){

		meio = (ini + fim) / 2;

		if (strcmp(palavra, matriz->lista_de_modulos[meio]->word) == 0) return meio;
		if (strcmp(palavra, matriz->lista_de_modulos[meio]->word) > 0) ini = meio + 1;
		if (strcmp(palavra, matriz->lista_de_modulos[meio]->word) < 0) fim = meio - 1;
	}
	
	clock_gettime(CLOCK_REALTIME, &stp);

	*search_time = (stp.tv_sec - strt.tv_sec) * 1000.0 + (stp.tv_nsec - strt.tv_nsec) / 1000000.0;

	return -1;
}


Boolean insere_matriz(Matriz* matriz, char* palavra, int line){
	
	// Verificar, numa lista nao vazia, a existencia de elemento repetido
	int aux = busca_matriz(matriz, palavra);

	if ((matriz->livre != 0) && (aux != -1)) {
		
		// Se o elemento se repete, adiciona a contagem e a linha

		matriz->lista_de_modulos[aux]->count++;

		int livre = matriz->lista_de_modulos[aux]->sentinela;

		// retornar falso caso a linha ja esteja na lista de linhas
		for (int k=livre; k>=0; k--) {
			if (matriz->lista_de_modulos[aux]->linha[k] == line) return FALSE;
		}

		matriz->lista_de_modulos[aux]->linha[livre] = line;
		matriz->lista_de_modulos[aux]->sentinela++;

		return FALSE;
	}


	if(matriz->livre < matriz->tamanho) {

		int i;

		for(i=matriz->livre; i > 0 && (strcmp(matriz->lista_de_modulos[i - 1]->word, palavra) > 0); i--) {

			// "Passar os elementos para tras" arrumando a lista
			matriz->lista_de_modulos[i]->word = matriz->lista_de_modulos[i-1]->word;
			matriz->lista_de_modulos[i]->count = matriz->lista_de_modulos[i-1]->count;

			matriz->lista_de_modulos[i]->sentinela = matriz->lista_de_modulos[i-1]->sentinela;
			for(int j=0; j<quantidade_linha; j++) {
				matriz->lista_de_modulos[i]->linha[j] = matriz->lista_de_modulos[i-1]->linha[j];
			}
		}

		matriz->lista_de_modulos[i]->word = palavra;
		matriz->livre++;
		matriz->lista_de_modulos[i]->count = 1;

		// Adicionar a linha que a palavra  esta

		matriz->lista_de_modulos[i]->linha[0] = line;
		matriz->lista_de_modulos[i]->sentinela = 1;

		return TRUE;
	}

	return FALSE;
}


void imprime_lista(Matriz* matriz, char* palavra, int indice) {

	if (!(indice == -1)) {

		printf("Existem %i ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", matriz->lista_de_modulos[indice]->count, palavra);

		// linhas

		for (int i=0; i<quantidade_linha; i++) {
			
			int linha = matriz->lista_de_modulos[indice]->linha[i];

			if(linha != -1) printf("%05d: %s", linha + 1, ponteiros_linha[linha]);
		}

		printf("Tempo de busca: %.4f ms\n", *search_time);
	}


	else {

		printf("Palavra '%s' nao encontrada.\n", palavra);
		printf("Tempo de busca: %.4f ms\n", *search_time);
	}
}
