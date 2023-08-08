int verificar_rosa(int pino_2[], int pino_3[], int i);
int verificar_verde(int pino_2[], int pino_3[], int i);
int verificar_amarelo(int pino_2[], int pino_3[], int i);
int verificar_vermelho(int pino_2[], int pino_3[], int i);
void printPinos(int i, int vermelho, int amarelo, int rosa, int verde);
void verificar_pinos(Graph *G, int amarelo_pino_2[], int amarelo_pino_3[], int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i, int vermelho);
void inserirValoresVertices(Graph *G);
void setValorVertice(Graph *G, int i, int vermelho, int amarelo, int rosa, int verde);

void verificar_pinos2(Graph *G, int vermelho, int amarelo, int verde, int rosa, int amarelo_pino_2[], int amarelo_pino_3[], int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i, int cont);
void chamadaRecursiva(Graph *G, int vermelho, int verde, int amarelo, int rosa, int amarelo_pino_2[], int amarelo_pino_3[], int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i, int cont);