#include <iostream>
using namespace std;

class noh {
	friend class lista;
	friend class Hash;
private:
	noh* proximo;
	string nome;
	int id;
public:
	noh(string n, int n2) { nome = n; id = n2; proximo = nullptr;}
};

class lista {
	friend class Hash;
private:
	noh* primeiro;
	int tamanho;
	void UltimaRemocao() {
		
		noh* aux = primeiro;
		delete aux;
		primeiro = nullptr;
		tamanho--;

	}
public:
	lista() { tamanho = 0; primeiro = nullptr; }
	bool verifica(int chave) {
		if (tamanho == 0) { return false; }

		noh* aux = primeiro;
		while (aux != nullptr) {
			if (aux->id == chave) {
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
	
		noh* aux = primeiro;
		noh* auxA = nullptr;

		for (int i = 0; i < tamanho; i++) {
			if (aux->nome == nome) {
				if (tamanho == 1) { UltimaRemocao(); }
				else {
					auxA->proximo = aux->proximo;
					delete aux;
					i = tamanho;
					tamanho--;
				}
			}
			else {
				auxA = aux;
				aux = aux->proximo;
			}
		}
	}
	void imprimir() {
		noh* aux = primeiro;
		while (aux != nullptr) {
			cout << "Nome: " << aux->nome << " ID: " << aux->id << " | ";
			aux = aux->proximo;
		}
	}
	noh* busca(int chave) {

		noh* aux = primeiro;
		while (aux != nullptr) {
			if (aux->id == chave) {
				return aux;
			}
			aux = aux->proximo;
		}
		return nullptr;
	}
};

class Hash {
private:
	lista* tabela;
	int tamanhoHash;
	unsigned funcao(int chave) {

		return chave % tamanhoHash;

	}
public:
	Hash(int cap) { tamanhoHash = cap; tabela = new lista[tamanhoHash]; }
	~Hash(){delete tabela;}
	void inserir(string valor, int chave) {

		int posicao = funcao(chave);
		lista& teste = tabela[posicao];

		if (!teste.verifica(chave)) {
			teste.insere(valor, chave);
		}
		else {
			cout << "Item ja esta na tabela" << endl;
		}
	}
	string recuperavalor(int chave) {

		int posicao = funcao(chave);
		noh* elemento = tabela[posicao].busca(chave);
		if (elemento != nullptr) {
			return elemento->nome;
		}

		else
			return "Elemento nao encontrado";

	}
	void remover(int chave) {
		
		int posicao = funcao(chave);
		noh* elemento = tabela[posicao].busca(chave);
		if (elemento != nullptr) {
			tabela[posicao].remover(elemento->nome);
		}
		else {
			cout << "Elemento nao encontrado" << endl;
		}
	}
	void alterarvalor(string novovalor, int chave) {
		int posicao = funcao(chave);
		noh* elemento = tabela[posicao].busca(chave);
		if (elemento != nullptr) {
			elemento->nome = novovalor;
		}
		else
			cout << "Item nao encontrado" << endl;
	}
	void imprime() {
		for (unsigned i = 0; i < tamanhoHash; i++) {
			if (tabela[i].primeiro != nullptr) {
				cout << i << ": ";
				tabela[i].imprimir();
				cout << endl;
			}
		}
	}

};

int main() {

	Hash teste(10);
	string nome;
	int id;
	char comando = ' ';

	do {
		try {
			cin >> comando;
			switch (comando) {
			case 'i':
				cin >> nome >> id;
				teste.inserir(nome, id);
				break;
			case 'r': 
				cin >> id;
				teste.remover(id);
				break;
			case 'p':
				teste.imprime();
				break;
			case 'v':
				cin >> id;
				cout << "O nome associado a este id e :" << teste.recuperavalor(id) << endl;
				break;
			case'a':
				cout << "Digite o novo nome que voce deseja e o seu id " << endl;
				cin >> nome >> id;
				teste.alterarvalor(nome, id);
				break;
			case 'f': 
				break;
			default:
				cerr << "comando inválido\n";
			}
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}
	} while (comando != 'f'); // finalizar execução
	return 0;
}
