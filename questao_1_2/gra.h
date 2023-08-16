typedef struct Vertice Vertice;
struct Vertice { //vertice
/* informacao associada a cada noh
 */
    int discos[4];
};

typedef struct Graph Graph;
struct Graph {
    Vertice *vertices;
    int **arestas;
};

Graph *iniciaGrafo(int n);
void imprimirMatrizAdjacente(Graph *G, int n);
void inserirArestas(Graph *G);
void inserirValoresVertices(Graph *G);
void inserirVerticeEarestas(Graph *G);

void imprimirConteudoVertice(Graph *G, int linha);

void dijkstra(int **grafo, int vertices, int origem, int destino);
void imprimeMenorCaminhoDijkstraBellman(int vertices, int destino, int verticeAnterior[], int distancia[]);
void bellmanFord(int **grafo, int vertices, int origem, int destino);