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
void inserirVerticeEarestas(Graph *G);

void imprimirConteudoVertice(Graph *G, int linha);

void dijkstra(int **grafo, int vertices, int origem, int destino);
void imprimeMenorCaminhoDijkstraBellman(int vertices, int destino, int verticeAnterior[], int distancia[]);
void bellmanFord(int **grafo, int vertices, int origem, int destino);

void liberarGrafo(Graph **G, int qtdVertice);

void lugarDasArestas(int *vetorVertice, int *vetorResposta, int *cont);
int verificaVitoria(Graph *G, int vertice);
int verificarOpcaoPraOndeIr(int *vetorResposta, int vertice);
void jogar(Graph *G, int vertice);