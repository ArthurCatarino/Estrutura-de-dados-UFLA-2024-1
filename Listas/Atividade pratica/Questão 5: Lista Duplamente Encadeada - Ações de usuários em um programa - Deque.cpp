/*Nota (0 a 100): 89.5

Status ou Justificativa de Nota: A quantidade de dados escritos pelo programa é diferente da quantidade de dados esperados.*/

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
    void PrimeiraInsercao(acaoPrograma acao);
    acaoPrograma UltimaRemocao();
public:
    listadup();
    ~listadup();
    void insereNaPosicao(int posicao, acaoPrograma acao);
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeNoFim();
    acaoPrograma removeNoInicio();
};

// constrói uma lista inicialmente vazia
listadup::listadup() {
    primeiro = nullptr;
    ultimo = nullptr;
    tamanho = 0;
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup() {
    removeTodos();
}

// remove todos os elementos da lista
void listadup::removeTodos() {
    while (primeiro != nullptr) {
        removeNoInicio();
    }
}

void listadup::PrimeiraInsercao(acaoPrograma acao) {

    noh* novo = new noh(acao);
    primeiro = novo;
    ultimo = novo;
    tamanho++;
}

// insere por no final da lista
void listadup::insereNoFim(acaoPrograma acao) {
    if (vazia()) { PrimeiraInsercao(acao); }
    else {
        noh* novo = new noh(acao);
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
        tamanho++;
    }
}

// insere no início da lista
void listadup::insereNoInicio(acaoPrograma acao) {
    if (vazia()) { PrimeiraInsercao(acao); }
    else {
        noh* novo = new noh(acao);
        primeiro->anterior = novo;
        novo->proximo = primeiro;
        primeiro = novo;
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

    throw runtime_error("Nao encontrado");
}

void listadup::imprime() {
    if (vazia()) { throw runtime_error("Lista vazia!"); }

    noh* aux = primeiro;
    while (aux != nullptr) {
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->proximo;
    }

    cout << "IMPRIMINDO REVERSO" << endl;

    aux = ultimo;

    while(aux != nullptr) {
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->anterior;
    }
}

inline bool listadup::vazia() {
    return primeiro == nullptr;
}

acaoPrograma listadup::UltimaRemocao() {

    noh* aux = primeiro;
    acaoPrograma temp = aux->acao;
    delete aux;

    primeiro = nullptr;
    ultimo = nullptr;
    tamanho--;

    return temp;
}

acaoPrograma listadup::removeNoInicio() {
    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }
    if (tamanho == 1) { acaoPrograma temp = UltimaRemocao(); return temp; }
    else {
        noh* aux = primeiro;
        acaoPrograma temp = aux->acao;

        aux->proximo->anterior = nullptr;
        primeiro = aux->proximo;
        delete aux;

        tamanho--;
        return temp;
    }
}

void listadup::removeNoFim() {
    if (vazia()) { throw runtime_error("Remoção em lista vazia!"); }
    if (tamanho == 1) { UltimaRemocao(); }
    else {
        noh* aux = ultimo;
        aux->anterior->proximo = nullptr;
        ultimo = aux->anterior;
        delete aux;
        tamanho--;
    }
}

void remover(listadup &lista, string filtro) {
    if (lista.vazia()) { throw runtime_error("Remoção em lista vazia!"); }
    
    listadup aux;
    acaoPrograma temp;
    int cont = 0;

    while (!lista.vazia()) {
      temp = lista.removeNoInicio();
      
      if (temp.nomeAcao != filtro) {
           aux.insereNoInicio(temp);
       }
      else {
          cont++;
      }
    }

    if (cont == 0) {
        cout << "Nao encontrado" << endl;
    }

    while (!aux.vazia()) {
        temp = aux.removeNoInicio();
        lista.insereNoInicio(temp);
    }
    

}

void listadup::insereNaPosicao(int posicao, acaoPrograma acao) {
    throw runtime_error("Operação não permitida!");
}

int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe,filtro;

    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoInicio(info);
                break;
            case 'm':
                cin >> posicao >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNaPosicao(posicao,info);
                break;
            case 'h': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoFim(info);
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
            case 'x':
                cin >> filtro;
                remover(minhaLista, filtro);
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
