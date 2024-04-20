#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};
//Nome: oito Tipo: h Valor: 8
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " Tipo: "
        << umDado.tipo << " Valor: " << umDado.valor << endl;
}

class Noh {
    friend class Pilha;
private:
    Dado mDado; // poderia ser outro tipo de variável
    Noh* mProx;
public:
    Noh(Dado v) {
        mDado = v;
        mProx = NULL;
    }
};

class Pilha {
public:
    // Constrói pilha vazia.
    Pilha();
    // Destrutor que desaloca memória.
    ~Pilha();
    // Retira e retorna o valor que estiver no mPtTopo da pilha.
    // Escreve uma mensagem de erro se não for possível desempilhar.
    Dado Desempilhar(); // retorna o mPtTopo da Pilha.
    // Insere um valor na pilha.
    void Empilhar(const Dado& d);
    // Apagar todos os dados da pilha.
    void LimparTudo();
    // Imprime o valor que está no mPtTopo sem desempilhar.
    inline void Topo();
    // Informa se a pilha está Vazia.
    inline bool Vazia();
    //Filtra os elementos de uma pilha.
    void peneira(int filtro);
private:
    Noh* mPtTopo;
};

Pilha::Pilha() { mPtTopo = NULL; }

Pilha::~Pilha() {}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    
    Dado temp = mPtTopo->mDado;
    Noh* aux = new Noh(mPtTopo->mDado);

    aux = mPtTopo;
    mPtTopo = aux->mProx;
    delete aux;
    
    return temp;
}

void Pilha::Empilhar(const Dado& d) {

    Noh* novo = new Noh(d);

    novo->mProx = mPtTopo;
    mPtTopo = novo;

}

void Pilha::LimparTudo() {
    while (not Vazia()) {
        Desempilhar();
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");

    Dado imprimir = mPtTopo->mDado;
    imprimir_dado(imprimir);

}

bool Pilha::Vazia() {

    return mPtTopo == NULL;

}

void Pilha::peneira(int filtro) {
if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    Pilha aux;
    Dado removido;

    while (not Vazia()) {
        removido = Desempilhar();

        if (removido.valor <= filtro) {
            aux.Empilhar(removido);
        }
        else {
            imprimir_dado(removido);
        }
    }

    while (not aux.Vazia()) {
        removido = aux.Desempilhar();
        Empilhar(removido);
    }


}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    int filtro;
    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> info.nome >> info.tipo >> info.valor;
                pilha.Empilhar(info);
                break;
            case 'r': // remover
                imprimir_dado(pilha.Desempilhar());
                break;
            case 'l': // limpar tudo
                pilha.LimparTudo();
                break;
            case 'e': // espiar                
                pilha.Topo();
                break;
            case 'x':
                cin >> filtro;
                pilha.peneira(filtro);
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
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}
