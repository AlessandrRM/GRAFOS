#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int num_vertices;
    int **matriz;
} Grafo;

Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo *g, int u, int v);
void liberar_grafo(Grafo *g);
Grafo* gerar_grafo_aleatorio(int num_vertices, double prob);

bool encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho);
bool encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *caminho);

#endif