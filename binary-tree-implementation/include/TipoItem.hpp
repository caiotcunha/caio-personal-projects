#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using namespace std;

class TipoItem
{
    public:
    //construtor
    TipoItem();
    //imprime a string nome e a string dado armazenados no tipo item
    void Imprime();
    
    string nome;
    string dado;
};




#endif