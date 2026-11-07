#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main(void) {
    int num_vertices = 6;
    GrafoListaPonderado *g = criar_grafo(num_vertices);

    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 1, 2, 1);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 2, 3, 8);
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 3, 4, 2);
    adicionar_aresta(g, 3, 5, 6);
    adicionar_aresta(g, 4, 5, 3);

    int dist[6];
    int pred[6];
    int origem = 0;

    printf("=== Algoritmo de Dijkstra (Origem: %d) ===\n", origem);
    dijkstra(g, origem, dist, pred);

    printf("\nVertice\tDistancia\tPredecessor\n");
    for (int i = 0; i < num_vertices; i++) {
        if (dist[i] == INF) {
            printf("%d\tINF\t\t%d\n", i, pred[i]);
        } else {
            printf("%d\t%d\t\t%d\n", i, dist[i], pred[i]);
        }
    }

    printf("\n=== Reconstrucao dos Caminhos Minimos ===\n");
    for (int dest = 0; dest < num_vertices; dest++) {
        printf("Caminho ate %d (Custo %d): ", dest, dist[dest]);
        reconstruir_caminho(origem, dest, pred);
    }

    liberar_grafo(g);
    return 0;
}