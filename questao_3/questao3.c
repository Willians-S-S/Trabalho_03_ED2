#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vertice Vertice;
struct Vertice { //vertice
/* informacao associada a cada nó*/
    int ponto; // tipo ponto 0, ponto 1...
};

typedef struct Graph Graph;
struct Graph {
    Vertice *vertices;
    double **arestas;
};

Graph *iniciaGrafo(int n){
    // n é o numero de vertices ou configuracoes possiveis
    Graph *G;

    G = (Graph *) malloc(sizeof(Graph));
    
    // Alocação de memoria para o vetor de vertices
    G->vertices = (Vertice *) malloc(n * sizeof(Vertice));
    
    // Alocação de memoria para a matriz de arestas
    G->arestas = (double **) malloc(n * sizeof(double *));
    for(int i = 0; i < n; i++){
        G->arestas[i] = (double *) calloc(n, sizeof(double));
    }

    return G;
}

void inserirVerticeEarestasAleatorio(Graph *G, int Tamanho){
    int qtdLigacoesArestas = 0, verticeIraLigar;
    double valorDaAresta;

    for(int i = 0; i < Tamanho; i++){

        G->vertices[i].ponto = i; // atribui o ponto se é 0, 1, 2...

        qtdLigacoesArestas = rand() % 5 + 1;; // a quantidade maxima de ligações de vertice vai ser 5 o minimo vai ser 1 
        for(int j = 0; j < qtdLigacoesArestas; j++){
            verticeIraLigar = rand() % Tamanho; // numero do outro vertice da matriz adjacente
    
            if (i != verticeIraLigar) {
                G->arestas[i][verticeIraLigar] = (double)rand() / RAND_MAX; // valor da ligação // atribuição do valor caso não seja igual ao mesmo vertice
            }
        }
    }
}

void imprimirConteudoVertice(Graph *G, int linha){
    printf("%d\n", G->vertices[linha].ponto);
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
            printf("%.2lf ", G->arestas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

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

int main() {
   
    srand(time(NULL));

    Graph *G; G = NULL;
    int op = -1, qtdVertice, op2, origem, destino, vertice;


    while (op != 0){
        printf("1 - Criar Grafo\n"
            "2 - Encontar caminho mais confiavel\n"
            "3 - Liberar Grafo\n"
            "4 - Imprimir Matriz Adjacente\n"
            "Digite a opcao: ");
        scanf("%d", &op);
        switch (op){
        case 0:
            if(G != NULL){
                printf("Para sair libere o grafo. Digite a quantidade de vertices: ");
                scanf("%d", &qtdVertice);
                liberarGrafo(&G, qtdVertice);
            }
            printf("saindo...\n");
            break;
        case 1:
            if(G == NULL){
                printf("Digite a quantidade de vertice: ");
                scanf("%d", &qtdVertice);
                G = iniciaGrafo(qtdVertice);

                printf("Deseja preencher o grafo de forma aletoria ou manual? 1 - Aleatorio, 2 - manual: ");
                scanf("%d", &op2);
                if(op2 == 1)
                    inserirVerticeEarestasAleatorio(G, qtdVertice);
                else if(op2 == 2){
                    for (int i = 0; i < qtdVertice; i++){
                        printf("Digite o valor do vertice: ");
                        scanf("%d", &G->vertices[i].ponto);
                         
                        for (int j = 0; j < qtdVertice; j++){
                            if (i != j) {
                                scanf("%lf", &G->arestas[i][j]);
                            }
                        }
                    }
                }else
                    printf("Opcao invalida\n");
            }
            else
                printf("Libere o grafo.\n");
            break;
        case 2:
            if (G != NULL){
                printf("Digite a quantidade de vertice: ");
                scanf("%d", &qtdVertice);
                printf("Digite a origem: ");
                scanf("%d", &origem);
                printf("Digite a destino: ");
                scanf("%d", &destino);

                dijkstra(G->arestas, qtdVertice, origem, destino);
                
            }else
                printf("Preencha o grafo.\n");
            break;
        case 3:
            if(G != NULL){
                printf("Digite a quantidade de vertices: ");
                scanf("%d", &qtdVertice);
                liberarGrafo(&G, qtdVertice);
            }else
                printf("O grafo já esta vazio\n");
            break;

        case 4:
            
            if(G != NULL){   
                printf("Digite a quantidade de vertices: ");
                scanf("%d", &qtdVertice);
                imprimirMatrizAdjacente(G, qtdVertice);
            }else
                printf("O grafo já esta vazio\n");
            break;
        default:
            printf("Opção invalida.\n");
            break;
        }
    }

    return 0;
}
