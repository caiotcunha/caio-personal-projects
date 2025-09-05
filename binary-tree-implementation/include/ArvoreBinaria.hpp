#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>

#include "TipoNo.hpp"

using namespace std;

class ArvoreBinaria
{
    public:
    //construtor
    ArvoreBinaria();
    //chama insere recursivo
    void Insere( TipoItem item );
    //insere um TipoItem na arvore através do método recursivo
    void InsereRecursivo( TipoNo* &p ,TipoItem item );
    //imprime a arvore em ordem central
    void InOrdem( TipoNo *p );
    //chama procura recursivo
    TipoNo* Procura( TipoItem item );
    //procura um no na arvore recursivamente
    TipoNo* ProcuraRecursivo( TipoNo* &p, TipoItem item );
    //chama remove recusivo
    void Remove( TipoItem item );
    //remove um nó da arvore usando método recursivo
    void RemoveRecursivo(TipoNo* &no,TipoItem item);
    //procura o antecessor de um nó na arvore e substitui
    void Antecessor(TipoNo *q, TipoNo* &r);
    
    TipoNo *raiz;
};




#endif