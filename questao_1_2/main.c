#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gra.h"

#define TAM 81

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

#include <time.h>

int main(){
    Graph *G;
    int op, vertice, opJogo, cont, vetorResposta[3]; op = -1;

    G = iniciaGrafo(TAM);
    
    inserirVerticeEarestas(G);
    // inserirValoresVertices(G);

    while (op != 0){
        printf("\n1 - imprimir valores de todos os vertices\n"
            "2 - imprimir um vertice\n"
            "3 - Imprimir matriz adjacente arestas\n"
            "4 - Imprimir para onde as arestas de vertice estao ligadas\n"
            "5 - Dijkstra\n"
            "6 - Ford-Moore-Bellman\n"
            "7 - Jogar\n\n"
            "Digite a opcao: "
        );
        scanf("%d", &op);

        switch (op){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            for(int i = 0; i < TAM; i++)
                imprimirConteudoVertice(G, i); // imprimir valores dos vertices
            break;
        case 2:
            printf("Digite o indice do vertice: ");
            scanf("%d", &vertice);
            if(vertice >= 0 && vertice <= 80)
                imprimirConteudoVertice(G, vertice);
            else
                printf("Indice de vertice não existe.\n");
            break;
        case 3:
            imprimirMatrizAdjacente(G, TAM); // imprimir arestas
            break;
        case 4:
            cont = 0;
            printf("Digite o indice do vertice: ");
            scanf("%d", &vertice);

            if(vertice >= 0 && vertice <= 80){
                lugarDasArestas(G->arestas[vertice], vetorResposta, &cont);
                
                imprimirConteudoVertice(G, vetorResposta[0]);
                imprimirConteudoVertice(G, vetorResposta[1]);
                
                if(cont == 3){
                    imprimirConteudoVertice(G, vetorResposta[2]);
                }
                memset(vetorResposta, 0, sizeof(vetorResposta));
                
            }else
                printf("Indice de vertice não existe.\n");
            break;
        case 5:
            // clock_t start, end;
            // double cpu_time_used_ms = 0;

            // for (int i = 0; i < 30; i++)
            // {
            //     start = clock(); // Marca o início da contagem de tempo

            //     // Código que você deseja medir
            //     dijkstra(G->arestas, TAM, 0, 65);

            //     end = clock(); // Marca o final da contagem de tempo

            //     cpu_time_used_ms += ((double) (end - start)) / (CLOCKS_PER_SEC / 1000);
            //     /* code */
            // }
            

            // cpu_time_used_ms /= 30;

            // printf("Tempo de execução: %f milissegundos\n", cpu_time_used_ms);

            break;
        case 6:
            printf("Ford-Moore-Bellman\n");
            clock_t start, end;
            double cpu_time_used_ms = 0;

            for (int i = 0; i < 30; i++)
            {
                start = clock(); // Marca o início da contagem de tempo

                // Código que você deseja medir
                 bellmanFord(G->arestas, TAM, 0, 65);

                end = clock(); // Marca o final da contagem de tempo

                cpu_time_used_ms += ((double) (end - start)) / (CLOCKS_PER_SEC / 1000);
                /* code */
            }

            cpu_time_used_ms /= 30;

            printf("Tempo de execução: %f milissegundos\n", cpu_time_used_ms);
           
            break;
        case 7:

            printf("\nDeseja começar de algum vertice? 1 - sim, 2 - nao: ");
            scanf("%d", &opJogo);

            if(opJogo == 1){
                printf("\nDigite o indice do vertice: ");
                scanf("%d", &vertice);

                if(vertice >= 0 && vertice <= 80)
                    jogar(G, vertice);
                else
                    printf("\nIndice de vertice não existe.\n");
            }else if(opJogo == 2)
                jogar(G, 0);
            else
                printf("\nOpcao invalida\n");
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }
    }
    
    return 0;
}