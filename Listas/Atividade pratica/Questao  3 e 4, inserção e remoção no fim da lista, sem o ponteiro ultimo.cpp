/*Nota (0 a 100): 77.5

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
    void removeTodos();
    void Primeirainsercao(equipe elenco);
    void ultimaremocao();
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
    void removeEspecifico(string removido);
    int tamanhodalista();
};

lista::lista() {
    primeiro = nullptr;
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
    primeiro = novo;

}

void lista::insereNoFim(equipe elenco) {

    if (vazia()){ Primeirainsercao(elenco); }
    else {

        noh* novo = new noh(elenco);
        noh* aux = primeiro;

        for (int i = 0; i < tamanhodalista() - 1; i++) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
}

void lista::insereNoInicio(equipe elenco) {

    if (vazia()) { Primeirainsercao(elenco); }
    else {
        noh* novo = new noh(elenco);
        novo->proximo = primeiro;
        primeiro = novo;
    }
}

void lista::insereNaPosicao(int posicao, equipe elenco) {

    if (posicao == tamanhodalista()) { insereNoFim(elenco); }
    else if (posicao == 0) { insereNoInicio(elenco); }
    else if (posicao > tamanhodalista()) { throw runtime_error("Posição Inexistente!"); }
    else {

        noh* novo = new noh(elenco);
        noh* aux = primeiro;
        int posaux = 0;

        for (posaux = 0; posaux < posicao - 1; posaux++) {
            aux = aux->proximo;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
}

int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;
    int cont = 0;

    while (aux != nullptr) {

        if (aux->elenco.nomeEquipe == valor) {
            return cont;
        }

        aux = aux->proximo;
        cont++;
    }

    throw runtime_error("Nao encontrado");

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

void lista::ultimaremocao() {

    noh* aux = primeiro;
    primeiro = nullptr;
    delete aux;
}

void lista::removeNoFim() {

    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }
    else if (tamanhodalista() == 1) { ultimaremocao(); }
    else {
        noh* aux = primeiro;
        noh* temp = aux;

        for (int i = 0; i < tamanhodalista() - 1; i++) {
            temp = aux;
            aux = aux->proximo;
        }
        delete aux;
        temp->proximo = nullptr;
    }
}

void lista::removeNoInicio() {
    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }
    if (tamanhodalista() == 1) { ultimaremocao(); }
    else {

        noh* temp = primeiro;

        primeiro = temp->proximo;
        delete temp;

    }
}

void lista::removeEspecifico(string removido) {
    if (vazia()) { throw runtime_error("Lista vazia!"); }

    noh* AnteriorAux = nullptr;
    noh* aux = primeiro;
    int cont = 1;

    while (aux != nullptr) {

        if (aux->elenco.nomeEquipe == removido) {
            if (cont == 1) { removeNoInicio(); }
            else if (cont == tamanhodalista()) { removeNoFim(); }
            else {
                AnteriorAux->proximo = aux->proximo;
                delete aux;
            }
            aux = nullptr;
        }
        else {
            AnteriorAux = aux;
            aux = aux->proximo;
            cont++;
        }
    }
}

int lista::tamanhodalista() {

    if (primeiro == nullptr) { return 0; }

    int cont = 0;

    for (noh* aux = primeiro; aux != nullptr; aux = aux->proximo) {
        cont++;
    }
    return cont;

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
            case 't':
                cout << minhaLista.tamanhodalista() << endl;
                break;
            case 'x':
                cin >> nomeEquipe;
                minhaLista.removeEspecifico(nomeEquipe);
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
