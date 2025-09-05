#include "functions.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<pair<int, int>> grafo[1000];

    int num_cidades,num_rodovias,num_consultas = 0;
    int cidade_origem, cidade_destino = 0;
    int u,v,w = 0;

    cin >> num_cidades;
    cin >> num_rodovias;
    cin >> num_consultas;

    for( int i = 0; i < num_rodovias; i ++ ){
        //descreve rodovia (preenche o grafo)
        cin >> u;
        cin >> v;
        cin >> w;
        grafo[u].push_back(make_pair(w, v));
    }

    for( int i = 0; i < num_consultas; i ++ ){
        cin >> cidade_origem;
        cin >> cidade_destino;
        //encontra maior carregamento possível de origem ate destino
        cout << Encontra_Maior_Valor(grafo,cidade_origem,cidade_destino) << endl;
    }

    return 0;

}