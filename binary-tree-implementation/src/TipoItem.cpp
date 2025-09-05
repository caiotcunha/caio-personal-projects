#include "TipoItem.hpp"

TipoItem::TipoItem(){
    this->nome = '\0';
    this->dado = '\0';
}

void TipoItem::Imprime(){
    std::cout << this->nome;
}