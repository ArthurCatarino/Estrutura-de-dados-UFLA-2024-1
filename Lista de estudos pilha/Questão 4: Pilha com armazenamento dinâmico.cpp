#include <iostream>
using namespace std;
typedef int Dado;

class Noh {
    friend class Pilha;
private:
    Dado mDado; // poderia ser outro tipo de variável
    Noh* mPtProx;

public:
    Noh(Dado info) { mDado = info; mPtProx = NULL; }
};

class Pilha {
public:
    // Constrói pilha vazia.
    Pilha();
    // Destrutor que desaloca memória.
    ~Pilha();
    // Retira e retorna o valor que estiver no mPtTopo da pilha.
    // Escreve uma mensagem de erro se não for possível desempilhar.
    Dado Desempilhar(); // retorna o mPtTopo da Pilha
    // Insere um valor na pilha.
    void Empilhar(const Dado& d);
    // Apagar todos os dados da pilha.
    void LimparTudo();
    // Informa quantos valores existem na pilha.
    unsigned Tamanho() { return mTamanho; }
    // Retorna o valor que está no mPtTopo sem desempilhar.
    Dado Topo() const;
    // Informa se a pilha está Vazia.
    bool Vazia() const;
private:
    Noh* mPtTopo;
    unsigned mTamanho;
};

using namespace std;

Pilha::Pilha() {
    mPtTopo = NULL;
    mTamanho = 0;
}

Pilha::~Pilha() {
    LimparTudo();
}

Dado Pilha::Desempilhar() {
    if (Vazia())throw runtime_error("Pilha vazia");

     Dado temp = mPtTopo->mDado;
     Noh* aux = new Noh(mPtTopo->mDado);

     aux = mPtTopo;
     mPtTopo = aux->mPtProx;
     delete aux;
     mTamanho--;
     
     return temp;
}

void Pilha::Empilhar(const Dado& d) {

    Noh* novo = new Noh(d);

    novo->mPtProx = mPtTopo;
    mPtTopo = novo;
    mTamanho++;

}

void Pilha::LimparTudo() {
    while (!Vazia()) {
        Desempilhar();
    }
}

Dado Pilha::Topo() const {
    return mPtTopo->mDado;
}

bool Pilha::Vazia() const {
    return mPtTopo == NULL;
}

int main() {
    Pilha pilha;
    Dado valor;
    char comando;
    do {
        try {

            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> valor;
                pilha.Empilhar(valor);
                break;
            case 'r': // remover
                cout << pilha.Desempilhar() << endl;
                break;
            case 'l': // limpar tudo
                pilha.LimparTudo();
                break;
            case 't': // consultar tamanho
                cout << pilha.Tamanho() << endl;
                break;
            case 'e': // espiar
                cout << pilha.Topo() << endl;
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
    while (not pilha.Vazia()) {
        cout << pilha.Desempilhar() << ' ';
    }
    cout << endl;
    return 0;
}
