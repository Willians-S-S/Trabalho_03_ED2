#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gra.h"

#define TAM 81

int main(){
    Graph *G;
    int op, vertice, opJogo, cont, vetorResposta[3], origem, destino; op = -1;

    G = iniciaGrafo(TAM);
    
    inserirVerticeEarestas(G);

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
            printf("Dijkstra\n");
            printf("Digite o vertice de origem: ");
            scanf("%d", &origem);
            printf("Digite o vertice de destino: ");
            scanf("%d", &destino);

            if((origem >= 0 && origem <= 80) && (destino >= 0 && destino <= 80) )
                dijkstra(G->arestas, TAM, origem, destino);
            else
                printf("Verifique se os vertices informados existem\n");

            break;
        case 6:
            printf("Ford-Moore-Bellman\n");
            printf("Digite o vertice de origem: ");
            scanf("%d", &origem);
            printf("Digite o vertice de destino: ");
            scanf("%d", &destino);

            if((origem >= 0 && origem <= 80) && (destino >= 0 && destino <= 80) )
                bellmanFord(G->arestas, TAM, origem, destino);
            else
                printf("Verifique se os vertices informados existem\n");
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
    liberarGrafo(&G, 81);
    return 0;
}