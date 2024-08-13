#include <iostream>
using namespace std;

class noh {
	friend class tree;
private:
	noh* esquerda;
	noh* direita;
	int conteudo;
	int altura;

public:
	noh(int n) { esquerda = nullptr; direita = nullptr; conteudo = n; altura = 1; }
};

class tree {
private:
	noh* raiz;

	int informa_altura(noh* aux) {
		if (aux == nullptr) {
			return 0;
		}
		return aux->altura;
	}

	void atualizar_altura(noh* aux) {
		int	altura_esquerda = informa_altura(aux->esquerda);
		int altura_direita = informa_altura(aux->direita);

		if (altura_esquerda > altura_direita) {
			aux->altura = altura_esquerda + 1;
			return;
		}
		else {
			aux->altura = altura_direita + 1;
			return;
		}
	}

	int fator_balanceamento(noh* aux) {
		if (aux == nullptr) {
			return 0;
		}

		int altura_esquerda = informa_altura(aux->esquerda);
		int altura_direita = informa_altura(aux->direita);
		int fator_balanceamento = altura_esquerda - altura_direita;

		return fator_balanceamento;
	}

	noh* rot_esquerda(noh* raiz) {
		noh* aux = raiz->direita;

		raiz->direita = aux->esquerda;
		aux->esquerda = raiz;

		atualizar_altura(raiz);
		atualizar_altura(aux);

		return aux;
	}

	noh* rot_direita(noh* raiz) {
		noh* aux = raiz->esquerda;

		raiz->esquerda = aux->direita;
		aux->direita = raiz;

		atualizar_altura(raiz);
		atualizar_altura(aux);

			return aux;
	}

	noh* rot_esquerda_direita(noh* raiz) {
		raiz->esquerda = rot_esquerda(raiz->esquerda);
		return rot_direita(raiz);
	}

	noh* rot_direita_esquerda(noh* raiz) {
		raiz->direita = rot_direita(raiz->direita);
		return rot_esquerda(raiz);
	}

	noh* arrumar_balanceamento(noh* sub_raiz) {

		if (sub_raiz == nullptr) { return sub_raiz; }
		
		atualizar_altura(sub_raiz);
		int Fbalanceamento = fator_balanceamento(sub_raiz);

		if ((Fbalanceamento >= -1) and (Fbalanceamento <= 1)) {
			return sub_raiz;
		}

		if ((Fbalanceamento > 1) and (fator_balanceamento(sub_raiz->esquerda) > 0)) {
			return rot_direita(sub_raiz);
		}

		if ((Fbalanceamento > 1) and (fator_balanceamento(sub_raiz->esquerda) < 0)) {
			sub_raiz->esquerda = rot_esquerda(sub_raiz->esquerda);
			return rot_direita(sub_raiz);
		}

		if ((Fbalanceamento < -1) and (fator_balanceamento(sub_raiz->esquerda) <= 0)) {
			return rot_esquerda(sub_raiz);
		}

		if ((Fbalanceamento < -1) and (fator_balanceamento(sub_raiz->esquerda) > 0)) {
			sub_raiz->direita = rot_direita(sub_raiz->direita);
			return rot_esquerda(sub_raiz);
		}
	}

	noh* inserir_aux(noh* sub_raiz, int n) {
		if (sub_raiz == nullptr) {
			noh* novo = new noh(n);
			return novo;
		}

		if (n > sub_raiz->conteudo) {
			sub_raiz->direita = inserir_aux(sub_raiz->direita, n);
		}
		else {
			sub_raiz->esquerda = inserir_aux(sub_raiz->esquerda, n);
		}
		return arrumar_balanceamento(sub_raiz);
	}

	noh* remove_menor(noh* sub_raiz) {
		if (sub_raiz->esquerda == nullptr) {
			return sub_raiz->direita;
		}
		else {
			sub_raiz->esquerda = remove_menor(sub_raiz->esquerda);
			return arrumar_balanceamento(sub_raiz);
		}
	}

	noh* minimo_aux(noh* raiz) {

		noh* aux = raiz;
		while (aux->esquerda != nullptr) {
			aux = aux->esquerda;
		}
		return aux;
	}

	noh* remover_aux(noh* sub_raiz, int n) {
		if (sub_raiz == nullptr) {
			throw runtime_error("Nõ nao encontrado");
		}
		noh* aux = sub_raiz;

		if (n < sub_raiz->conteudo) {
			sub_raiz->esquerda = remover_aux(sub_raiz->esquerda, n);
		}
		else if (n > sub_raiz->conteudo) {
			sub_raiz->direita = remover_aux(sub_raiz->direita, n);
		}
		else {
			if (sub_raiz->esquerda == nullptr) {
				aux = sub_raiz->direita;
			}
			else if (sub_raiz->direita == nullptr) {
				aux = sub_raiz->esquerda;
			}
			else {
				aux = minimo_aux(sub_raiz->direita);
				aux->direita = remove_menor(sub_raiz->direita);
				aux->esquerda = sub_raiz->esquerda;
			}
			delete sub_raiz;
		}
		return arrumar_balanceamento(aux);
	}

	void percorre_em_pre_ordem_aux(noh* aux) {

		if (aux != NULL) {
			cout << aux->conteudo << "|";
			percorre_em_pre_ordem_aux(aux->esquerda);
			percorre_em_pre_ordem_aux(aux->direita);
		}
	}

public:
	tree() { raiz = nullptr; }

	void inserir(int n) { raiz = inserir_aux(raiz, n); }
	void remover(int n) { raiz = remover_aux(raiz, n); }
	void percorre_em_pre_ordem() { percorre_em_pre_ordem_aux(raiz); }

};

int main() {

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
				cout << "Elemento " << n << " inserido com sucesso " << endl;
				break;

			case 'r':
				cin >> n;
				arvore.remover(n);
				cout << "elemento " << n << " removido com sucesso" << endl;
				break;

			case 'b':
				cin >> n;
				//cout << "Valor " << arvore.busca(n) << " encontrado" << endl;
				break;

			case 'm':
				// metodo de minimo
				//cout << "O menor item da arvore e:" << arvore.minimo() << endl;
				break;

			case 'n':
				//metodo do maximo
				//cout << "O maior item da arvore e:" << arvore.maximo() << endl;
				break;

			case 'p':
				arvore.percorre_em_pre_ordem();
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
