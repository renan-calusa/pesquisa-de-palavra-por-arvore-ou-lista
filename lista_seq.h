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


int busca(ListaSequencial* lista, Elemento e){

	// busca binária!

	int ini = 0;
	int fim = lista->livre - 1;
	int meio;

	while(ini <= fim){

		meio = (ini + fim) / 2;

		if (strcmp(e, lista->elemento[meio]) == 0) return meio;
		if (strcmp(e, lista->elemento[meio]) > 0) ini = meio + 1;
		if (strcmp(e, lista->elemento[meio]) < 0) fim = meio - 1;
	}
		
	return -1;
}


Boolean insere(ListaSequencial* lista, Elemento e){

	int i;


	if(lista->livre < lista->capacidade) {

		for(i = lista->livre; i > 0 && (strcmp(lista->elemento[i - 1], e) > 0); i--) {

			if ((lista->livre != 0) && (busca(lista, e) != -1)) return FALSE;

			lista->elemento[i] = lista->elemento[i - 1];
		}

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

void destroi_lista(ListaSequencial* lista){

	free(lista->elemento);
	free(lista);
}
