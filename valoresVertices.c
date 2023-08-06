#include <stdio.h>
#include "gra.h"
#include "valoresVertices.h"

int verificar_rosa(int pino_2[], int pino_3[], int i){
    int flag = 1;

    for (int j = 0; j < 27 && flag != 3 && flag != 2; j++){
        if (i == pino_3[j]){
            flag = 3;
        }
        else if (i == pino_2[j]){
            flag = 2;
        }
    }
    return flag;
    // for (int j = 0; j < 27; j++){
    //     if (i == pino_3[j]){
    //         return 3;
    //     }
    //     else if (i == pino_2[j]){
    //         return 2;
    //     }
    // }
    // return 1;
}

int verificar_verde(int pino_2[], int pino_3[], int i){
    int flag = 1;

    for (int j = 0; j < 27 && flag != 3 && flag != 2; j++){
        if (i == pino_3[j]){
            flag = 3;
        }
        else if (i == pino_2[j]){
            flag = 2;
        }
    }
    return flag;
    // for (int j = 0; j < 27; j++){
    //     if (i == pino_3[j]){
    //         return 3;
    //     }
    //     else if (i == pino_2[j]){
    //         return 2;
    //     }
    // }
    // return 1;
}

int verificar_amarelo(int pino_2[], int pino_3[], int i){
    int cont = 0, pino = 1;
    
    while (cont < 27 && pino != 2 && pino != 3){
        if (i == pino_3[cont]){
            pino = 3;
        }
        else if (i == pino_2[cont]){
            pino = 2;
        }
        cont++;
    }

    return pino;
}

int verificar_vermelho(int pino_2[], int pino_3[], int i){
    int cont = 0, pino = 1;
    
    while (cont < 27 && pino != 2 && pino != 3){
        if (i == pino_3[cont]){
            pino = 3;
        }
        else if (i == pino_2[cont]){
            pino = 2;
        }
        cont++;
    }

    return pino;
}

void printPinos(int i, int vermelho, int amarelo, int rosa, int verde){
    printf("vertice = %d, vermelho_1 = %d, amarelo_2 = %d, verde_3 = %d, rosa_4 = %d\n", i, vermelho, amarelo, verde, rosa);
}

void setValorVertice(Graph *G, int i, int vermelho, int amarelo, int rosa, int verde){
    G->vertices[i].discos[0] = vermelho;
    G->vertices[i].discos[1] = amarelo;
    G->vertices[i].discos[2] = verde;
    G->vertices[i].discos[3] = rosa;
}

void verificar_pinos(Graph *G, int amarelo_pino_2[], int amarelo_pino_3[], int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i, int vermelho){
    int amarelo = 1, verde = 1, rosa = 1;
    
    amarelo = verificar_amarelo(amarelo_pino_2, amarelo_pino_3, i);
    verde = verificar_verde(verde_pino_2, verde_pino_3, i);
    rosa = verificar_rosa(rosa_pino_2, rosa_pino_3, i);

     if (amarelo == 3){ // amarelo = 3

        if(verde == 3){
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        }
        else if(verde == 2){
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        } 
        else{   
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        }
    }


    else if (amarelo == 2){
        if(verde == 3){
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        }
        else if(verde == 2){
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        } 
        else
        {   
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        }
    }
    else{ // amarelo = 1
        if(verde == 3){
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        }
        else if(verde == 2){
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        } 
        else{   
            if (rosa == 3){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else if(rosa == 2){
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
            else{
                printPinos(i, vermelho, amarelo, rosa, verde);
                setValorVertice(G, i, vermelho, amarelo, rosa, verde);
            }
        }
    }
}

void inserirValoresVertices(Graph *G){
    int rosa_pino_2[] = {1, 3, 8, 10, 12, 16, 19, 24, 25, 27, 32, 36, 38, 39, 41, 47, 49, 52, 55, 57, 60, 63, 68, 69, 74, 75, 80};
    int rosa_pino_3[] = {2, 4, 5, 9, 13, 17, 20, 21, 26, 28, 29, 33, 40, 42, 43, 46, 50, 53, 56, 58, 61, 64, 65, 70, 71, 76, 77};

    int verde_pino_2[] = {4, 7, 8, 10, 13, 14, 15, 19, 20, 27, 29, 30, 35, 41, 42, 47, 53, 54, 58, 59, 64, 67, 68, 69, 70, 79, 80};
    int verde_pino_3[] = {3, 5, 6, 9, 11, 12, 18, 25, 26, 28, 31, 32, 34, 39, 40, 46, 51, 52, 57, 62, 63, 65, 66, 75, 76, 77, 78};

    int amarelo_pino_2[] = {9, 11, 12, 15, 16, 19, 20, 21, 22, 27, 29, 30, 33, 34, 37, 38, 39, 40, 48, 55, 56, 63, 64, 77, 78, 79, 80};
    int amarelo_pino_3[] = {10, 13, 14, 17, 18, 23, 24, 25, 26, 45, 49, 50, 57, 58, 65, 66, 67, 68, 28, 31, 32, 35, 36, 41, 42, 43, 44};

    int vermelho_pino_3[] = {27, 29, 30, 33, 34, 37, 38, 39, 40, 45, 46, 49, 50, 51, 52, 57, 58, 59, 60, 65, 66, 67, 68, 69, 70, 71, 72};
    int vermelho_pino_2[] = {28, 31, 32, 35, 36, 41, 42, 43, 44, 47, 48, 53, 54, 55, 56, 61, 62, 63, 64, 73, 74, 75, 76, 77, 78, 79, 80};

    for (int i = 0; i <= 80; i++){
        int vermelho;
        vermelho = verificar_vermelho(vermelho_pino_2, vermelho_pino_3, i);
    
        if (i >= 26 && vermelho == 3){
            vermelho = 3;
            verificar_pinos(G, amarelo_pino_2, amarelo_pino_3, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i, vermelho);
        }

        else if (i >= 26 && vermelho == 2){ // vermelho = 2
            vermelho = 2;
            verificar_pinos(G, amarelo_pino_2, amarelo_pino_3, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i, vermelho);
        }

        else{
            verificar_pinos(G, amarelo_pino_2, amarelo_pino_3, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i, vermelho);
        }
    }
}