#include "busca_profundidade.h"

Pilha* criar_pilha(int capacidade) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->capacidade = capacidade;
    p->topo = -1;
    p->dados = (int*) malloc(capacidade * sizeof(int));
    return p;
}

void empilhar(Pilha *p, int v) {
    if (p->topo < p->capacidade - 1) {
        p->topo++;
        p->dados[p->topo] = v;
    }
}

int desempilhar(Pilha *p) {
    if (p->topo >= 0) {
        int v = p->dados[p->topo];
        p->topo--;
        return v;
    }
    return -1;
}

bool pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void destruir_pilha(Pilha *p) {
    if (!p) return;
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *d, int *f, int *tempo) {
    visitado[u] = 1;
    (*tempo)++;
    if (d != NULL) d[u] = *tempo;

    No *adj = g->listas[u];
    while (adj != NULL) {
        int v = adj->vertice;
        if (!visitado[v]) {
            dfs_recursiva(g, v, visitado, d, f, tempo);
        }
        adj = adj->prox;
    }

    (*tempo)++;
    if (f != NULL) f[u] = *tempo;
}

static void dfs_componentes_aux(GrafoLista *g, int u, int *visitado) {
    visitado[u] = 1;
    No *adj = g->listas[u];
    while (adj != NULL) {
        int v = adj->vertice;
        if (!visitado[v]) {
            dfs_componentes_aux(g, v, visitado);
        }
        adj = adj->prox;
    }
}

int contar_componentes(GrafoLista *g) {
    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));
    int componentes = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_componentes_aux(g, i, visitado);
        }
    }

    free(visitado);
    return componentes;
}

static bool dfs_ciclo_aux(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;
    No *adj = g->listas[u];
    while (adj != NULL) {
        int v = adj->vertice;
        if (!visitado[v]) {
            if (dfs_ciclo_aux(g, v, u, visitado)) {
                return true;
            }
        } else if (v != pai) {
            return true;
        }
        adj = adj->prox;
    }
    return false;
}

bool tem_ciclo(GrafoLista *g) {
    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo_aux(g, i, -1, visitado)) {
                free(visitado);
                return true;
            }
        }
    }

    free(visitado);
    return false;
}