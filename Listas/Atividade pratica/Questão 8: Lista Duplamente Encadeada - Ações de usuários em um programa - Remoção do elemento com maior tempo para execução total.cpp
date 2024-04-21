/*

Nota (0 a 100): 90

Status ou Justificativa de Nota: A quantidade de dados escritos pelo programa é diferente da quantidade de dados esperados.


 * Classe listadup, uma lista dinamicamente duplamente encadeada
 *
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma {
    int identificador;
    string nomeAcao;
    int tempoExecucao;
    int tempoConsumido;
};


class noh {
    friend class listadup;
private:
    acaoPrograma acao; // poderia ser outro tipo de variável
    noh* proximo;
    noh* anterior;
public:
    //noh();
    noh(acaoPrograma d);
};

// construindo dado chamando seu construtor
noh::noh(acaoPrograma d) {
    acao = d;
    proximo = NULL;
    anterior = NULL;
}


// lista dinamicamente encadeada
class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista    
public:
    listadup();
    ~listadup();
    // inserção, remoção e procura
    void primeirainsercao(acaoPrograma acao);
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeultimoelemento();
    void removeNoFim();
    void removeNoInicio();
    void removeMaiorTempo();
};


// constrói uma lista inicialmente vazia
listadup::listadup() {
    primeiro = nullptr;
    ultimo = nullptr;
    tamanho = 0;
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup() { removeTodos(); }

// remove todos os elementos da lista
void listadup::removeTodos() {
    while (primeiro->proximo != nullptr) {
        removeNoInicio();
    }

}

void listadup::primeirainsercao(acaoPrograma acao) {

    noh* novo = new noh(acao);
    primeiro = novo;
    ultimo = novo;
    tamanho++;
}

// insere por no final da lista
void listadup::insereNoFim(acaoPrograma acao) {

    if (vazia()) { primeirainsercao(acao); }

    else {
        noh* novo = new noh(acao);
        novo->anterior = ultimo;
        ultimo->proximo = novo;
        ultimo = novo;
        tamanho++;
    }
}

// insere no início da lista
void listadup::insereNoInicio(acaoPrograma acao) {

    if (tamanho == 0) { primeirainsercao(acao); }
    else {
        noh* novo = new noh(acao);
        primeiro->anterior = novo;
        novo->proximo = primeiro;
        primeiro = novo;
        tamanho++;
    }
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, acaoPrograma acao) {

    if (tamanho == 0) { primeirainsercao(acao); }
    else if (posicao == tamanho) { insereNoFim(acao); }
    else if (posicao == 0) { insereNoInicio(acao); }
    else {
        if (posicao > tamanho) { throw runtime_error("Posição Inexistente!"); }

        noh* novo = new noh(acao);
        noh* aux = primeiro;

        for (int i = 0; i < posicao - 1; i++) {
            aux = aux->proximo;
        }

        novo->proximo = aux->proximo;
        novo->anterior = aux;
        aux->proximo = novo;
        aux = novo->proximo;
        aux->anterior = novo;

        tamanho++;
    }
}

int listadup::procura(string valor) {
    if (vazia()) { throw runtime_error("Lista vazia!"); }

    noh* aux = primeiro;
    int cont = 0;

    while (aux != nullptr) {

        if (aux->acao.nomeAcao == valor) {
            return cont;
        }

        aux = aux->proximo;
        cont++;
    }

    return -1;

}

// método básico que *percorre* uma lista, imprimindo seus elementos
void listadup::imprime() {
    if (vazia()) { throw runtime_error("Lista vazia!"); }

    noh* aux = primeiro;
    while (aux != nullptr) {
        //(Identificador, NomeAcao, TempoExecução, TempoConsumido) -- (2, semaforoProc, 32, 11)      
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->proximo;
    }
    cout << "IMPRIMINDO REVERSO" << endl;

    aux = ultimo;
    while (aux != nullptr) {
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->anterior;
    }


}

// verifica se a lista está vazia
inline bool listadup::vazia() {

    return primeiro == nullptr;
}

void listadup::removeNoInicio() {

    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }
    else if (tamanho == 1) { removeultimoelemento(); }
    else {

        noh* temp = primeiro;

        temp->proximo->anterior = nullptr;
        primeiro = temp->proximo;

        delete temp;
        tamanho--;
    }
}

void listadup::removeultimoelemento() {

    noh* aux = primeiro;
    aux->acao.tempoExecucao = 1; // Completamente inutil, do pq o geany e burro e daria erro
    delete primeiro;

    ultimo = nullptr;
    primeiro = nullptr;
    tamanho--;

}

void listadup::removeNoFim() {
    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }
    else if (tamanho == 1) { removeultimoelemento(); }
    else {
        noh* aux = ultimo;

        aux->anterior->proximo = nullptr;
        ultimo = aux->anterior;
        delete aux;
        tamanho--;
    }

}

void listadup::removeMaiorTempo() {
    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }

    noh* aux = primeiro;

    int maior = -1;
    int cont = -1;
    int indice;

    while (aux != nullptr) {
        if (aux->acao.tempoExecucao > maior) {
            maior = aux->acao.tempoExecucao;
            indice = cont + 1;
        }
        aux = aux->proximo;
        cont++;
    }

    aux = primeiro;

    for (int i = 0; i < indice; i++) {
        aux = aux->proximo;
    }

    acaoPrograma temp = aux->acao;
    if (tamanho == 1) { removeultimoelemento(); }
    else if (indice == tamanho - 1) { removeNoFim(); }
    else if (indice == 0) { removeNoInicio(); }
    else {

        aux->proximo->anterior = aux->anterior;
        aux->anterior->proximo = aux->proximo;
        delete aux;
    }

    cout << "(" << temp.identificador << ", " << temp.nomeAcao << ", " << temp.tempoExecucao << ", " << temp.tempoConsumido << ")" << endl;
}

int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoInicio(info);
                break;
            case 'h': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoFim(info);
                break;
            case 'm': // inserir
                cin >> posicao;
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNaPosicao(posicao, info);
                break;
            case 's': // procurar
                cin >> nomeEquipe;
                posicao = minhaLista.procura(nomeEquipe);
                if (posicao == -1)
                    cout << "Nao encontrado" << endl;
                else
                    cout << posicao << endl;
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
                minhaLista.removeMaiorTempo();
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
