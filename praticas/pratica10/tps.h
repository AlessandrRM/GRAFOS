#ifndef TPS_H
#define TPS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "hamiltoniano.h"

#define INF 1000000

typedef struct {
    int num_vertices;
    int **custos;
} MatrizDistancias;

MatrizDistancias* criar_matriz_distancias(int num_vertices);
void liberar_matriz_distancias(MatrizDistancias *m);
MatrizDistancias* gerar_matriz_aleatoria(int num_vertices);
MatrizDistancias* grafo_para_tsp(Grafo *g);

int tsp_forca_bruta(MatrizDistancias *m, int *melhor_caminho);
int tsp_vizinho_mais_proximo(MatrizDistancias *m, int origem, int *caminho);
int tsp_insercao(MatrizDistancias *m, int *caminho);

#endif