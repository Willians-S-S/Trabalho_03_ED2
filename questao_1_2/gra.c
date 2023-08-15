#include <stdio.h>
#include <stdlib.h>
#include "gra.h"
// #include "valoresVertices.h"

#define TAM 81
#define INF 999999


Graph *iniciaGrafo(int n){
    // n é o numero de vertices ou configuracoes possiveis
    Graph *G;

    G = (Graph *) malloc(sizeof(Graph));
    
    // Alocação de memoria para o vetor de vertices
    G->vertices = (Vertice *) malloc(n * sizeof(Vertice));
    
    // Alocação de memoria para a matriz de arestas
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

    // Inserir as arestas no grafo a partir do arquivo arestas.txt
    while (fscanf(arestas, "%d %d %d %d", &verticeAtual, &aresta1, &aresta2, &aresta3) != EOF){
        G->arestas[verticeAtual][aresta1] = 1;
        G->arestas[verticeAtual][aresta2] = 1;
        if(aresta3 != 9999)
            G->arestas[verticeAtual][aresta3] = 1;    
    }
}

void inserirValoresVertices(Graph *G){
    FILE *valoresVertices; valoresVertices = fopen("valoresVertices.txt", "r");
    int verticeAtual = 0, vermelho, amarelo, verde, rosa;

    // Inserir os valores dos vertices no grafo a partir do arquivo valoresVertices.txt
    while (fscanf(valoresVertices, "%d %d %d %d %d", &verticeAtual, &vermelho, &amarelo, &verde, &rosa) != EOF){
        G->vertices[verticeAtual].discos[0] = vermelho;
        G->vertices[verticeAtual].discos[1] = amarelo;
        G->vertices[verticeAtual].discos[2] = verde;
        G->vertices[verticeAtual].discos[3] = rosa;
    }
}

void imprimirConteudoVertice(Graph *G, int linha){
    printf("%d: (%d, %d, %d, %d)\n", linha, G->vertices[linha].discos[0], G->vertices[linha].discos[1], G->vertices[linha].discos[2], G->vertices[linha].discos[3]);
}

void dijkstra(int **grafo, int vertices, int origem, int destino) {
    int distanciaMinima, indiceVerticeAtual;
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
                indiceVerticeAtual = i;
            }
        }
        // Marca o próximo vértice como visitado
        verticevisitado[indiceVerticeAtual] = 1;
        // Atualiza as distâncias dos vértices adjacentes não visitados
        for (int i = 0; i < vertices; i++) {
            if (!verticevisitado[i] && grafo[indiceVerticeAtual][i] &&
                distancia[indiceVerticeAtual] + grafo[indiceVerticeAtual][i] < distancia[i]) {

                distancia[i] = distancia[indiceVerticeAtual] + grafo[indiceVerticeAtual][i];
                verticeAnterior[i] = indiceVerticeAtual;
            }
        }
    }

    // imprimeMenorCaminhoDijkstraBellman(vertices,destino,verticeAnterior,distancia);
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

void bellmanFord(int **grafo, int vertices, int origem, int destino) {
    int possuiCicloNegativo = 0;
    int *distancia, *verticeAnterior;
    distancia = (int*)malloc(vertices * sizeof(int));
    verticeAnterior = (int*)malloc(vertices * sizeof(int));
    // Os arrays de distância e vértices anteriores são inicializados com valores que indicam a 
    // ausência de ligação(infinito) ou que a posição do vetor ainda não foi utilizada(-1)   
    for (int i = 0; i < vertices; i++) {
        distancia[i] = INF;
        verticeAnterior[i] = -1;
    }
    // A distância do vértice de origem para ele mesmo é zero
    distancia[origem] = 0;
    // Encontra o caminho mais curto partindo do vértice de origem para todos os demais vértices
    for (int qtdRelaxamentos = 0; qtdRelaxamentos < vertices - 1; qtdRelaxamentos++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (grafo[i][j] && distancia[i] != INF && distancia[i] + grafo[i][j] < distancia[j]) {
                    distancia[j] = distancia[i] + grafo[i][j];
                    verticeAnterior[j] = i;
                }
            }
        }
    }

    // Checa se existe um ciclo negativo no grafo, 
    // caso exista não é possível encontrar o menor caminho no grafo devido ás limitações do algoritmo
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (grafo[i][j] && distancia[i] != INF && distancia[i] + grafo[i][j] < distancia[j]) {
                printf("O grafo contem um ciclo negativo.\n");
                possuiCicloNegativo = 1;
                j = vertices;
                i = j;
            }
        }
    }
    // caso não exista um ciclo negativo, imprime o menor caminho
    // if(!possuiCicloNegativo)
    //     imprimeMenorCaminhoDijkstraBellman(vertices,destino,verticeAnterior,distancia);
    free(distancia);
    free(verticeAnterior);
}