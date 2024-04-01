#include <iostream>
#include <algorithm>
using namespace std;

class torneio {
private:
	int* heap;
	int tamanho;
	int capacidade;
	int pai(int i);
	int esq(int i);
	int dir(int i);
	void arruma();
	void copiamaior(int i);


public:
	torneio(int vet[], int cap) {
		tamanho = cap;
		int pais = 1;
		while (pais < tamanho) {
			pais *= 2;
		}
		capacidade = pais + cap - 1;
		heap = new int[capacidade];
		
		copy(vet, vet + cap, heap + (capacidade - tamanho));
		arruma();
		cout << heap[0] << endl;
	}

	~torneio() { delete[] heap; }
};



int torneio::pai(int i) {
	return (i - 1) / 2;
}

int torneio::esq(int i) {
	return (i*2)+1;
}

int torneio::dir(int i) {
	return (i*2) + 2;
}

void torneio::arruma() {

	for (int i = capacidade - tamanho - 1; i >= 0; i--) {
		copiamaior(i);
	}

}

void torneio::copiamaior(int i) {
	int e = esq(i);
	int d = dir(i);
	int maior;

	if (e <= capacidade - 1) {
		if ((d <= capacidade - 1) and (heap[d] > heap[e])) {
			maior = d;
		}

		else {
			maior = e;
		}

		heap[i] = heap[maior];
	}
	else {
		heap[i] = -1;
	}
}
int main() {

	int n;
	cin >> n;
	int* vet = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> vet[i];
	}

	torneio teste(vet, n);



	delete[] vet;
	return 0;
}

 
