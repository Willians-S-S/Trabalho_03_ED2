#include <stdio.h>
#include <stdlib.h>
#include "gra.h"
#include "valoresVertices.h"

#define TAM 81

int main(){
    Graph *G;

    G = iniciaGrafo(TAM);

    
    inserirArestas(G);
    inserirValoresVertices(G);
    //
    // for(int i = 0; i < TAM; i++)
    //     imprimirConteudoVertice(G, i);

    // imprimirGrafo(G, TAM);
    dijkstra(G->arestas, TAM, 0, 65);
    return 0;
}