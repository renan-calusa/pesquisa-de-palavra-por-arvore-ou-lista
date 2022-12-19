#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef char* Elemento;
typedef int Boolean;

typedef struct _no_arvore_ {

	Elemento valor;
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


void imprime_rec(No* no){

	// percurso in-ordem para a impressão dos elementos

	if(no){
		imprime_rec(no->esq);
		printf(" %d", no->valor);
		imprime_rec(no->dir);
	}
}


void imprime_arvore(Arvore* arvore){

	printf("Elementos na arvore:");
	imprime_rec(arvore->raiz);
	printf("\n");
}


No* busca_bin_rec(No* no, Elemento e){

	if(no){

		if(no->valor == e) return no;
		if(e < no->valor) return busca_bin_rec(no->esq, e);
		return busca_bin_rec(no->dir, e);
	}

	return NULL;
}


No* busca_bin(Arvore* arvore, Elemento e){
	
	return busca_bin_rec(arvore->raiz, e);	
}


Boolean insere_ord_rec(No* raiz, No* novo){

	if(novo->valor != raiz->valor){

		if(novo->valor < raiz->valor){

			if(raiz->esq) return insere_ord_rec(raiz->esq, novo);
			else raiz->esq = novo;
		}
		else{
			if(raiz->dir) return insere_ord_rec(raiz->dir, novo);
			else raiz->dir = novo;
		}
	
		return TRUE;
	}

	return FALSE;
}


Boolean insere_ord(Arvore* arvore, Elemento e){

	No* novo = (No*) malloc(sizeof(No));
	
	novo->valor = e;
	novo->esq = novo->dir = NULL;

	if(arvore->raiz) return insere_ord_rec(arvore->raiz, novo);
		
	arvore->raiz = novo;
	return TRUE;
}


No* encontra_pai_ord(No* raiz, No* no){

	if(raiz){

		if(raiz->esq == no) return raiz;
		if(raiz->dir == no) return raiz;
		if(no->valor < raiz->valor) return encontra_pai_ord(raiz->esq, no);
		if(no->valor > raiz->valor) return encontra_pai_ord(raiz->dir, no);
	}
		
	return NULL;
}
