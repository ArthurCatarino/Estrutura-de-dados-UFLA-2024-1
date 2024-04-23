#include <iostream>
using namespace std;

class noh {
	friend class lista;
private:
	noh* proximo;
	string nome;
	int id;
public:
	noh(string n, int n2) { nome = n; id = n2; proximo = nullptr;}
};

class lista {
private:
	noh* primeiro;
	int tamanho;
public:
	lista() { tamanho = 0; primeiro = nullptr; }
	bool busca(string nome) {
		if (tamanho == 0) { throw runtime_error("Lista Vazia"); }

		noh* aux = primeiro;
		while (aux != nullptr) {
			if (aux->nome == nome) {
				return true;
			}
			aux = aux->proximo;
		}
		return false;

	}
	void insere(string nome, int id) {

		noh* novo = new noh(nome, id);
		novo->proximo = primeiro;
		primeiro = novo;
		tamanho++;
	}
	void remover(string nome) {
		if (tamanho == 0) { throw runtime_error("Lista Vazia"); }

		noh* aux = primeiro;
		noh* auxA = nullptr;

		for (int i = 0; i < tamanho; i++) {
			if (aux->nome == nome) {
				auxA->proximo = aux->proximo;
				delete aux;
				i = tamanho;
				tamanho--;
			}
			else {
				auxA = aux;
				aux = aux->proximo;
			}
		}
	}
	void imprimir() {
		if (tamanho == 0) { throw runtime_error("Lista Vazia"); }

		noh* aux = primeiro;
		while (aux != nullptr) {
			cout << "Nome: " << aux->nome << " ID: " << aux->id << endl;
			aux = aux->proximo;
		}
	}
};

int main() {

	lista teste;
	int id;
	string nome;

	teste.insere("Joao", 13);
	teste.insere("Roberto", 29);
	teste.insere("Genivaldo", 34);

	teste.imprimir();

	cout << teste.busca("Joao") << endl;
	cout << teste.busca("Judsom") << endl;

	teste.remover("Roberto");
	teste.imprimir();
	
	return 0;
}
