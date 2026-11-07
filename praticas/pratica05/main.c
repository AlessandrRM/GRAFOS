#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

int main() {
    printf("=== Pratica 05: Coloracao de Grafos ===\n\n");

    int n1 = 6;
    GrafoLista *g1 = criar_grafo(n1);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 0, 2);
    adicionar_aresta(g1, 1, 3);
    adicionar_aresta(g1, 2, 4);
    adicionar_aresta(g1, 3, 5);
    adicionar_aresta(g1, 4, 5);

    printf("--- Grafo 1 (C6 - Ciclo Bipartido de 6 vertices) ---\n");
    printf("E bipartido? %s\n", eh_bipartido(g1) ? "Sim" : "Nao");

    int num_cores_g1 = 0;
    int *cores_g1 = coloracao_gulosa(g1, &num_cores_g1);
    printf("Coloracao Gulosa (ordem padrao): %d cores usadas\n", num_cores_g1);
    for (int i = 0; i < n1; i++) {
        printf("Vertice %d: Cor %d\n", i, cores_g1[i]);
    }
    free(cores_g1);

    int num_cores_wp1 = 0;
    int *cores_wp1 = coloracao_welsh_powell(g1, &num_cores_wp1);
    printf("\nColoracao Welsh-Powell (grau decrescente): %d cores usadas\n", num_cores_wp1);
    for (int i = 0; i < n1; i++) {
        printf("Vertice %d: Cor %d\n", i, cores_wp1[i]);
    }
    free(cores_wp1);
    destruir_grafo(g1);

    int n2 = 5;
    GrafoLista *g2 = criar_grafo(n2);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 0);
    adicionar_aresta(g2, 0, 3);
    adicionar_aresta(g2, 0, 4);

    printf("\n--- Grafo 2 (Ciclo C3 + vertices pendentes em 0) ---\n");
    printf("E bipartido? %s\n", eh_bipartido(g2) ? "Sim" : "Nao");

    int num_cores_g2 = 0;
    int *cores_g2 = coloracao_gulosa(g2, &num_cores_g2);
    printf("Coloracao Gulosa (ordem padrao): %d cores usadas\n", num_cores_g2);
    free(cores_g2);

    int num_cores_wp2 = 0;
    int *cores_wp2 = coloracao_welsh_powell(g2, &num_cores_wp2);
    printf("Coloracao Welsh-Powell: %d cores usadas\n", num_cores_wp2);
    free(cores_wp2);

    destruir_grafo(g2);

    return 0;
}