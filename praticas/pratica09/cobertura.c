#include "cobertura.h"

Grafo* criar_grafo(int num_vertices) {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->matriz = (int**) malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++) {
        g->matriz[i] = (int*) calloc(num_vertices, sizeof(int));
    }
    g->arestas = (Aresta*) malloc((num_vertices * (num_vertices - 1) / 2) * sizeof(Aresta));
    return g;
}

void adicionar_aresta(Grafo *g, int u, int v) {
    if (g->matriz[u][v] == 0) {
        g->matriz[u][v] = 1;
        g->matriz[v][u] = 1;
        g->arestas[g->num_arestas].u = u;
        g->arestas[g->num_arestas].v = v;
        g->num_arestas++;
    }
}

void liberar_grafo(Grafo *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g->arestas);
    free(g);
}

Grafo* gerar_grafo_aleatorio(int num_vertices, double probabilidade) {
    Grafo *g = criar_grafo(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            if ((double) rand() / RAND_MAX < probabilidade) {
                adicionar_aresta(g, i, j);
            }
        }
    }
    return g;
}

bool eh_cobertura(Grafo *g, const int *cobertura) {
    for (int i = 0; i < g->num_arestas; i++) {
        int u = g->arestas[i].u;
        int v = g->arestas[i].v;
        if (cobertura[u] == 0 && cobertura[v] == 0) {
            return false;
        }
    }
    return true;
}

void cobertura_minima_bt(Grafo *g, int idx, int *cobertura_atual, int tam_atual, int *melhor_cobertura, int *tam_minimo) {
    if (tam_atual >= *tam_minimo) {
        return;
    }

    if (idx == g->num_vertices) {
        if (eh_cobertura(g, cobertura_atual)) {
            *tam_minimo = tam_atual;
            for (int i = 0; i < g->num_vertices; i++) {
                melhor_cobertura[i] = cobertura_atual[i];
            }
        }
        return;
    }

    cobertura_atual[idx] = 1;
    cobertura_minima_bt(g, idx + 1, cobertura_atual, tam_atual + 1, melhor_cobertura, tam_minimo);

    cobertura_atual[idx] = 0;
    cobertura_minima_bt(g, idx + 1, cobertura_atual, tam_atual, melhor_cobertura, tam_minimo);
}

int cobertura_gulosa(Grafo *g, int *cobertura) {
    int V = g->num_vertices;
    int E = g->num_arestas;

    for (int i = 0; i < V; i++) {
        cobertura[i] = 0;
    }

    int *coberta = (int*) calloc(E, sizeof(int));
    int arestas_cobertas = 0;
    int tam_cobertura = 0;

    while (arestas_cobertas < E) {
        int max_grau = -1;
        int melhor_v = -1;

        for (int v = 0; v < V; v++) {
            if (cobertura[v] == 1) continue;

            int grau = 0;
            for (int e = 0; e < E; e++) {
                if (!coberta[e] && (g->arestas[e].u == v || g->arestas[e].v == v)) {
                    grau++;
                }
            }

            if (grau > max_grau) {
                max_grau = grau;
                melhor_v = v;
            }
        }

        if (melhor_v == -1 || max_grau == 0) break;

        cobertura[melhor_v] = 1;
        tam_cobertura++;

        for (int e = 0; e < E; e++) {
            if (!coberta[e] && (g->arestas[e].u == melhor_v || g->arestas[e].v == melhor_v)) {
                coberta[e] = 1;
                arestas_cobertas++;
            }
        }
    }

    free(coberta);
    return tam_cobertura;
}