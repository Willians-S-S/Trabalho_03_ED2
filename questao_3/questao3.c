#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void imprimeCaminhoConfiavel(int vertices, int destino, int verticeAnterior[], double confiabilidade[]) {
    // Mostrar o caminho mais confiável para o vértice de destino, bem como a confiabilidade total
    printf("\nCaminho mais confiável: ");
    int *caminhovertices = (int*)malloc(vertices * sizeof(int));
    int verticeatual = destino;
    int comprimentocaminho = 0;
    while (verticeatual != -1) {
        caminhovertices[comprimentocaminho++] = verticeatual;
        verticeatual = verticeAnterior[verticeatual];
    }
    for (int i = comprimentocaminho - 1; i >= 0; i--) {
        printf("%d ", caminhovertices[i]);
        if (i > 0)
            printf("-> ");
    }
    printf("\nConfiabilidade total: %lf\n", confiabilidade[destino]);
    free(caminhovertices);
}

void dijkstra(double **grafo, int vertices, int origem, int destino) {
    double *confiabilidade;
    int *verticevisitado, *verticeAnterior;
    int cont = 0;
    
    confiabilidade = (double*) malloc(vertices * sizeof(double));
    verticevisitado = (int*) malloc(vertices * sizeof(int));
    verticeAnterior = (int*) malloc(vertices * sizeof(int));

    // Inicializa o vetor que guarda a maior confiabilidade, os vértices visitados e o vértice anterior 
    for (int i = 0; i < vertices; i++) {
        confiabilidade[i] = 0.0;
        verticevisitado[i] = 0;
        verticeAnterior[i] = -1;
    }
    
    // A confiabilidade do nó de origem é 1.0
    confiabilidade[origem] = 1.0;
    
    // Encontra o caminho mais confiável para todos os vértices
    for (int qtdRelaxamentos = 0; qtdRelaxamentos < vertices - 1; qtdRelaxamentos++) {
        double maiorConfiabilidade = 0.0;
        int indiceVerticeAtual = -1;

        // Encontra o próximo vértice não visitado com a maior confiabilidade
        for (int i = 0; i < vertices; i++) {
            if (!verticevisitado[i] && confiabilidade[i] >= maiorConfiabilidade) {
                maiorConfiabilidade = confiabilidade[i];
                indiceVerticeAtual = i;
            }
        }

        // Marca o atual vértice como visitado
        verticevisitado[indiceVerticeAtual] = 1;
        
        // Atualiza as confiabilidades dos vértices adjacentes não visitados
        for (int i = 0; i < vertices; i++) {
            if (!verticevisitado[i] && grafo[indiceVerticeAtual][i] > 0) {
                double novaConfiabilidade = (confiabilidade[indiceVerticeAtual] * grafo[indiceVerticeAtual][i]);
                if (novaConfiabilidade > confiabilidade[i]) {
                    confiabilidade[i] = novaConfiabilidade;
                    verticeAnterior[i] = indiceVerticeAtual;
                    printf("Nova confiabilida: %lf\n", novaConfiabilidade);
                }
            }
        }
    }

    // Imprimir o caminho mais confiável e a confiabilidade total
    imprimeCaminhoConfiavel(vertices, destino, verticeAnterior, confiabilidade);
    free(confiabilidade);
    free(verticevisitado);
    free(verticeAnterior);
}

int main() {
    int vertices = 4; // Número total de vértices no grafo
    int origem = 0;   // Vértice de origem para o cálculo do caminho mais confiável
    int destino = 3;  // Vértice de destino para o cálculo do caminho mais confiável

    // Criação e inicialização da matriz de adjacência (representando probabilidades de confiabilidade)
    double **adjMatrix = (double **)malloc(vertices * sizeof(double *));

    for (int i = 0; i < vertices; i++) {
        adjMatrix[i] = (double *)malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = 0.0; // Inicialize com as probabilidades de confiabilidade apropriadas
        }
    }

    // Preencha a matriz de adjacência com as probabilidades de confiabilidade entre os vértices
    adjMatrix[0][1] = 0.2; // Exemplo: Probabilidade de confiabilidade da aresta A -> B
    adjMatrix[0][2] = 0.2; // Exemplo: Probabilidade de confiabilidade da aresta A -> B
    
    // adjMatrix[1][2] = 0.5; // Exemplo: Probabilidade de confiabilidade da aresta A -> B
    adjMatrix[1][3] = 0.5; // Exemplo: Probabilidade de confiabilidade da aresta A -> B
    
    adjMatrix[2][1] = 0.9; // Exemplo: Probabilidade de confiabilidade da aresta A -> B
    adjMatrix[2][3] = 0.3; // Exemplo: Probabilidade de confiabilidade da aresta A -> B
    
    
    for(int i = 0; i < vertices; i++){
        printf("  %d ", i);
    }
    printf("\n");
    for(int i = 0; i < vertices; i++){
        printf("%d ", i);
        for(int j = 0; j < vertices; j++){
            printf("%.1lf ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    // Chama a função dijkstra para encontrar o caminho mais confiável entre os vértices de origem e destino
    dijkstra(adjMatrix, vertices, origem, destino);

    // Libera a memória alocada para a matriz de adjacência
    for (int i = 0; i < vertices; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);

    return 0;
}
