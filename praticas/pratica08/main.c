#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main(void) {
    int num_vertices = 5;
    int capacidade_arestas = 10;
    GrafoPonderado *g = criar_grafo(num_vertices, capacidade_arestas);

    adicionar_aresta(g, 0, 1, 2);
    adicionar_aresta(g, 0, 3, 6);
    adicionar_aresta(g, 1, 2, 3);
    adicionar_aresta(g, 1, 3, 8);
    adicionar_aresta(g, 1, 4, 5);
    adicionar_aresta(g, 2, 4, 7);
    adicionar_aresta(g, 3, 4, 9);

    printf("=== Algoritmo de Kruskal ===\n");
    Aresta *mst_kruskal = (Aresta*) malloc((num_vertices - 1) * sizeof(Aresta));
    int peso_kruskal = kruskal(g, mst_kruskal);

    printf("Arestas na AGM (Kruskal):\n");
    for (int i = 0; i < num_vertices - 1; i++) {
        printf("%d -- %d (Peso: %d)\n", mst_kruskal[i].u, mst_kruskal[i].v, mst_kruskal[i].peso);
    }
    printf("Peso Total da AGM: %d\n\n", peso_kruskal);

    printf("=== Algoritmo de Prim ===\n");
    int pred[5];
    int origem = 0;
    int peso_prim = prim(g, origem, pred);

    printf("Arestas na AGM (Prim, Origem: %d):\n", origem);
    for (int i = 0; i < num_vertices; i++) {
        if (pred[i] != -1) {
            printf("%d -- %d\n", pred[i], i);
        }
    }
    printf("Peso Total da AGM: %d\n", peso_prim);

    free(mst_kruskal);
    liberar_grafo(g);
    return 0;
}