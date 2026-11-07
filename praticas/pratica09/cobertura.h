#ifndef COBERTURA_H
#define COBERTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int u;
    int v;
} Aresta;

typedef struct {
    int num_vertices;
    int num_arestas;
    int **matriz;
    Aresta *arestas;
} Grafo;

Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo *g, int u, int v);
void liberar_grafo(Grafo *g);
Grafo* gerar_grafo_aleatorio(int num_vertices, double probabilidade);

bool eh_cobertura(Grafo *g, const int *cobertura);
void cobertura_minima_bt(Grafo *g, int idx, int *cobertura_atual, int tam_atual, int *melhor_cobertura, int *tam_minimo);
int cobertura_gulosa(Grafo *g, int *cobertura);

#endif