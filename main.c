#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvore_binaria.h"
#include "lista_seq.h"
#include <ctype.h>

#define TAMANHO 1000
#define INPUT_BUFFER_SIZE 1024

char *strsep(char **stringp, const char *delim);
int prompt(int option, ListaSequencial* lista_seq, Arvore* arvore);


int main(int argc, char ** argv) {

	ListaSequencial* lista_seq;
	Arvore* arvore;
	FILE* in;
	char* linha;
	char* copia_ponteiro_linha;
	char* quebra_de_linha;
	char* palavra;	
	int contador_linha;
	clock_t start, stop;
	
	char* tipo = argv[2];
	int OPCAO = -1;		// 0 = lista e 1 = arvore


	if (strcmp(tipo, "arvore") == 0) {
		OPCAO = 1;
		arvore = cria_arvore();
	}



	if (strcmp(tipo, "lista") == 0) {

		OPCAO = 0;
		lista_seq = cria_lista(TAMANHO);
	}

	

	/* --------------------------------------------------------------------------------------------------------- */


	// Verificando se faltam argumentos
	if(argc < 2) {

		printf("Falta argumentos!\n(Usage: ./script 'arquivo.txt' 'tipo de estrutura')\n");
		return 0;
	}


	// Arquivo de entrada
	start = clock();
	in = fopen(argv[1], "r");

	contador_linha = 0;
	linha = (char*) malloc((TAMANHO + 1) * sizeof(char));

	while(in && fgets(linha, TAMANHO, in)){
		
		if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

		// printf("linha %03d: '%s'\n", contador_linha + 1, linha);

		// fazemos uma copia do endereço que corresponde ao array de chars 
		// usado para armazenar cada linha lida do arquivo pois a função 'strsep' 
		// modifica o endereço do ponteiro a cada chamada feita a esta função (e 
		// não queremos que 'linha' deixe de apontar para o inicio do array).

		copia_ponteiro_linha = linha;

		while( (palavra = strsep(&copia_ponteiro_linha, " ")) ){

			// antes de guardar a palavra em algum tipo de estrutura usada
			// para implementar o índice, será necessário fazer uma copia
			// da mesma, uma vez que o ponteiro 'palavra' aponta para uma 
			// substring dentro da string 'linha', e a cada nova linha lida
			// o conteúdo da linha anterior é sobreescrito.


			char* copia = palavra;
			char* word = (char*) malloc(sizeof(char)*25); 

			for (int i=0; i<=25; i++) {
				if(copia[i] == ' ' || copia[i] == ',' || copia[i] == '.' || copia[i] == ';') {
					word[i] = '\0';	
					break;
				}
				
			 	word[i] = tolower(copia[i]);
			}

			if (OPCAO == 0) insere(lista_seq, word);
			if (OPCAO == 1) insere_ord(arvore, word);

		}

		contador_linha++;
	}
	

	stop = clock();

	double time_taken = (double) (stop - start)/CLOCKS_PER_SEC*1000;

	
	printf("Tipo de indice: '%s'\n", argv[2]);
	printf("Arquivo texto: '%s'\n", argv[1]);
	printf("Numero de linhas no arquivo: %i\n", contador_linha);
	printf("Tempo para carregar o arquivo e construir o indice: %d ms\n", time_taken);

	imprime_lista(lista_seq);
	// imprime_arvore(arvore);

	prompt(OPCAO, lista_seq, arvore);

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


int prompt(int option, ListaSequencial* lista_seq, Arvore* arvore) {

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

			// Copying the word from the input
			int j = 0;
			int i = 0;
			for (i=6; i<= length; i++) {
				word[j] = input[i];
				j++;
			}


			if (option == 0) busca(lista_seq, word); // BUSCA WORD LISTA
			if (option == 1) break; // BUSCA WORD ARVORE

		}

		else printf("Opcao invalida!\nComando nao conhecido, use 'help' para ver opcoes.\n");
	}
	return 1;
}
