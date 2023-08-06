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

Graph *iniciaGrafo(int n);
void imprimirGrafo(Graph *G, int n);
void inserirArestas(Graph *G);
void imprimirConteudoVertice(Graph *G, int linha);

void dijkstra(int **grafo, int vertices, int origem, int destino);
void imprimeMenorCaminhoDijkstraBellman(int vertices, int destino, int verticeAnterior[], int distancia[]);