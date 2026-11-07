#include "agm.h"

GrafoPonderado* criar_grafo(int num_vertices, int capacidade_arestas) {
    GrafoPonderado *g = (GrafoPonderado*) malloc(sizeof(GrafoPonderado));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->listas = (NoAresta**) malloc(num_vertices * sizeof(NoAresta*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    g->arestas = (Aresta*) malloc(capacidade_arestas * sizeof(Aresta));
    return g;
}

void adicionar_aresta(GrafoPonderado *g, int u, int v, int peso) {
    NoAresta *n1 = (NoAresta*) malloc(sizeof(NoAresta));
    n1->destino = v;
    n1->peso = peso;
    n1->proximo = g->listas[u];
    g->listas[u] = n1;

    NoAresta *n2 = (NoAresta*) malloc(sizeof(NoAresta));
    n2->destino = u;
    n2->peso = peso;
    n2->proximo = g->listas[v];
    g->listas[v] = n2;

    g->arestas[g->num_arestas].u = u;
    g->arestas[g->num_arestas].v = v;
    g->arestas[g->num_arestas].peso = peso;
    g->num_arestas++;
}

void liberar_grafo(GrafoPonderado *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        NoAresta *atual = g->listas[i];
        while (atual != NULL) {
            NoAresta *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g->arestas);
    free(g);
}

DSU* criar_dsu(int n) {
    DSU *d = (DSU*) malloc(sizeof(DSU));
    d->n = n;
    d->pai = (int*) malloc(n * sizeof(int));
    d->rank = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        d->pai[i] = i;
        d->rank[i] = 0;
    }
    return d;
}

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        d->pai[x] = find(d, d->pai[x]);
    }
    return d->pai[x];
}

void unir(DSU *d, int x, int y) {
    int raiz_x = find(d, x);
    int raiz_y = find(d, y);

    if (raiz_x != raiz_y) {
        if (d->rank[raiz_x] < d->rank[raiz_y]) {
            d->pai[raiz_x] = raiz_y;
        } else if (d->rank[raiz_x] > d->rank[raiz_y]) {
            d->pai[raiz_y] = raiz_x;
        } else {
            d->pai[raiz_y] = raiz_x;
            d->rank[raiz_x]++;
        }
    }
}

void liberar_dsu(DSU *d) {
    if (!d) return;
    free(d->pai);
    free(d->rank);
    free(d);
}

MinHeap* criar_min_heap(int capacidade) {
    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    heap->posicao = (int*) malloc(capacidade * sizeof(int));
    for (int i = 0; i < capacidade; i++) {
        heap->posicao[i] = -1;
    }
    return heap;
}

void trocar_nos(MinHeap *heap, int i, int j) {
    heap->posicao[heap->dados[i].vertice] = j;
    heap->posicao[heap->dados[j].vertice] = i;

    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;
}

void submeter_heap_abaixo(MinHeap *heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && heap->dados[esq].chave < heap->dados[menor].chave) {
        menor = esq;
    }
    if (dir < heap->tamanho && heap->dados[dir].chave < heap->dados[menor].chave) {
        menor = dir;
    }

    if (menor != idx) {
        trocar_nos(heap, idx, menor);
        submeter_heap_abaixo(heap, menor);
    }
}

void submeter_heap_acima(MinHeap *heap, int idx) {
    while (idx > 0 && heap->dados[idx].chave < heap->dados[(idx - 1) / 2].chave) {
        trocar_nos(heap, idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

bool esta_no_min_heap(MinHeap *heap, int vertice) {
    return heap->posicao[vertice] < heap->tamanho && heap->posicao[vertice] != -1;
}

void inserir_min_heap(MinHeap *heap, int vertice, int chave) {
    if (heap->tamanho == heap->capacidade) return;

    int i = heap->tamanho;
    heap->dados[i].vertice = vertice;
    heap->dados[i].chave = chave;
    heap->posicao[vertice] = i;
    heap->tamanho++;

    submeter_heap_acima(heap, i);
}

NoHeap extrair_minimo(MinHeap *heap) {
    NoHeap vazio = {-1, -1};
    if (heap->tamanho == 0) return vazio;

    NoHeap raiz = heap->dados[0];
    NoHeap ultimo_no = heap->dados[heap->tamanho - 1];

    heap->dados[0] = ultimo_no;

    heap->posicao[raiz.vertice] = -1;
    heap->posicao[ultimo_no.vertice] = 0;

    heap->tamanho--;
    submeter_heap_abaixo(heap, 0);

    return raiz;
}

void diminuir_chave(MinHeap *heap, int vertice, int nova_chave) {
    int i = heap->posicao[vertice];
    if (i == -1) return;

    heap->dados[i].chave = nova_chave;
    submeter_heap_acima(heap, i);
}

void liberar_min_heap(MinHeap *heap) {
    if (!heap) return;
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

static int comparar_arestas(const void *a, const void *b) {
    Aresta *a1 = (Aresta*) a;
    Aresta *a2 = (Aresta*) b;
    return a1->peso - a2->peso;
}

int kruskal(GrafoPonderado *g, Aresta *mst) {
    int V = g->num_vertices;
    int E = g->num_arestas;

    Aresta *arestas = (Aresta*) malloc(E * sizeof(Aresta));
    for (int i = 0; i < E; i++) {
        arestas[i] = g->arestas[i];
    }

    qsort(arestas, E, sizeof(Aresta), comparar_arestas);

    DSU *dsu = criar_dsu(V);
    int peso_total = 0;
    int qtd_mst = 0;

    for (int i = 0; i < E && qtd_mst < V - 1; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;

        if (find(dsu, u) != find(dsu, v)) {
            unir(dsu, u, v);
            mst[qtd_mst++] = arestas[i];
            peso_total += arestas[i].peso;
        }
    }

    free(arestas);
    liberar_dsu(dsu);

    return peso_total;
}

int prim(GrafoPonderado *g, int origem, int *pred) {
    int V = g->num_vertices;
    int *chave = (int*) malloc(V * sizeof(int));
    MinHeap *heap = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        chave[v] = INF;
        pred[v] = -1;
        inserir_min_heap(heap, v, chave[v]);
    }

    chave[origem] = 0;
    diminuir_chave(heap, origem, 0);

    int peso_total = 0;

    while (heap->tamanho > 0) {
        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        if (chave[u] == INF) break;
        peso_total += chave[u];

        NoAresta *aresta = g->listas[u];
        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;

            if (esta_no_min_heap(heap, v) && peso < chave[v]) {
                chave[v] = peso;
                pred[v] = u;
                diminuir_chave(heap, v, chave[v]);
            }
            aresta = aresta->proximo;
        }
    }

    free(chave);
    liberar_min_heap(heap);

    return peso_total;
}