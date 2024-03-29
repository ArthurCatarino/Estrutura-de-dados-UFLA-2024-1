#include <iostream> 
using namespace std;

struct tarefas {
	string nome,premio;
	int n;
	char tipo;
};

void exibir_tarefa(tarefas dados) {

	//Nome: destruirArmazen Premio : jaqueta Tipo : f tempo : 100

	cout << "Nome: " << dados.nome << " Premio: "
		<< dados.premio << " Tipo: " << dados.tipo << " tempo: " << dados.n << endl;

}

class no {
	friend class fila;
private:
	no* proximo;
	tarefas dado;

public:
	no(tarefas info) { dado = info; proximo = nullptr; }
	~no() {}
};

class fila {

private:
	no* fim;
	no* inicio;

public:
	fila() { fim = nullptr; inicio = nullptr; }
	~fila() { limpar(); }

	bool vazia() {

		return inicio == nullptr;
	}

	void adicionar(tarefas info) {

		no* novo = new no(info);

		if (vazia()) {
			inicio = novo;
			fim = novo;
		}

		else {
			fim->proximo = novo;
			fim = novo;
		}

	}

	tarefas remover() {
		if (this->vazia()) throw runtime_error("Erro: Fila vazia!");

		tarefas removido = inicio->dado;

		no* aux = inicio;
		inicio = inicio->proximo;
		delete aux;

		if (vazia()) {
			fim = nullptr;
		}

		return removido;
	}

	void limpar() {

		while (not vazia()) {
			remover();

		}

	}

	void espiar() {
		if (this->vazia()) throw runtime_error("Erro: Fila vazia!");
		exibir_tarefa(inicio->dado);
	}

	void tempo(char filtro) {
		if (this->vazia()) throw runtime_error("Erro: Fila vazia!");

		fila aux, resul;
		tarefas removido;
		int soma = 0;

		while (not vazia()) {
			removido = remover();
			
			if (removido.tipo == filtro) {
				soma += removido.n;
				resul.adicionar(removido);
			}
			
			else {
				aux.adicionar(removido);
			}
		}

		cout << soma << endl;

		while (not resul.vazia()) {
			removido = resul.remover();
			adicionar(removido);
		}

		while (not aux.vazia()) {
			removido = aux.remover();
			adicionar(removido);
		}


	}

};

int main() {
	fila fila;
	tarefas info;
	char comando;
	char filtro;
	do {
		try {
			cin >> comando;
			switch (comando) {
			case 'i': // inserir
				cin >> info.nome >> info.premio >> info.tipo >> info.n;
				fila.adicionar(info);
				break;
			case 'r': // remover
				exibir_tarefa(fila.remover());
				break;
			case 'l': // limpar tudo
				fila.limpar();
				break;
			case 'e': // espiar                
				fila.espiar();
				break;
			case 'a':
				cin >> filtro;
				fila.tempo(filtro);
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
		exibir_tarefa(fila.remover());
	}
	cout << endl;
	return 0;
}
