#include "busca_largura.h"

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

Fila* criar_fila(int capacidade) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->capacidade = capacidade;
    f->dados = (int*) malloc(capacidade * sizeof(int));
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, int v) {
    if (f->tamanho == f->capacidade) return;
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int desfileirar(Fila *f) {
    if (f->tamanho == 0) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

bool fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void destruir_fila(Fila *f) {
    if (!f) return;
    free(f->dados);
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *f = criar_fila(g->num_vertices);

    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = desfileirar(f);

        No *adj = g->listas[u];
        while (adj != NULL) {
            int v = adj->vertice;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
            adj = adj->prox;
        }
    }

    destruir_fila(f);
}

bool eh_bipartido(GrafoLista *g) {
    int *cor = (int*) malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        cor[i] = -1; // -1: sem cor, 0: cor A, 1: cor B
    }

    Fila *f = criar_fila(g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) {
        if (cor[i] == -1) {
            cor[i] = 0;
            enfileirar(f, i);

            while (!fila_vazia(f)) {
                int u = desfileirar(f);

                No *adj = g->listas[u];
                while (adj != NULL) {
                    int v = adj->vertice;
                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        enfileirar(f, v);
                    } else if (cor[v] == cor[u]) {
                        destruir_fila(f);
                        free(cor);
                        return false;
                    }
                    adj = adj->prox;
                }
            }
        }
    }

    destruir_fila(f);
    free(cor);
    return true;
}