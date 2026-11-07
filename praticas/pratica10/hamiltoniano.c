#include "hamiltoniano.h"

Grafo* criar_grafo(int num_vertices) {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->matriz = (int**) malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++) {
        g->matriz[i] = (int*) calloc(num_vertices, sizeof(int));
    }
    return g;
}

void adicionar_aresta(Grafo *g, int u, int v) {
    g->matriz[u][v] = 1;
    g->matriz[v][u] = 1;
}

void liberar_grafo(Grafo *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
}

Grafo* gerar_grafo_aleatorio(int num_vertices, double prob) {
    Grafo *g = criar_grafo(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            if ((double) rand() / RAND_MAX < prob) {
                adicionar_aresta(g, i, j);
            }
        }
    }
    return g;
}

static bool eh_valido(Grafo *g, int v, int pos, int *caminho) {
    if (pos > 0 && g->matriz[caminho[pos - 1]][v] == 0) {
        return false;
    }
    for (int i = 0; i < pos; i++) {
        if (caminho[i] == v) {
            return false;
        }
    }
    return true;
}

static bool hamiltoniano_rec(Grafo *g, int *caminho, int pos) {
    if (pos == g->num_vertices) {
        return true;
    }

    for (int v = 0; v < g->num_vertices; v++) {
        if (eh_valido(g, v, pos, caminho)) {
            caminho[pos] = v;
            if (hamiltoniano_rec(g, caminho, pos + 1)) {
                return true;
            }
            caminho[pos] = -1;
        }
    }
    return false;
}

bool encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho) {
    for (int i = 0; i < g->num_vertices; i++) {
        caminho[i] = -1;
    }
    for (int start = 0; start < g->num_vertices; start++) {
        caminho[0] = start;
        if (hamiltoniano_rec(g, caminho, 1)) {
            return true;
        }
    }
    return false;
}

bool encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *caminho) {
    for (int i = 0; i < g->num_vertices; i++) {
        caminho[i] = -1;
    }
    caminho[0] = 0;
    if (hamiltoniano_rec(g, caminho, 1)) {
        if (g->matriz[caminho[g->num_vertices - 1]][caminho[0]] == 1) {
            return true;
        }
    }
    return false;
}