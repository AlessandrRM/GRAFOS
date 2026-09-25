#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

int main() {
    printf("=== Pratica 04: Conectividade e Planaridade ===\n\n");

    int n1 = 5;
    GrafoLista *g1 = criar_grafo(n1);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 1, 2);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 4);

    int *articulacoes = (int*) calloc(n1, sizeof(int));
    dfs_articulacoes(g1, articulacoes);

    printf("Grafo 1 (Caminho de 5 vértices):\n");
    printf("Vértices de corte (articulações): ");
    for (int i = 0; i < n1; i++) {
        if (articulacoes[i]) printf("%d ", i);
    }
    printf("\n");

    int qtd_pontes = 0;
    Aresta *pontes = detectar_pontes(g1, &qtd_pontes);
    printf("Pontes encontradas (%d): ", qtd_pontes);
    for (int i = 0; i < qtd_pontes; i++) {
        printf("(%d, %d) ", pontes[i].u, pontes[i].v);
    }
    printf("\n");
    printf("Passa na fórmula de Euler? %s\n", eh_planar_euler(g1) ? "Sim" : "Não");
    printf("É planar? %s\n\n", eh_planar(g1) ? "Sim" : "Não");

    free(articulacoes);
    free(pontes);
    destruir_grafo(g1);

    int n2 = 5;
    GrafoLista *k5 = criar_grafo(n2);
    for (int i = 0; i < n2; i++) {
        for (int j = i + 1; j < n2; j++) {
            adicionar_aresta(k5, i, j);
        }
    }

    printf("Grafo K5 (Completo com 5 vértices):\n");
    printf("Passa na fórmula de Euler? %s\n", eh_planar_euler(k5) ? "Sim" : "Não");
    printf("É planar? %s\n\n", eh_planar(k5) ? "Sim" : "Não");

    destruir_grafo(k5);

    int n3 = 6;
    GrafoLista *k33 = criar_grafo(n3);
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 6; j++) {
            adicionar_aresta(k33, i, j);
        }
    }

    printf("Grafo K3,3 (Bipartido completo):\n");
    printf("Passa na fórmula de Euler? %s\n", eh_planar_euler(k33) ? "Sim" : "Não");
    printf("É planar? %s\n\n", eh_planar(k33) ? "Sim" : "Não");

    destruir_grafo(k33);

    return 0;
}