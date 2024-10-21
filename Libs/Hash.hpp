/* Strut hash genérica */

#include "LDE.hpp"

#define TAM 10

template<class T>
struct Hash
{
    LDE<T> tabela[TAM];
};


int hashing(string nome){
    int N = 0;

    for(int i = 0; i < nome.length(); i++)
        N += int(nome[i]);

    return N%TAM;
}