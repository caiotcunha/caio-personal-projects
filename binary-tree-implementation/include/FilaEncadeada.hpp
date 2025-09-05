#ifndef FILA_H
#define FILA_H

#include "TipoCelula.hpp"

class FilaEncadeada{
    public:
    //construtor
    FilaEncadeada();
    //acrescenta uma string ao final da fila
    void Enfileira(string dado);
    //imprime a fila encadeada
    void Imprime();
    //apaga os dados armazenados na fila encadeada
    void Limpa();
    //soma os dados binarios armazenados nas strings da fila encadeada
    int SomaBinarios();
    
    int tamanho;
    TipoCelula* head;
    TipoCelula* tail;

};

#endif