#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade;
    int tamanho;
    int *posicao;
} MinHeap;

GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

MinHeap* criar_min_heap(int capacidade);
void trocar_nos(MinHeap *heap, int i, int j);
void submeter_heap_abaixo(MinHeap *heap, int idx);
void submeter_heap_acima(MinHeap *heap, int idx);
bool esta_no_min_heap(MinHeap *heap, int vertice);
void inserir_min_heap(MinHeap *heap, int vertice, int distancia);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia);
void liberar_min_heap(MinHeap *heap);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif