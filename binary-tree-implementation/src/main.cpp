#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "ArvoreBinaria.hpp"
#include "FilaEncadeada.hpp"

using namespace std;

int main(int agrc, char* argv[]){

    //inteiros auxiliares para o loop de leitura e insercao na arvore
    int contador = 0;
    int NumInseridos = 0;

    //auxiliaries para a insercao na arvore
    TipoItem Consciencia;
    TipoNo *encontrado;

    //Cria a ArvoreBinaria q será preenchida
    ArvoreBinaria Arvore;

    //strings para leitura
    string Linha;
    string Nome;
    string Dado;
    const char delim = ' ';

    //abre o arquivo para leitura
    fstream file(argv[1]);

    //pega a primeira linha e armazena o valor para saber quantas insercoes serao feitas
    getline (file, Linha);
    NumInseridos = stoi(Linha);
    cout<<endl;

    //loop de leitura dos dados que serao inseridos
    while( contador <  NumInseridos ){
        getline (file, Linha);
        stringstream ss(Linha);
        getline(ss, Nome, delim);
        getline(ss, Dado);
        Consciencia.nome = Nome;
        Consciencia.dado = Dado;
        encontrado = Arvore.Procura(Consciencia);
        if( encontrado == nullptr ){
            Arvore.Insere(Consciencia);
        }
        else{
            encontrado->fila->Enfileira(Consciencia.dado);
        }
        contador++;
    }

    //imprime os nomes na arvore
    Arvore.InOrdem(Arvore.raiz);
    cout<<endl;

    //loop de leitura que pega os comandos até o final do arquivo
    while( getline (file, Linha) ){
        stringstream ss(Linha);
        getline(ss, Nome, delim);
        Consciencia.nome = Nome;
        encontrado = Arvore.Procura(Consciencia);
        cout << Nome << " " << encontrado->fila->SomaBinarios() << endl;
        Arvore.Remove(Consciencia);
    }

    //imprime os nomes na arvore depois das remocoes
    Arvore.InOrdem(Arvore.raiz);

    return 0;
}