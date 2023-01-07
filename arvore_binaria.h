#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef int Boolean;
extern int tamanho_da_palavra;
extern int quantidade_linha;
extern char** ponteiros_linha;
double* search_time;

typedef struct _no_arvore_ {

	char* word;
	int count;
	int* linha;
	int sentinela;

	struct _no_arvore_* esq;
	struct _no_arvore_* dir;

} No;


typedef struct {

	No* raiz;

} Arvore;


Arvore* cria_arvore(){

	Arvore* arvore = (Arvore*) malloc (sizeof(Arvore));
	arvore->raiz = NULL;
	return arvore;
}


No* busca_arvore_rec(No* no, char* palavra){

	if(no){

		if(strcmp(no->word, palavra) == 0) return no;
		if(strcmp(palavra, no->word) < 0) return busca_arvore_rec(no->esq, palavra);
		return busca_arvore_rec(no->dir, palavra);
	}

	return NULL;
}


No* busca_arvore(Arvore* arvore, char* palavra){
	
	struct timespec strt, stp;

	clock_gettime(CLOCK_REALTIME, &strt);

	No* resultado = busca_arvore_rec(arvore->raiz, palavra);

	clock_gettime(CLOCK_REALTIME, &stp);

	*search_time = (stp.tv_sec - strt.tv_sec) * 1000.0 + (stp.tv_nsec - strt.tv_nsec) / 1000000.0;

	return resultado;
}


Boolean insere_arvore_rec(No* raiz, No* novo){

	if(strcmp(novo->word, raiz->word) != 0){

		if(strcmp(novo->word, raiz->word) < 0){

			if(raiz->esq) return insere_arvore_rec(raiz->esq, novo);
			else raiz->esq = novo;
		}
		else{

			if(raiz->dir) return insere_arvore_rec(raiz->dir, novo);
			else raiz->dir = novo;
		}
	
		return TRUE;
	}

	return FALSE;
}


Boolean insere_arvore(Arvore* arvore, char* palavra, int line){

	No* novo = (No*) malloc(sizeof(No));
	
	// Verificar se é uma palavra repetida na arvore

	No* aux = busca_arvore(arvore, palavra);
	if (aux) {

		aux->count++;

		int livre = aux->sentinela;
		// retornar falso caso a linha ja esteja na lista de linhas
		for (int k=livre; k>=0; k--) {
			if (aux->linha[k] == line) return FALSE;
		}

		aux->linha[livre] = line;
		aux->sentinela++;

		return FALSE;
	}

	// Caso nao seja:

	novo->word = palavra;
	novo->count = 1;
	novo->linha = (int*) malloc(sizeof(int)*quantidade_linha);
	for(int i=0; i<quantidade_linha; i++) novo->linha[i] = -1;
	novo->sentinela = 0;
	novo->linha[0] = line;
	novo->sentinela++;
	novo->esq = novo->dir = NULL;

	if(arvore->raiz) return insere_arvore_rec(arvore->raiz, novo);
		
	arvore->raiz = novo;

	return TRUE;
}


void imprime_arvore(Arvore* arvore, char* palavra, No* no) {

	// Verifica se o no é valido (se a busca deu certo)

	if(no) {

		printf("Existem %i ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", no->count, palavra);

		// linhas

		for (int i=0; i<quantidade_linha; i++) {
			
			int linha = no->linha[i];

			if(linha != -1) printf("%05d: %s", linha + 1, ponteiros_linha[linha]);
		}

		printf("Tempo de busca: %.4f ms\n", *search_time);
	}

	// Se no == NULL

	else {

		printf("Palavra '%s' nao encontrada.\n", palavra);
		printf("Tempo de busca: %.4f ms\n", *search_time);
	}
}
