#include "FilaEncadeada.hpp"
#include <cmath>

FilaEncadeada::FilaEncadeada(){
    this->tamanho = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

void FilaEncadeada::Enfileira( string dado ){
    if( this->head == nullptr ){
        TipoCelula *nova;
        nova = new TipoCelula();
        nova->dado = dado;
        nova->prox = nullptr;
        this->head = nova;
        this->tail = nova;
        this->tamanho++;
    }
    else{
        TipoCelula *nova;
        nova = new TipoCelula();
        nova->dado = dado;
        this->tail->prox = nova;
        this->tail = nova;
        this->tamanho++;
    }
}

void FilaEncadeada::Imprime(){
    TipoCelula *p;
    p = this->head;
    if( this->tamanho != 0 ){
        while( p != nullptr ){
        cout << p->dado;
        cout << endl;
        p = p->prox;
        }
    }
    else{
        cout << "lista vazia!";
    }
    
}

void FilaEncadeada::Limpa(){
    TipoCelula *p;
    TipoCelula *aux;
    p = this->head;
    aux = this->head->prox;
    while( p->prox != nullptr ){
        delete p;
        p = aux;
        aux = aux->prox;
    }
    delete p;
    this->tamanho = 0;
    this->tail = nullptr;
    this->head = nullptr;
}

int FilaEncadeada::SomaBinarios(){
    TipoCelula *p;
    p = this->head;
    int posicao = 0;
    int soma = 0;
    int TamanhoString = 0;
    float potencia = 0;
    while( p != nullptr ){
        TamanhoString = p->dado.length();
        posicao = (TamanhoString - 1);
        potencia = 0;
        while( posicao >= 0 ){
            soma = soma + ((p->dado[posicao] - '0')*pow(2.0,potencia));
            posicao--;
            potencia++;
        }
        p = p->prox;
    }
    return soma;
}