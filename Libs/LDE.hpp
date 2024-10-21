#include <iostream>
using namespace std;

template <class T>
struct No{
    T info;
    No <T> *eloA = nullptr;
    No <T> *eloP = nullptr;
};

template <class T>
struct LDE{
    No <T> *comeco = nullptr;
    No <T> *fim = nullptr;
};

// Opera��es da LDE
template <class T>
void inicializarLDE( LDE <T> &lista ){
    lista.comeco = nullptr;
    lista.fim = nullptr;
}

template <class T>
bool inserirFinalLDE( LDE <T> &lista, T valor ){
    No <T> *novo = new No <T>;

    if( novo == nullptr ) return false;
    novo->info = valor;
    novo->eloA = nullptr;
    novo->eloP = nullptr;

    if( lista.comeco == nullptr ){ // Caso 1 - lista vazia
        lista.comeco = novo;
        lista.fim = novo;
    }
    else{   // Caso 2 - Inserir no final
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    }
    return true;
}

template <class T>
bool inserirLDE(LDE <T> &lista, T valor){
    No <T> *novo = new No <T>;

    if( novo == nullptr ) return false;
    novo->info = valor;
    novo->eloA = nullptr;
    novo->eloP = nullptr;

    if( lista.comeco == nullptr ){ // Caso A
        lista.comeco = novo;
        lista.fim = novo;
    }
    else if( valor <= lista.comeco->info ){ // Caso B
        novo->eloP = lista.comeco;
        lista.comeco->eloA = novo;
        lista.comeco = novo;
    }
    else if( valor > lista.fim->info ){ // Caso C
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    }
    else{ // Caso D
        No <T> *aux = lista.comeco;
        while( aux != nullptr ){
            No <T> *prox = aux->eloP;
            if( aux->info <= valor && valor < prox->info ){
                aux->eloP = novo;
                prox->eloA = novo;
                novo->eloA = aux;
                novo->eloP = prox;
                break;
            }
            aux = aux->eloP;
        }
    }
    return true;
}

template <class T>
bool retirarLDE( LDE <T> &lista, T valor ){
    if( lista.comeco == nullptr ) return false;
    No <T> *aux, *ant, *prox;

    if( valor == lista.comeco->info ){
        aux = lista.comeco;
        if( valor == lista.fim->info ){ // Caso a
            lista.comeco = nullptr;
            lista.fim = nullptr;
        }
        else{ // Caso b
            lista.comeco = aux->eloP;
            lista.comeco->eloA = nullptr;
        }
    }
    else{
        if( valor == lista.fim->info ){ // Caso c
            aux = lista.fim;
            lista.fim = aux->eloA;
            lista.fim->eloP = nullptr;
        }
        else{ // Caso d
            aux = lista.comeco;
            while( aux != nullptr ){
                if( aux->info == valor ){
                    ant = aux->eloA;
                    prox = aux->eloP;
                    ant->eloP = prox;
                    prox->eloA = ant;
                    break;
                }
                aux = aux->eloP;
            }
            if( aux == nullptr ) return false;
        }
    }

    delete aux;
    return true;
}

template <class T>
void mostrarLDE(LDE <T> lista, char ordem){
    if( ordem == 'C' || ordem == 'c' ){
        No <T> *aux = lista.comeco;
        while( aux != nullptr ){
            cout << aux->info << " ";
            aux = aux->eloP; // Avan�a para o pr�ximo no
        }
    } else {
        No <T> *aux = lista.fim;
        while( aux != nullptr ){
            cout << aux->info << " ";
            aux = aux->eloA; // Avan�a para o no anterior
        }
    }
}

template <class T>
void liberarLDE(LDE <T> &lista){
    No <T> *temp, *aux = lista.comeco;
    while( aux != nullptr ){
        temp = aux;
        aux = aux->eloP;
        delete temp;
    }
    lista.comeco = lista.fim = nullptr;
}

// Retornar true se o valor for encontrado ou false se n�o estiver na lista
// **********
template <class T>
bool pesquisarLDE(LDE <T> lista, T valor){
    No <T> *aux = lista.comeco;
    while( aux != nullptr ){
        if( aux->info == valor ) return true;
        aux = aux->eloP;
    }
    return false;
}