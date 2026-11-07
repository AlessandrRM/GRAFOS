#ifndef AGM_H
#define AGM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

typedef struct {
    int *pai;
    int *rank;
    int n;
} DSU;

typedef struct {
    int u;
    int v;
    int peso;
} Aresta;

typedef struct NoAresta {
    int destino;
    int peso;
    struct NoAresta *proximo;
} NoAresta;

typedef struct {
    int num_vertices;
    int num_arestas;
    NoAresta **listas;
    Aresta *arestas;
} GrafoPonderado;

typedef struct {
    int vertice;
    int chave;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade;
    int tamanho;
    int *posicao;
} MinHeap;

GrafoPonderado* criar_grafo(int num_vertices, int capacidade_arestas);
void adicionar_aresta(GrafoPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoPonderado *g);

DSU* criar_dsu(int n);
int find(DSU *d, int x);
void unir(DSU *d, int x, int y);
void liberar_dsu(DSU *d);

MinHeap* criar_min_heap(int capacidade);
void trocar_nos(MinHeap *heap, int i, int j);
void submeter_heap_abaixo(MinHeap *heap, int idx);
void submeter_heap_acima(MinHeap *heap, int idx);
bool esta_no_min_heap(MinHeap *heap, int vertice);
void inserir_min_heap(MinHeap *heap, int vertice, int chave);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_chave);
void liberar_min_heap(MinHeap *heap);

int kruskal(GrafoPonderado *g, Aresta *mst);
int prim(GrafoPonderado *g, int origem, int *pred);

#endif