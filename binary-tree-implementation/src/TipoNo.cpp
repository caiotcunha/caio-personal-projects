#include "TipoNo.hpp"

TipoNo::TipoNo(){
    this->nome = '\0';
    this->esq = nullptr;
    this->dir = nullptr;
    this->fila = new FilaEncadeada;
}