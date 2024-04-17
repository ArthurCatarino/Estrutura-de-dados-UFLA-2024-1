/* 
 * Classe lista, uma lista dinamicamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe{
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

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void Primeirainsercao(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
lista::lista() {
	ultimo = nullptr;
	primeiro = nullptr;
	tamanho = 0;
}

// construtor de cópia
lista::lista(const lista& umaLista) {

}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) { removeTodos();

}    

// remove todos os elementos da lista
void lista::removeTodos( ) {
	
	while(primeiro != nullptr) {
		removeNoFim();
		}
}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

void lista::Primeirainsercao(equipe elenco) {
	
	noh* novo = new noh(elenco);
	ultimo = novo;
	primeiro = novo;
	tamanho++;
	
}
	

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
	
	if(tamanho == 0) {Primeirainsercao(elenco);}
	else {
	
		noh* novo = new noh(elenco);
		novo = ultimo->proximo;
		ultimo = novo;
		tamanho++;
	}
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
	
	if(tamanho == 0) {Primeirainsercao(elenco);}
	else {
		noh* novo = new noh(elenco);
		novo = primeiro->proximo;
		primeiro = novo;
		tamanho++;
	}
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){

	if(tamanho == 0) {Primeirainsercao(elenco);}
	else if (posicao == tamanho) {insereNoFim(elenco);}
	else if (posicao == 0) {insereNoInicio(elenco);}
	else {
		
		noh* novo = new noh(elenco);
		noh* aux = primeiro;
		int posaux = 0;
		
		for(posaux = 0; posaux < posicao -1; posaux++) {
			aux = aux->proximo;
		}
		
		novo->proximo = aux->proximo;
		aux->proximo = novo;
		tamanho++;
		}
}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
    
    noh* aux = primeiro;
    int cont = 0;
    
    while(aux->elenco.lider != valor or aux == nullptr) {
		aux = aux->proximo;
		cont++;
	}
		
	if(aux != nullptr) 
	return cont;
	else
	throw runtime_error("Nao encontrado");

}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }
    
     //cout << "(" << removido.nomeEquipe << ", " << removido.lider << ", " << removido.linguagem << ", " removido.qtdMembros << ")" << endl;
     
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == nullptr);
}
   
void lista::removeNoFim() {
	
	if(vazia()) {throw runtime_error("Remoção em lista vazia!");}
	
	noh* aux = primeiro;
	noh* temp;
	
	for(int i = 0; i < tamanho-1;i++){
		aux = aux->proximo;
	}
	
	temp = aux->proximo;
	aux = ultimo->proximo;
	ultimo = aux;
	delete temp;
	tamanho--;
	
	if(tamanho == 0) {
		primeiro = nullptr;
		ultimo = nullptr;
	}
}
    
void lista::removeNoInicio() {
	if(vazia()) {throw runtime_error("Remoção em lista vazia!");}
	
	noh* temp = primeiro;
	
	primeiro = temp->proximo;
	delete temp;
	
	if(tamanho == 0) {
		primeiro = nullptr;
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
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // remover
                    cin >> nomeEquipe;
                    cout << minhaLista.procura(nomeEquipe) <<endl;
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
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
