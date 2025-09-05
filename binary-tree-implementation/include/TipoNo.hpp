#ifndef N0_H
#define NO_H

#include <iostream>
#include "TipoItem.hpp"
#include "FilaEncadeada.hpp"

using namespace std;

class TipoNo
{
    public:
    //construtor
    TipoNo();
    
    string nome;
    TipoNo *esq;
    TipoNo *dir;
    FilaEncadeada *fila;
};




#endif