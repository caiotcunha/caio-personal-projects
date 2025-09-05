#include "functions.h"
#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int Encontra_Maior_Valor(vector< pair<int, int> > grafo[1000],int cidade_origem, int cidade_destino){

    //manter o maior peso (gargalo)
    vector<int> gargalo(1000,INT_MIN);

    //cria um min heap usando fila de prioridades
    priority_queue< pair<int,int>,  vector< pair<int, int> >, greater<pair<int, int>> > fila;

    fila.push(make_pair(0,cidade_origem));

    gargalo[cidade_origem] = INT_MAX;

    //o algoritmo deve rodar enquanto a fila nao está vazia
    while( fila.empty() == false ){

        //pega o elemento do topo da fila
        pair<int,int> aux = fila.top();

        //pega o valor do vertice atual, os pares são (peso,vertice)
        int vertice_atual = aux.second;

        //remove da fila
        fila.pop();

        //percorre todos os vertices adjacentes
        for( auto vertice : grafo[vertice_atual]  ){

            //Encontra o maior peso possível para o vertice
            //usando o vertice atual e o maior peso até agora
            int peso = max(gargalo[vertice.second],min(gargalo[vertice_atual], vertice.first) );

            if( peso > gargalo[vertice.second] ){
                gargalo[vertice.second] = peso;

                //adiciona aresta de volta para possibilitar o funcionamento do algoritmo
                fila.push( make_pair( peso,vertice.second ) );
            }

        }


    }

    return gargalo[cidade_destino];

}