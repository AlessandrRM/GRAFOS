#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

static void imprimir_vetor(const char *rotulo, int *vetor, int tamanho) {
    printf("%s: ", rotulo);
    if (!vetor) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main(void) {
    GrafoLista *g1 = criar_grafo(6);
    adicionar_aresta(g1, 5, 2);
    adicionar_aresta(g1, 5, 0);
    adicionar_aresta(g1, 4, 0);
    adicionar_aresta(g1, 4, 1);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 1);

    printf("Grafo 1 (DAG):\n");
    printf("eh_dag: %d\n", eh_dag(g1));

    int tam_kahn = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(g1, &tam_kahn);
    imprimir_vetor("Kahn", ordem_kahn, tam_kahn);
    free(ordem_kahn);

    int tam_dfs = 0;
    int *ordem_dfs = ordenacao_topologica_dfs(g1, &tam_dfs);
    imprimir_vetor("DFS", ordem_dfs, tam_dfs);
    free(ordem_dfs);

    liberar_grafo(g1);

    printf("\n");

    GrafoLista *g2 = criar_grafo(3);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 0);

    printf("Grafo 2 (Ciclico):\n");
    printf("eh_dag: %d\n", eh_dag(g2));

    int tam_kahn_ciclo = 0;
    int *ordem_kahn_ciclo = ordenacao_topologica_kahn(g2, &tam_kahn_ciclo);
    imprimir_vetor("Kahn", ordem_kahn_ciclo, tam_kahn_ciclo);
    free(ordem_kahn_ciclo);

    int tam_dfs_ciclo = 0;
    int *ordem_dfs_ciclo = ordenacao_topologica_dfs(g2, &tam_dfs_ciclo);
    imprimir_vetor("DFS", ordem_dfs_ciclo, tam_dfs_ciclo);
    free(ordem_dfs_ciclo);

    liberar_grafo(g2);

    return 0;
}