#define FALSE 0
#define TRUE 1


typedef int Boolean;

typedef struct aux_modulo {

	char* word;
	int count;
	int* linha;

} Modulo;


typedef struct aux_matriz {

	int livre;
	int tamanho;
	Modulo** lista_de_modulos;

} Matriz;


Matriz* cria_matriz(int tamanho_matriz, int quantidade_linha) {

	Matriz* matriz = malloc(sizeof(Matriz)*tamanho_matriz);

	matriz->tamanho = tamanho_matriz;
	matriz->livre = 0;
	matriz->lista_de_modulos = (Modulo**) malloc(sizeof(Modulo*)*tamanho_matriz);

	for(int i=0; i<tamanho_matriz; i++) {
		
		matriz->lista_de_modulos[i] = (Modulo*) malloc(sizeof(Modulo));
		matriz->lista_de_modulos[i]->word = (char*) malloc(sizeof(char)*20);
		matriz->lista_de_modulos[i]->count = 0;
		matriz->lista_de_modulos[i]->linha = (int*) malloc(sizeof(int)*quantidade_linha);
		// prevenir lixo de memoria
		for(int j=0; j<quantidade_linha; j++) matriz->lista_de_modulos[i]->linha[j] = -1;
	}

	return matriz;
}


Boolean busca(Matriz* matriz, char* palavra) {

	int ini = 0;
	int fim = matriz->livre - 1;
	int meio;

	while(ini <= fim){

		meio = (ini + fim) / 2;

		if (strcmp(palavra, matriz->lista_de_modulos[meio]->word) == 0) return meio;
		if (strcmp(palavra, matriz->lista_de_modulos[meio]->word) > 0) ini = meio + 1;
		if (strcmp(palavra, matriz->lista_de_modulos[meio]->word) < 0) fim = meio - 1;
	}
		
	return -1;
}


Boolean insere(Matriz* matriz, char* palavra){

	// Verificar, numa lista nao vazia, a existencia de elemento repetido
	if ((matriz->livre != 0) && (busca(matriz, palavra) != -1)) {
				
		// Colocar a linha da palavra repetida na lista de linhas da palavra (...)
		return FALSE;
	}


	if(matriz->livre < matriz->tamanho) {

		int i;

		for(i=matriz->livre; i > 0 && (strcmp(matriz->lista_de_modulos[i - 1]->word, palavra) > 0); i--) {

			matriz->lista_de_modulos[i]->word = matriz->lista_de_modulos[i-1]->word;
		}

		matriz->lista_de_modulos[i]->word = palavra;
		matriz->livre++;

		return TRUE;
	}

	return FALSE;
}


void imprime_matriz(Matriz* matriz){

	printf("Lista:");

	for(int i = 0; i < matriz->livre; i++){

		printf(" %s", matriz->lista_de_modulos[i]->word);
	}

	printf("\n");
}
