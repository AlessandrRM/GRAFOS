#include "coloracao.h"

typedef struct {
    int vertice;
    int grau;
} VerticeGrau;

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

static int compara_grau(const void *a, const void *b) {
    VerticeGrau *v1 = (VerticeGrau*) a;
    VerticeGrau *v2 = (VerticeGrau*) b;
    return v2->grau - v1->grau;
}

int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    int *cor = (int*) malloc(n * sizeof(int));
    bool *disponivel = (bool*) malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        cor[i] = -1;
        disponivel[i] = true;
    }

    cor[0] = 0;

    for (int u = 1; u < n; u++) {
        No *adj = g->listas[u];
        while (adj) {
            if (cor[adj->vertice] != -1) {
                disponivel[cor[adj->vertice]] = false;
            }
            adj = adj->prox;
        }

        int cr;
        for (cr = 0; cr < n; cr++) {
            if (disponivel[cr]) break;
        }

        cor[u] = cr;

        adj = g->listas[u];
        while (adj) {
            if (cor[adj->vertice] != -1) {
                disponivel[cor[adj->vertice]] = true;
            }
            adj = adj->prox;
        }
    }

    int max_cor = 0;
    for (int i = 0; i < n; i++) {
        if (cor[i] > max_cor) max_cor = cor[i];
    }
    *num_cores = max_cor + 1;

    free(disponivel);
    return cor;
}

int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    VerticeGrau *vg = (VerticeGrau*) malloc(n * sizeof(VerticeGrau));

    for (int i = 0; i < n; i++) {
        vg[i].vertice = i;
        vg[i].grau = 0;
        No *adj = g->listas[i];
        while (adj) {
            vg[i].grau++;
            adj = adj->prox;
        }
    }

    qsort(vg, n, sizeof(VerticeGrau), compara_grau);

    int *cor = (int*) malloc(n * sizeof(int));
    bool *disponivel = (bool*) malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        cor[i] = -1;
        disponivel[i] = true;
    }

    for (int i = 0; i < n; i++) {
        int u = vg[i].vertice;

        No *adj = g->listas[u];
        while (adj) {
            if (cor[adj->vertice] != -1) {
                disponivel[cor[adj->vertice]] = false;
            }
            adj = adj->prox;
        }

        int cr;
        for (cr = 0; cr < n; cr++) {
            if (disponivel[cr]) break;
        }

        cor[u] = cr;

        adj = g->listas[u];
        while (adj) {
            if (cor[adj->vertice] != -1) {
                disponivel[cor[adj->vertice]] = true;
            }
            adj = adj->prox;
        }
    }

    int max_cor = 0;
    for (int i = 0; i < n; i++) {
        if (cor[i] > max_cor) max_cor = cor[i];
    }
    *num_cores = max_cor + 1;

    free(vg);
    free(disponivel);
    return cor;
}

bool eh_bipartido(GrafoLista *g) {
    int n = g->num_vertices;
    int *cor = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) cor[i] = -1;

    int *fila = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (cor[i] == -1) {
            int inicio = 0, fim = 0;
            cor[i] = 0;
            fila[fim++] = i;

            while (inicio < fim) {
                int u = fila[inicio++];
                No *adj = g->listas[u];
                while (adj) {
                    int v = adj->vertice;
                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        fila[fim++] = v;
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        free(fila);
                        return false;
                    }
                    adj = adj->prox;
                }
            }
        }
    }

    free(cor);
    free(fila);
    return true;
}