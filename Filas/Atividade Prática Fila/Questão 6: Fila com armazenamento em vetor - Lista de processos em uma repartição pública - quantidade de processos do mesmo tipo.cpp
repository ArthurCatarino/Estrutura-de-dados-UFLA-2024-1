#include <iostream>
#include <stdexcept>
using namespace std;

const int LIMITE = 6;
const int COMECO = -1;

struct processo {

	string nome, processos;
	int n;
	char tipo;

};

void exibir_processo(processo dados) {

	//Nome: processo1 Assunto: Joao Tipo: a Processo: 2

	cout << "Nome: " << dados.nome <<
		" Assunto: " << dados.processos <<
		" Tipo: " << dados.tipo <<
		" Processo: " << dados.n << endl;

}

class fila {

private:

	int inicio, fim, tamanho;
	processo* processos;

public:

	fila() {

		tamanho = 0;
		inicio = COMECO;
		fim = COMECO;
		processos = new processo[LIMITE];

	}

	~fila() { delete[] processos; }

	bool vazia() {

		return tamanho == 0;

	}

	void adicionar(processo info) {

		if (tamanho == LIMITE) throw runtime_error("Erro: fila cheia!");

		if (inicio == -1) {
			inicio++;
		}

		fim = (fim + 1) % LIMITE;
		processos[fim] = info;
		tamanho++;

	}

	processo remover() {

		if (this->vazia()) throw runtime_error("Erro: fila vazia!");

		processo aux = processos[inicio];

		if (inicio == fim) {
			inicio = -1;
			fim = -1;
		}

		else {
			inicio = (inicio + 1) % LIMITE;

		}

		tamanho--;
		return aux;

	}

	void limpa() {

		while (not vazia()) {
			remover();
		}
	}

	void espia() {
		if (this->vazia()) throw runtime_error("Erro: fila vazia!");
		exibir_processo(processos[inicio]);

	}

	void contabiliza(char filtro) {
		if (this->vazia()) throw runtime_error("Erro: fila vazia!");
		
		int cont = 0;
		processo removido;
		fila aux;

		while (not vazia()) {
			removido = remover();

			if (removido.tipo == filtro) {
				cout << "Processo: " << removido.n << endl;
				cont++;
			}
			aux.adicionar(removido);
		}

		while (not aux.vazia()) {
			removido = aux.remover();
			adicionar(removido);
		}

		cout << "Numero de processos: " << cont << endl;
	}
};

int main() {
	fila fila;
	processo info;
	char comando, filtro;
	do {
		try {
			cin >> comando;
			switch (comando) {
			case 'i': // inserir
				cin >> info.nome >> info.processos >> info.tipo >> info.n;
				fila.adicionar(info);
				break;
			case 'r': // remover
				exibir_processo(fila.remover());
				break;
			case 'l': // limpar tudo
				fila.limpa();
				break;
			case 'e': // espiar 
				if (!fila.vazia())
					fila.espia();
				else
					cout << "Erro: fila vazia!" << endl;
				break;
			case 'c':
				cin >> filtro;
				fila.contabiliza(filtro);
				break;
			case 'f': // finalizar
				// checado no do-while
				break;
			default:
				cerr << "comando inválido\n";
			}
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}
	} while (comando != 'f'); // finalizar execução
	while (not fila.vazia()) {
		exibir_processo(fila.remover());
	}
	cout << endl;
	return 0;

}
