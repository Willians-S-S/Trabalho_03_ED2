#include <stdio.h>
#include <stdlib.h>
#include "gra.h"
#include "valoresVertices.h"

#define TAM 81

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

void jogar(Graph *G, int vertice){
    int vetorResposta[3], cont, flagParada = 1;


    if(G->vertices[vertice].discos[0] == 3 && G->vertices[vertice].discos[1] == 3 && G->vertices[vertice].discos[2] == 3 && G->vertices[vertice].discos[3] == 3){
        printf("\nVertice atual e conteudo.\n ");
        imprimirConteudoVertice(G, vertice);
    }else{

        while (G->vertices[vertice].discos[0] != 3 && G->vertices[vertice].discos[1] != 3 && G->vertices[vertice].discos[2] != 3 && G->vertices[vertice].discos[3] != 3 && flagParada != 0){

            printf("\nVertice atual e conteudo.\n ");
            imprimirConteudoVertice(G, vertice);
            printf("Possibilidades de para onde pode ir: \n");

            memset(vetorResposta, 0, sizeof(vetorResposta));

            lugarDasArestas(G->arestas[vertice], vetorResposta, &cont);
            
            imprimirConteudoVertice(G, vetorResposta[0]);
            imprimirConteudoVertice(G, vetorResposta[1]);
            
            if(cont == 3){
                imprimirConteudoVertice(G, vetorResposta[2]);
            }

            printf("\nDigite o indice do vertice que deseja ir: ");
            scanf("%d ", &vertice);

            if((vertice < 0 && vertice > 80) && (vertice != vetorResposta[0] && vertice != vetorResposta[1] &&vertice != vetorResposta[2])){
                printf("Indice de vertice não existe.\n");
                flagParada = 0;
            }
        }
    }

    printf("Voce venceu\n");
    

}

int main(){
    Graph *G;
    int op, vertice, opJogo; op = -1;

    G = iniciaGrafo(TAM);

    
    inserirArestas(G);
    inserirValoresVertices(G);
    //
    // for(int i = 0; i < TAM; i++)
    //     imprimirConteudoVertice(G, i);

    // imprimirGrafo(G, TAM);
    // dijkstra(G->arestas, TAM, 0, 65);

    while (op != 0){
        printf("1 - imprimir valores de todos os vertices\n"
            "2 - imprimir arestas\n"
            "3 - Dijkstra\n"
            "4 - Imprimir arestas\n"
            "5 - Outro ai\n"
            "6 - Jogar\n\n"
            "Digite a opcao: "
        );
        scanf("%d", &op);

        switch (op){
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
            imprimirGrafo(G, TAM); // imprimir arestas
            break;
        case 4:
            dijkstra(G->arestas, TAM, 0, 65);
            break;
        case 5:
            printf("Outro ai\n");
            break;
        case 6:

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
            break;
        }
    }
    
    return 0;
}