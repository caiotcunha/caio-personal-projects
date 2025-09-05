#ifndef CELULA_H
#define CELULA_H

#include <iostream>
#include <string>

using namespace std;

class TipoCelula
{
    public:
        //construtor
        TipoCelula();
        
        string dado;
        TipoCelula *prox;
};




#endif