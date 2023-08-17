#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gra.h"

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

void imprimirMatrizAdjacente(Graph *G, int n){
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

void inserirVerticeEarestas(Graph *G){
    FILE *verticesEarestas; verticesEarestas = fopen("verticesEarestas.txt", "r");
    int verticeAtual = 0, vermelho, amarelo, verde, rosa, aresta1, aresta2, aresta3;

    // Inserir os valores dos vertices no grafo a partir do arquivo valoresVertices.txt
    while (fscanf(verticesEarestas, "%d %d %d %d %d %d %d %d", &verticeAtual, &vermelho, &amarelo, &verde, &rosa, &aresta1, &aresta2, &aresta3) != EOF){

        //preenche os pinos dos vertices
        G->vertices[verticeAtual].discos[0] = vermelho;
        G->vertices[verticeAtual].discos[1] = amarelo;
        G->vertices[verticeAtual].discos[2] = verde;
        G->vertices[verticeAtual].discos[3] = rosa;

        // marca a ligação das arestas na matriz adjacente
        G->arestas[verticeAtual][aresta1] = 1;
        G->arestas[verticeAtual][aresta2] = 1;
        if(aresta3 != 9999)
            G->arestas[verticeAtual][aresta3] = 1;
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
    if(!possuiCicloNegativo)
        imprimeMenorCaminhoDijkstraBellman(vertices,destino,verticeAnterior,distancia);
    free(distancia);
    free(verticeAnterior);
}

void liberarGrafo(Graph **G, int qtdVertice){
    for (int i = 0; i < qtdVertice; i++){
        free((*G)->arestas[i]);
        (*G)->arestas[i] = NULL;
    }
    free((*G)->vertices);
    (*G)->vertices = NULL;

    free(*G);
    *G = NULL;
}

// jogo

// verifica resposta informa para quais arestas um vertice pode ir
void lugarDasArestas(int *vetorVertice, int *vetorResposta, int *cont){
    *cont = 0;

    for(int i = 0; i < 81; i++){
        if(vetorVertice[i] == 1){
            if(*cont == 0)
                vetorResposta[0] = i;
            if(*cont == 1)
                vetorResposta[1] = i;
            if(*cont == 2)
                vetorResposta[2] = i;
            *cont += 1;
        }
    }
}

// verificar se todos os pinos estão no 3 pino, retorna 4 caso estejam.
int verificaVitoria(Graph *G, int vertice){
    int incremento = 0;
    for (int i = 0; i < 4; i++){
        if(G->vertices[vertice].discos[i] == 3)
        {
            incremento += 1;
        }   
    }
    return incremento;
}

// verifica se o vertice informado é uma opção para onde ir
int verificarOpcaoPraOndeIr(int *vetorResposta, int vertice){
    int cont = 1;
    if (vertice == vetorResposta[0]) 
        cont = 0;
    if (vertice == vetorResposta[1])
        cont = 0;
    if (vertice == vetorResposta[2])
        cont = 0;
    
    return cont;
}

// Essa função permite que o usuário jogue o jogo
void jogar(Graph *G, int vertice){
    int vetorResposta[3], cont, flagParada = 1;


    if(G->vertices[vertice].discos[0] == 3 && G->vertices[vertice].discos[1] == 3 && G->vertices[vertice].discos[2] == 3 && G->vertices[vertice].discos[3] == 3){
        printf("\nVertice com conteudo.\n ");
        imprimirConteudoVertice(G, vertice);
    }else{

        // Esse while continuar até que o usuário ganhe ou desista
        while ((verificaVitoria(G, vertice) != 4) && (flagParada != 0)){

            printf("\nVertice atual e conteudo.\n ");
            imprimirConteudoVertice(G, vertice);
            printf("Possibilidades de para onde pode ir: \n");

            // zera o vetor de resposta
            memset(vetorResposta, 0, sizeof(vetorResposta));

            // verifica resposta informa para quais arestas um vertice pode ir
            lugarDasArestas(G->arestas[vertice], vetorResposta, &cont);
            
            imprimirConteudoVertice(G, vetorResposta[0]);
            imprimirConteudoVertice(G, vetorResposta[1]);
            
            if(cont == 3){
                imprimirConteudoVertice(G, vetorResposta[2]);
            }

            printf("Deseja continuar jogando? 1 - sim, 0 - nao: ");
            scanf("%d", &flagParada);

            // entra nesse if se o usuário deseja continuar jogando, se não entrar isso significa que ele desistiu.
            if(flagParada == 1){
                
                printf("\nDigite o indice do vertice que deseja ir: ");
                scanf("%d", &vertice);

                while ((vertice < 0 || vertice > 80) || (verificarOpcaoPraOndeIr(vetorResposta, vertice))){
                    printf("Indice de vertice não existe ou foi informado um vertice que nao tem ligacao com o vertice atual.\n");
                    printf("Digite novamente o vertice que deseja ir: ");
                    scanf("%d", &vertice);
                }
            }else if(flagParada == 0){
                printf("Voce desistiu\n");
            }else{
                printf("Opcao invalida\n");
            }
        }
    }

    if(flagParada == 1)
        printf("Voce venceu\n");
}