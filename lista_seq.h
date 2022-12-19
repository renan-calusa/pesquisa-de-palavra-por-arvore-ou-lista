#define FALSE 0
#define TRUE 1

typedef char* Elemento;
typedef int Boolean;

typedef struct {

	Elemento* elemento;
	int livre;
	int capacidade;

} ListaSequencial;


ListaSequencial* cria_lista(int capacidade){

	ListaSequencial * lista =  (ListaSequencial *) malloc (sizeof(ListaSequencial));
	lista->elemento = (Elemento*) malloc (capacidade * sizeof(Elemento));
	lista->capacidade = capacidade;
	lista->livre = 0;

	return lista;
}

void destroi_lista(ListaSequencial* lista){

	free(lista->elemento);
	free(lista);
}


int busca(ListaSequencial* lista, Elemento e){

	// busca binária! ;)

	int ini = 0;
	int fim = lista->livre - 1;
	int meio;

	while(ini <= fim){

		meio = (ini + fim) / 2;

		if(e == lista->elemento[meio] ) return meio;
		if(e < lista->elemento[meio]) fim = meio - 1;
		if(e > lista->elemento[meio]) ini = meio + 1;
	}
		
	return -1;
}


int for_recursivo_insere(ListaSequencial* lista, Elemento e, int j){
	int i;
	for(i = lista->livre; i > 0 && lista->elemento[i - 1][j] >= e[j]; i--){
			
			if (lista->elemento[i - 1][j] == e[j]) {
				j++;
				for_recursivo_insere(lista, e, j);
			}
		
			lista->elemento[i] = lista->elemento[i - 1];
		}
	return i;
}


Boolean insere(ListaSequencial* lista, Elemento e){

	int i;
	int j = 0;

	if(lista->livre < lista->capacidade) {

		i = for_recursivo_insere(lista, e, j);

		lista->elemento[i] = e;
		lista->livre++;

		return TRUE;
	}

	return FALSE;
}



void imprime_lista(ListaSequencial * lista){

	int i;

	printf("Lista:");

	for(i = 0; i < lista->livre; i++){

		printf(" %s", lista->elemento[i]);
	}

	printf("\n");
}
