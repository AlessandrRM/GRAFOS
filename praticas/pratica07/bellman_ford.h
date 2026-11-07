#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

typedef struct NoAresta {
    int destino;
    int peso;
    struct NoAresta *proximo;
} NoAresta;

typedef struct {
    int num_vertices;
    NoAresta **listas;
} GrafoListaPonderado;

GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);
void reconstruir_ciclo_negativo(int vertice_ciclo, int *pred, int V);

#endif