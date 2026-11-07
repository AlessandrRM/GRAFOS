#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

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

typedef struct {
    int u;
    int v;
} Aresta;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void destruir_grafo(GrafoLista *g);

void dfs_articulacoes(GrafoLista *g, int *articulacoes);
Aresta* detectar_pontes(GrafoLista *g, int *qtd_pontes);

#endif