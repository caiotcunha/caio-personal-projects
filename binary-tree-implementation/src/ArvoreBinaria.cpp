#include "ArvoreBinaria.hpp"


ArvoreBinaria::ArvoreBinaria(){
    this->raiz = nullptr;
}

void ArvoreBinaria::Insere( TipoItem item ){
    this->InsereRecursivo( this->raiz,item );
}

void ArvoreBinaria::InsereRecursivo( TipoNo* &p ,TipoItem item ){
    if( p == nullptr ){
        p = new TipoNo();
        p->nome = item.nome;
        p->fila->Enfileira(item.dado);
    }
    else{
        if( item.nome.compare( p->nome ) < 0 ){
            InsereRecursivo( p->esq, item );
        }
        else{
            InsereRecursivo( p->dir, item );
        }
    }
}

void ArvoreBinaria::InOrdem( TipoNo *p ){
    if( p != nullptr ){
        InOrdem( p->esq );
        cout << p->nome << " ";
        InOrdem( p-> dir );
    }
}

TipoNo * ArvoreBinaria::Procura( TipoItem item ){
    return ProcuraRecursivo( this->raiz, item );
}

TipoNo * ArvoreBinaria::ProcuraRecursivo( TipoNo* &p, TipoItem item ){
    TipoNo* aux = nullptr;
    if( p == nullptr ){
        return aux;
    }
    if( item.nome.compare( p->nome ) == 0 ){
        return p;
    }
    else{
        if( item.nome.compare( p->nome ) < 0 ){
            return ProcuraRecursivo( p->esq, item );
        }
        else{
            return ProcuraRecursivo( p->dir, item );
        }
    }
}

void ArvoreBinaria::Remove( TipoItem item ){
   return RemoveRecursivo(this->raiz,item);
}

void ArvoreBinaria::RemoveRecursivo( TipoNo* &no, TipoItem item ){
    TipoNo *aux;
    if ( no == NULL ){
        cout << "item nao esta presente";
    }
    if( item.nome.compare( no->nome ) < 0 ){
        RemoveRecursivo( no->esq, item );
    }
    else if( item.nome.compare( no->nome ) > 0 ) {
        RemoveRecursivo( no->dir, item );
    }
    else{
        if( no->dir == NULL ){
            aux = no;
            no = no->esq;
            delete aux;
        }
        else if( no->esq == NULL ){
            aux = no;
            no = no->dir;
            delete aux;
        }
        else{
            Antecessor(no, no->esq);
        }

    }

}

void ArvoreBinaria::Antecessor( TipoNo *q, TipoNo* &r ){
    if( r->dir != NULL ){
        Antecessor(q,r->dir);
        return;
    }
    
    q->nome = r->nome;
    q->fila->Limpa();
    q->fila = r->fila;
    q = r;
    r = r->esq;
    delete q;
}


