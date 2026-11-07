#ifndef COLORACAO_H
#define COLORACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct {
    No **listas;
    int num_vertices;
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void destruir_grafo(GrafoLista *g);

int* coloracao_gulosa(GrafoLista *g, int *num_cores);
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores);
bool eh_bipartido(GrafoLista *g);

#endif