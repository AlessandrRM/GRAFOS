#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura do nó da lista de adjacência
typedef struct No {
    int vertice;
    struct No *prox;
} No;

// Estrutura do Grafo utilizando Lista de Adjacência
typedef struct {
    No **listas;
    int num_vertices;
} GrafoLista;

// Fila (FIFO) para BFS
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

// Funções do Grafo
GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void destruir_grafo(GrafoLista *g);

Fila* criar_fila(int capacidade);
void enfileirar(Fila *f, int v);
int desfileirar(Fila *f);
bool fila_vazia(Fila *f);
void destruir_fila(Fila *f);

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
bool eh_bipartido(GrafoLista *g);

#endif 