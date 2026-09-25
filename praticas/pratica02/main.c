#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

int main() {
    printf("=== Teste de Algoritmos em Grafos (Pratica 02) ===\n\n");

    int n1 = 6;
    GrafoLista *g1 = criar_grafo(n1);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 1, 2);
    adicionar_aresta(g1, 2, 0);
    adicionar_aresta(g1, 3, 4);
    adicionar_aresta(g1, 4, 5);

    printf("--- Grafo 1 (Com Ciclo Ímpar) ---\n");
    printf("Número de componentes conexos: %d\n", contar_componentes(g1));
    printf("Possui ciclo? %s\n", tem_ciclo(g1) ? "Sim" : "Não");
    printf("É bipartido? %s\n", eh_bipartido(g1) ? "Sim" : "Não");

    int *dist = (int*) malloc(n1 * sizeof(int));
    int *pred = (int*) malloc(n1 * sizeof(int));
    bfs(g1, 0, dist, pred);

    printf("\n[BFS a partir do vertice 0]\n");
    for (int i = 0; i < n1; i++) {
        printf("Vertice %d: Distancia = %d, Predecessor = %d\n", i, dist[i], pred[i]);
    }

    int *visitado = (int*) calloc(n1, sizeof(int));
    int *d = (int*) malloc(n1 * sizeof(int));
    int *f = (int*) malloc(n1 * sizeof(int));
    int tempo = 0;

    dfs_recursiva(g1, 0, visitado, d, f, &tempo);

    printf("\n[DFS a partir do vertice 0]\n");
    for (int i = 0; i < n1; i++) {
        if (visitado[i]) {
            printf("Vertice %d: Descoberta = %d, Finalizacao = %d\n", i, d[i], f[i]);
        } else {
            printf("Vertice %d: Não alcançado a partir da origem 0\n", i);
        }
    }

    free(dist);
    free(pred);
    free(visitado);
    free(d);
    free(f);
    destruir_grafo(g1);

    int n2 = 4;
    GrafoLista *g2 = criar_grafo(n2);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 0, 2);
    adicionar_aresta(g2, 1, 3);

    printf("\n--- Grafo 2 (Árvore Bipartida) ---\n");
    printf("Número de componentes conexos: %d\n", contar_componentes(g2));
    printf("Possui ciclo? %s\n", tem_ciclo(g2) ? "Sim" : "Não");
    printf("É bipartido? %s\n", eh_bipartido(g2) ? "Sim" : "Não");

    destruir_grafo(g2);

    return 0;
}