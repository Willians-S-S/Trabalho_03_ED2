#include <stdio.h>
#include <stdlib.h>

#define TAM 80

typedef struct Vertice Vertice;


struct Vertice { //vertice
/* informacao associada a cada noh
 */
    int discos[4];
};
struct arc {
    int adj;
/* informacao associada a cada arco */
};

typedef struct Graph Graph;
struct Graph {
    Vertice *vertices;
    int **arestas;
};


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

void inserirValorVertice(Graph *G, int linha, int Disco1maior, int Disco2medioMa, int Disco3medioMe, int Disco4menor, int aresta1, int aresta2, int aresta3, int qtdArestas){
    G->vertices[linha].discos[0] = Disco1maior;
    G->vertices[linha].discos[1] = Disco2medioMa;
    G->vertices[linha].discos[2] = Disco3medioMe;
    G->vertices[linha].discos[3] = Disco4menor;

    if(qtdArestas == 2){
        G->arestas[linha][aresta1] = 1;
        G->arestas[linha][aresta2] = 1;
    }else if(qtdArestas == 3){
        G->arestas[linha][aresta1] = 1;
        G->arestas[linha][aresta2] = 1;
        G->arestas[linha][aresta3] = 1;
    }
}

void imprimirConteudoVertice(Graph *G, int linha){
    printf("Vertice %d: %d %d %d %d\n", linha, G->vertices[linha].discos[0], G->vertices[linha].discos[1], G->vertices[linha].discos[2], G->vertices[linha].discos[3]);
}

int main(){
    Graph *G;
    int linha,  Disco1maior,  Disco2medioMa,  Disco3medioMe,  Disco4menor,  aresta1,  aresta2,  aresta3,  qtdArestas;

    G = iniciaGrafo(TAM);

    inserirValorVertice(G, 0, 1, 1, 1, 1, 1, 2, 0, 2); // vertice 0
    inserirValorVertice(G, linha = 1, Disco1maior = 1, Disco2medioMa = 1, Disco3medioMe = 1, Disco4menor = 2, aresta1 = 0, aresta2 = 2, aresta3 = 3, qtdArestas = 3); // vertice 1
    inserirValorVertice(G, linha = 2, Disco1maior = 1, Disco2medioMa = 1, Disco3medioMe = 1, Disco4menor = 3, aresta1 = 0, aresta2 = 1, aresta3 = 4, qtdArestas = 3); // vertice 2
    imprimirGrafo(G, TAM);
    imprimirConteudoVertice(G, 0);
    imprimirConteudoVertice(G, 1);
    imprimirConteudoVertice(G, 2);
    return 0;
}


