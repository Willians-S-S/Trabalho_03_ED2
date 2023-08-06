#include <stdio.h>
#include <stdlib.h>
#include "gra.h"
#include "valoresVertices.h"

#define TAM 81
#define INF 999999


Graph *iniciaGrafo(int n){
    Graph *G;

    G = (Graph *) malloc(sizeof(Graph));
    
    G->vertices = (Vertice *) malloc(n * sizeof(Vertice));
    G->arestas = (int **) malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++){
        G->arestas[i] = (int *) calloc(n, sizeof(int));
    }

    return G;
}

void imprimirGrafo(Graph *G, int n){
    printf("Vertices: \n"
    "  "
    );
    // n = 19;
    for(int i = 0; i < n; i++){
        printf(" %d", i);
    }
    printf("\n\n");
    for(int i = 0; i < n; i++){
        printf("%d  ", i);
        for(int j = 0; j < n; j++){
            printf("%d ", G->arestas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void inserirArestas(Graph *G){
    FILE *arestas; arestas = fopen("arestas.txt", "r");
    int verticeAtual = 0, aresta1, aresta2, aresta3;

    while (fscanf(arestas, "%d %d %d %d", &verticeAtual, &aresta1, &aresta2, &aresta3) != EOF){
        G->arestas[verticeAtual][aresta1] = 1;
        G->arestas[verticeAtual][aresta2] = 1;
        G->arestas[verticeAtual][aresta3] = 1;    
    }
}

void imprimirConteudoVertice(Graph *G, int linha){
    printf("Vertice %d: %d %d %d %d\n", linha, G->vertices[linha].discos[0], G->vertices[linha].discos[1], G->vertices[linha].discos[2], G->vertices[linha].discos[3]);
}

void dijkstra(int **grafo, int vertices, int origem, int destino) {
    int distanciaMinima, proximoVertice;
    int *distancia, *verticevisitado, *verticeAnterior;
    
    distancia = (int*) malloc(vertices * sizeof(int));
    verticevisitado = (int*) malloc(vertices * sizeof(int));
    verticeAnterior = (int*) malloc(vertices * sizeof(int));

    // Inicializa o vetor que guarda a menor distância, os vértices visitados e o vértice anterior 
    for (int i = 0; i < vertices; i++) {
        distancia[i] = INF;
        verticevisitado[i] = 0;
        verticeAnterior[i] = -1;
    }
    
    // A distância do nó de origem para ele mesmo é zero
    distancia[origem] = 0;
    
    // Encontra o caminho mais curto para todos os vértices
    for (int qtdRelaxamentos = 0; qtdRelaxamentos < vertices - 1; qtdRelaxamentos++) {
        distanciaMinima = INF;
        // Encontra o próximo vértice não visitado com a menor distância
        for (int i = 0; i < vertices; i++) {
            if (!verticevisitado[i] && distancia[i] <= distanciaMinima) {
                distanciaMinima = distancia[i];
                proximoVertice = i;
            }
        }
        // Marca o próximo vértice como visitado
        verticevisitado[proximoVertice] = 1;
        // Atualiza as distâncias dos vértices adjacentes não visitados
        for (int i = 0; i < vertices; i++) {
            if (!verticevisitado[i] && grafo[proximoVertice][i] &&
                distancia[proximoVertice] + grafo[proximoVertice][i] < distancia[i]) {
                distancia[i] = distancia[proximoVertice] + grafo[proximoVertice][i];
                verticeAnterior[i] = proximoVertice;
            }
        }
    }

    imprimeMenorCaminhoDijkstraBellman(vertices,destino,verticeAnterior,distancia);
    free(distancia);
    free(verticevisitado);
    free(verticeAnterior);
}

void imprimeMenorCaminhoDijkstraBellman(int vertices, int destino, int verticeAnterior[], int distancia[]){
    // Mostrar o caminho mais curto para o vértice de destino como também a distância
    printf("\nCaminho mais curto: ");
    int comprimentocaminho = 0;
    int *caminhovertices; caminhovertices = (int*)malloc(vertices * sizeof(int));
    int verticeatual = destino;
    while (verticeatual != -1) {
        caminhovertices[comprimentocaminho++] = verticeatual;
        verticeatual = verticeAnterior[verticeatual];
    }
    for (int i = comprimentocaminho - 1; i >= 0; i--) {
        printf("%d ", caminhovertices[i]);
        if (i > 0)
            printf("-> ");
    }
    printf("\nDistancia: %d\n", distancia[destino]);
    free(caminhovertices);
}
