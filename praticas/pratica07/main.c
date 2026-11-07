#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int main(void) {
    int num_vertices = 5;
    GrafoListaPonderado *g = criar_grafo(num_vertices);

    adicionar_aresta(g, 0, 1, -1);
    adicionar_aresta(g, 0, 2, 4);
    adicionar_aresta(g, 1, 2, 3);
    adicionar_aresta(g, 1, 3, 2);
    adicionar_aresta(g, 1, 4, 2);
    adicionar_aresta(g, 3, 2, 5);
    adicionar_aresta(g, 3, 1, 1);
    adicionar_aresta(g, 4, 3, -3);

    int dist[5];
    int pred[5];
    int origem = 0;

    printf("=== Algoritmo de Bellman-Ford (Origem: %d) ===\n", origem);
    int resultado = bellman_ford(g, origem, dist, pred);

    if (resultado) {
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
    }

    liberar_grafo(g);
    return 0;
}