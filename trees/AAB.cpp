#include <iostream>
using namespace std;

class noh {
	friend class tree;
private:
	noh* esquerdo;
	noh* direito;
	int conteudo;


public:
	noh(int n) { conteudo = n; direito = NULL; esquerdo = NULL; };

};


class tree {
	friend class noh;
private:
	noh* raiz;

	noh* inserir_recursivamente(noh* atual, int n) {
		
		if (atual == nullptr) {
			noh* novo = new noh(n);
			return novo;
		}
		else {
			if (n > atual->conteudo) {
				atual->direito = inserir_recursivamente(atual->direito, n);
			}
			else {
				atual->esquerdo = inserir_recursivamente(atual->esquerdo, n);
			}
		}
		return atual;
	
	};

	noh* busca_recursiva(int n) {
		noh* aux = raiz;

		while (aux != NULL) {
			if (aux->conteudo == n) {
				return aux;
			}
			else if (n > aux->conteudo) {
				aux = aux->direito;
			}
			else if (n < aux->conteudo) {
				aux = aux->esquerdo;
			}
		}
		return NULL;
	
	}

	void percorre_em_ordem_aux(noh* aux) {
		if (aux != NULL) {
			percorre_em_ordem_aux(aux->esquerdo);
			cout << aux->conteudo << "|";
			percorre_em_ordem_aux(aux->direito);
		}
	}

	void percorre_em_pre_ordem_aux(noh* aux) {

		if (aux != NULL) {
			cout << aux->conteudo << "|";
			percorre_em_pre_ordem_aux(aux->esquerdo);
			percorre_em_pre_ordem_aux(aux->direito);
		}
	}

	void percorre_em_pos_ordem_aux(noh* aux) {
		if (aux != NULL) {
			percorre_em_pos_ordem_aux(aux->esquerdo);
			percorre_em_pos_ordem_aux(aux->direito);
			cout << aux->conteudo << "|";
		}
	}

	noh* remove_menor(noh* aux) {
		if (aux->esquerdo == NULL) { // Encontrou o sucessor
			return aux->direito;
		}
		else { // nao achou ainda, desce mais na subarvore
			aux->esquerdo = remove_menor(aux->esquerdo);
			return aux;
		}

	}

	noh* remover_recursivamente(noh* aux, int n) {
		if(aux == NULL) {
			throw runtime_error("No nao encontrado");
		}

		noh* novo_aux = nullptr;

		if (n < aux->conteudo) { // valor menor, vai pra SE
			aux->esquerdo = remover_recursivamente(aux->esquerdo, n);
			return aux;
		}
		else if (n > aux->conteudo) { // valor maior, vai pra SD
			aux->direito = remover_recursivamente(aux->direito, n);
			return aux;
		}
		else { // Aux e apagado aqui
			if (aux->esquerdo == NULL) { // quando o no nao tem filhos a esquerda
				novo_aux = aux->direito;
			}
			else if (aux->direito == NULL) { // quando o no nao tem filhos a direita
				novo_aux = aux->esquerdo;
			}
			else { // O no tem dois filhos 
				novo_aux = minimo_aux(aux->direito);
				novo_aux->direito = remove_menor(aux->direito);
				novo_aux->esquerdo = aux->esquerdo;
			}
			
			delete aux;
		}
		return novo_aux;
	}

	noh* minimo_aux(noh* aux) {
		while (aux->esquerdo != NULL) {
			aux = aux->esquerdo;
		}
		return aux;
	}

public:
	tree() { raiz = nullptr; }
	void inserir(int n) { raiz = inserir_recursivamente(raiz,n); }
	
	int maximo() {
		if (raiz == nullptr) {
			throw runtime_error("Arvore vazia");
		}

		noh* aux = raiz;
		while (aux->direito != NULL) {
			aux = aux->direito;
		}
		return aux->conteudo;

	}
	
	int minimo() {
		if (raiz == nullptr) {
			throw runtime_error("Arvore vazia");
		}

		noh* aux = minimo_aux(raiz);
		return aux->conteudo;

	}

	int busca(int n) {
		
		noh* resultado = busca_recursiva(n);
		if (resultado == NULL) {
			throw runtime_error("Valor nao encontrado");
		}

		return resultado->conteudo;

	}

	void percorre_em_ordem() { percorre_em_ordem_aux(raiz); }

	void percorre_em_pre_ordem() { percorre_em_pre_ordem_aux(raiz); }

	void percorre_em_pos_ordem() { percorre_em_pos_ordem_aux(raiz); }

	void remocao(int n) { raiz = remover_recursivamente(raiz, n);  }


};

int main () {

char opcao;
tree arvore;
int n;



do {
	try {
	cin >> opcao;
	switch (opcao) {
	case 'i':
		cin >> n;
		arvore.inserir(n);
		cout << "Elemento "  << n << " inserido com sucesso " << endl;
		break;

	case 'r':
		cin >> n;
		arvore.remocao(n);
		cout << "elemento " << n << " removido com sucesso" << endl;
		break;

	case 'b':
		cin >> n;
		cout << "Valor " << arvore.busca(n) << " encontrado" << endl;
		break;

	case 'm':
		// metodo de minimo
		cout << "O menor item da arvore e:" << arvore.minimo() << endl;
		break;

	case 'n':
		//metodo do maximo
		cout << "O maior item da arvore e:" << arvore.maximo() << endl;
		break;

	case 'p':
		cout << "1 = Percorrimento em pre-ordem" << endl << "2 = Percorrimento em ordem" << endl << "3 = Percorrimento em pos-ordem" << endl;
		cin >> n;
		switch (n) {
		case 1 :
			cout << "Arvore sendo percorrida em pre-ordem" << endl;
			arvore.percorre_em_pre_ordem();
			cout << endl;
			break;
		case 2: 
			cout << "Arvore sendo percorrida em ordem" << endl;
			arvore.percorre_em_ordem();
			cout << endl;
			break;

		case 3:
			cout << "Arvore sendo percorrida em pos-ordem" << endl;
			arvore.percorre_em_pos_ordem();
			cout << endl;
			break;
		}
		
		break;

	case 'f':
		//fim
		cout << "Fim" << endl;
	}

	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}

} while (opcao != 'f');

return 0;
}
