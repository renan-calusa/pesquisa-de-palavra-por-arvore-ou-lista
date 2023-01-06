#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvore_binaria.h"
#include "lista_seq.h"
#include <ctype.h>

#define TAMANHO 1000
#define INPUT_BUFFER_SIZE 1024

char* strsep(char** stringp, const char* delim);
int prompt(int option, Matriz* matriz, Arvore* arvore);


int main(int argc, char** argv) {

	Matriz* matriz;
	Arvore* arvore;
	FILE* in;
	char* linha;
	char* copia_ponteiro_linha;
	char* quebra_de_linha;
	char* palavra;	
	int contador_linha;
	struct timespec start, stop;
	search_time = (double*) malloc(sizeof(double));
	
	char* tipo = argv[2];
	// 0 = lista e 1 = arvore
	int OPCAO = -1;


	if (strcmp(tipo, "arvore") == 0) {
		OPCAO = 1;
		arvore = cria_arvore();
	}


	if (strcmp(tipo, "lista") == 0) {

		OPCAO = 0;
		matriz = cria_matriz(TAMANHO);
	}

	
	/* --------------------------------------------------------------------------------------------------------- */


	// Verificando se faltam argumentos
	if(argc < 2) {

		printf("Falta argumentos!\n(Usage: ./script 'arquivo.txt' 'tipo de estrutura')\n");
		return 0;
	}


	// Obtain the start time
	clock_gettime(CLOCK_REALTIME, &start);

	// Arquivo de entrada
	in = fopen(argv[1], "r");

	contador_linha = 0;
	linha = (char*) malloc((TAMANHO + 1) * sizeof(char));

	while(in && fgets(linha, TAMANHO, in)){
		
		if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

		// printf("linha %03d: '%s'\n", contador_linha + 1, linha);

		copia_ponteiro_linha = linha;

		while( (palavra = strsep(&copia_ponteiro_linha, " ")) ){

			// inserir a palavra na matriz
			char* word = (char*) malloc(sizeof(char)*tamanho_da_palavra);

			for (int i=0; i<=20; i++) {
				if(palavra[i] == ' ' || palavra[i] == ',' || palavra[i] == '.' || palavra[i] == ';') {
					word[i] = '\0';	
					break;
				}
				
			 	word[i] = tolower(palavra[i]);
			}

			// Se a palavra for 'nao nula', insere na estrutura
			if(*word != ' ') {
				if (OPCAO == 0) insere(matriz, word);
				if (OPCAO == 1) insere_ord(arvore, word);
			}

		}

		contador_linha++;
	}
	

	// Obtain the stop time
	clock_gettime(CLOCK_REALTIME, &stop);

	// Calculate the elapsed time in milliseconds
	double time_taken = (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_nsec - start.tv_nsec) / 1000000.0;

	
	printf("Tipo de indice: '%s'\n", argv[2]);
	printf("Arquivo texto: '%s'\n", argv[1]);
	printf("Numero de linhas no arquivo: %i\n", contador_linha);
	printf("Tempo para carregar o arquivo e construir o indice: %f ms\n", time_taken);

	// imprime_matriz(matriz);
	// imprime_arvore(arvore);

	prompt(OPCAO, matriz, arvore);

	return 1;
}




char *strsep(char **stringp, const char *delim) { 
    char *rv = *stringp; 
    if (rv) { 
        *stringp += strcspn(*stringp, delim); 
        if (**stringp) 
            *(*stringp)++ = '\0'; 
        else 
            *stringp = 0; } 
    return rv; 
}


int prompt(int option, Matriz* matriz, Arvore* arvore) {

	char input[INPUT_BUFFER_SIZE];

	while (1) {
		printf("> ");
		fgets(input, INPUT_BUFFER_SIZE, stdin);

		// Remove the trailing newline character
		input[strcspn(input, "\n")] = 0;

		// Process the input
		if (strcmp(input, "help") == 0) {
			printf("\n-----------------------------------------------------------------------------\n\n");
			printf("As opcoes disponiveis sao:\n\n- fim/exit : sai do programa\n- help : mostra os comandos disponiveis\n- busca 'palavra' : busca uma certa palavra no texto\n\n");
			printf("-----------------------------------------------------------------------------\n\n");
			continue;
		}
		
		if ((strcmp(input, "fim") == 0) || (strcmp(input, "exit") == 0)) break;

		// String slicing to separate the terms:
		
		// Extract the first 5 char from input
		char command[6];
		strncpy(command, input, 5);
		command[5] = '\0';

		
		// Searching the word
		if (strcmp(command, "busca") == 0) {
			
			// Extract the word to be searched

			// First we need to discover the length of the input (without the '\0') to determine the length of the word
			int length = strlen(input);
			
			// Since 'busca' has 5 letters and a space   ->   busca word  -> length = 10, 10 - 6 = 4 + 1 '\0' = 5
			char word[(length - 6) + 1];

			// Copying the word from the input - Cuidado de retirar letras maiusculas
			int j = 0;
			int i = 0;
			for (i=6; i<= length; i++) {
				word[j] = tolower(input[i]);
				j++;
			}


			if (option == 0) {

				// BUSCA WORD LISTA
				int indice_aux = busca(matriz, word);
				printf("%i\n", indice_aux);
				imprime_lista(matriz, word, indice_aux);
			}


			if (option == 1) {
				
				// BUSCA WORD ARVORE
				break;
			}

		}

		else printf("Opcao invalida!\nComando nao conhecido, use 'help' para ver opcoes.\n");
	}
	return 1;
}
