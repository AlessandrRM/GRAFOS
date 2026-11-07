#include "conectividade.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->listas = (No**) malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->listas[u];
    g->listas[u] = novo;

    novo = (No*) malloc(sizeof(No));
    novo->vertice = u;
    novo->prox = g->listas[v];
    g->listas[v] = novo;
}

void destruir_grafo(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->listas[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

static void tarjan_dfs(GrafoLista *g, int u, int parent, int *tempo, int *descoberta, int *low, int *articulacoes, Aresta *pontes, int *qtd_pontes) {
    descoberta[u] = low[u] = ++(*tempo);
    int filhos = 0;
    No *adj = g->listas[u];
    while (adj != NULL) {
        int v = adj->vertice;
        if (v == parent) {
            adj = adj->prox;
            continue;
        }
        if (descoberta[v]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        } else {
            filhos++;
            tarjan_dfs(g, v, u, tempo, descoberta, low, articulacoes, pontes, qtd_pontes);
            if (low[v] < low[u]) {
                low[u] = low[v];
            }
            if (parent != -1 && low[v] >= descoberta[u]) {
                if (articulacoes) articulacoes[u] = 1;
            }
            if (low[v] > descoberta[u]) {
                if (pontes && qtd_pontes) {
                    pontes[*qtd_pontes].u = u;
                    pontes[*qtd_pontes].v = v;
                    (*qtd_pontes)++;
                }
            }
        }
        adj = adj->prox;
    }
    if (parent == -1 && filhos > 1) {
        if (articulacoes) articulacoes[u] = 1;
    }
}

void dfs_articulacoes(GrafoLista *g, int *articulacoes) {
    int n = g->num_vertices;
    int *descoberta = (int*) calloc(n, sizeof(int));
    int *low = (int*) calloc(n, sizeof(int));
    int tempo = 0;

    for (int i = 0; i < n; i++) {
        articulacoes[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!descoberta[i]) {
            tarjan_dfs(g, i, -1, &tempo, descoberta, low, articulacoes, NULL, NULL);
        }
    }

    free(descoberta);
    free(low);
}

Aresta* detectar_pontes(GrafoLista *g, int *qtd_pontes) {
    int n = g->num_vertices;
    int *descoberta = (int*) calloc(n, sizeof(int));
    int *low = (int*) calloc(n, sizeof(int));
    int tempo = 0;

    int max_arestas = 0;
    for (int i = 0; i < n; i++) {
        No *adj = g->listas[i];
        while (adj) {
            max_arestas++;
            adj = adj->prox;
        }
    }
    max_arestas /= 2;

    Aresta *pontes = (Aresta*) malloc((max_arestas + 1) * sizeof(Aresta));
    *qtd_pontes = 0;

    for (int i = 0; i < n; i++) {
        if (!descoberta[i]) {
            tarjan_dfs(g, i, -1, &tempo, descoberta, low, NULL, pontes, qtd_pontes);
        }
    }

    free(descoberta);
    free(low);
    return pontes;
}