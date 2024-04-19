/*Nota (0 a 100): 64.5

Status ou Justificativa de Nota: A quantidade de dados escritos pelo programa é diferente da quantidade de dados esperados.*/


#include <iostream>
#include <cstdlib>

using namespace std;

struct equipe {
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

class noh {
    friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

noh::noh(equipe d) {
    elenco = d;
    proximo = NULL;
}

class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); 
    void Primeirainsercao(equipe elenco);
public:
    lista();
    ~lista();
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor);
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

lista::lista() {
    ultimo = nullptr;
    primeiro = nullptr;
    tamanho = 0;
}

lista::~lista() {
    removeTodos();

}

void lista::removeTodos() {

    while (primeiro != nullptr) {
        removeNoInicio();
    }
}

void lista::Primeirainsercao(equipe elenco) {

    noh* novo = new noh(elenco);
    ultimo = novo;
    primeiro = novo;
    tamanho++;

}

void lista::insereNoFim(equipe elenco) {

    if (tamanho == 0) { Primeirainsercao(elenco); }
    else {

        noh* novo = new noh(elenco);
        ultimo->proximo = novo;
        ultimo = novo;
        tamanho++;
    }
}

void lista::insereNoInicio(equipe elenco) {

    if (tamanho == 0) { Primeirainsercao(elenco); }
    else {
        noh* novo = new noh(elenco);
        novo->proximo = primeiro;
        primeiro = novo;
        tamanho++;
    }
}

void lista::insereNaPosicao(int posicao, equipe elenco) {

    if (tamanho == 0) { Primeirainsercao(elenco); }
    else if (posicao == tamanho) { insereNoFim(elenco); }
    else if (posicao == 0) { insereNoInicio(elenco); }
    else {

        noh* novo = new noh(elenco);
        noh* aux = primeiro;
        int posaux = 0;

        for (posaux = 0; posaux < posicao - 1; posaux++) {
            aux = aux->proximo;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;
        tamanho++;
    }
}

int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;
    int cont = 0;

    while (aux != nullptr ) {

        if (aux->elenco.lider == valor) {
            return cont;
        }

        aux = aux->proximo;
        cont++;
    }

    if (aux != nullptr) {
        return cont;
    }

    else {
        throw runtime_error("Nao encontrado");
    }
}

void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;

    while (aux != nullptr) {
        cout << "(" << aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", " << aux->elenco.linguagem << ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }

    //cout << "(" << removido.nomeEquipe << ", " << removido.lider << ", " << removido.linguagem << ", " removido.qtdMembros << ")" << endl;

}

inline bool lista::vazia() {
    return (primeiro == nullptr);
}

void lista::removeNoFim() {

    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }

    noh* aux = primeiro;
    noh* temp = nullptr;

    for (int i = 0; i < tamanho- 1; i++) {
        temp = aux;
        aux = aux->proximo;
        
    }

    delete aux;
    temp->proximo = nullptr;
    ultimo = temp;
    tamanho--;

    if (vazia()) {
        primeiro = nullptr;
    }
}

void lista::removeNoInicio() {
    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }

    noh* temp = primeiro;

    primeiro = temp->proximo;
    delete temp;
    tamanho--;

    if (vazia()) {
        ultimo = nullptr;
    }
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoInicio(info);
                break;
            case 'h': // inserir
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoFim(info);
                break;
            case 'm': // inserir
                cin >> posicao;
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNaPosicao(posicao, info);
                break;
            case 's': // remover
                cin >> nomeEquipe;
                cout << minhaLista.procura(nomeEquipe) << endl;
                break;
            case 'r': // remover
                minhaLista.removeNoInicio();
                break;
            case 'a': // remover
                minhaLista.removeNoFim();
                break;
            case 'p': // limpar tudo
                minhaLista.imprime();
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
    cout << endl;
    return 0;
}
