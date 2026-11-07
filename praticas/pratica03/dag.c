#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

GrafoLista* criar_grafo(int num_vertices) {
    if (num_vertices <= 0) {
        return NULL;
    }
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    if (!g) {
        return NULL;
    }
    g->num_vertices = num_vertices;
    g->adj = (No**) calloc(num_vertices, sizeof(No*));
    if (!g->adj) {
        free(g);
        return NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) {
        return;
    }
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) {
        return;
    }
    novo->vertice = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

void liberar_grafo(GrafoLista *g) {
    if (!g) {
        return;
    }
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->adj[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    if (!g || !tamanho || g->num_vertices <= 0) {
        if (tamanho) {
            *tamanho = 0;
        }
        return NULL;
    }

    int n = g->num_vertices;
    int *grau_entrada = (int*) calloc(n, sizeof(int));
    if (!grau_entrada) {
        *tamanho = 0;
        return NULL;
    }

    for (int u = 0; u < n; u++) {
        for (No *p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (v >= 0 && v < n) {
                grau_entrada[v]++;
            }
        }
    }

    int *fila = (int*) malloc(n * sizeof(int));
    if (!fila) {
        free(grau_entrada);
        *tamanho = 0;
        return NULL;
    }

    int inicio = 0;
    int fim = 0;
    for (int i = 0; i < n; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    int *resultado = (int*) malloc(n * sizeof(int));
    if (!resultado) {
        free(grau_entrada);
        free(fila);
        *tamanho = 0;
        return NULL;
    }

    int count = 0;
    while (inicio < fim) {
        int u = fila[inicio++];
        resultado[count++] = u;

        for (No *p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (v >= 0 && v < n) {
                grau_entrada[v]--;
                if (grau_entrada[v] == 0) {
                    fila[fim++] = v;
                }
            }
        }
    }

    free(grau_entrada);
    free(fila);

    if (count == n) {
        *tamanho = count;
        return resultado;
    }

    free(resultado);
    *tamanho = 0;
    return NULL;
}

static int dfs_visitar(GrafoLista *g, int u, int *visitado, int *resultado, int *pos) {
    visitado[u] = 1;

    for (No *p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->vertice;
        if (visitado[v] == 1) {
            return 0;
        }
        if (visitado[v] == 0) {
            if (!dfs_visitar(g, v, visitado, resultado, pos)) {
                return 0;
            }
        }
    }

    visitado[u] = 2;
    resultado[(*pos)--] = u;
    return 1;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    if (!g || !tamanho || g->num_vertices <= 0) {
        if (tamanho) {
            *tamanho = 0;
        }
        return NULL;
    }

    int n = g->num_vertices;
    int *visitado = (int*) calloc(n, sizeof(int));
    if (!visitado) {
        *tamanho = 0;
        return NULL;
    }

    int *resultado = (int*) malloc(n * sizeof(int));
    if (!resultado) {
        free(visitado);
        *tamanho = 0;
        return NULL;
    }

    int pos = n - 1;
    for (int i = 0; i < n; i++) {
        if (visitado[i] == 0) {
            if (!dfs_visitar(g, i, visitado, resultado, &pos)) {
                free(visitado);
                free(resultado);
                *tamanho = 0;
                return NULL;
            }
        }
    }

    free(visitado);
    *tamanho = n;
    return resultado;
}

int eh_dag(GrafoLista *g) {
    if (!g) {
        return 0;
    }
    if (g->num_vertices == 0) {
        return 1;
    }
    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem != NULL) {
        free(ordem);
        return 1;
    }
    return 0;
}