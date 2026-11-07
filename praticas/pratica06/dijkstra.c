#include "dijkstra.h"

GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->listas = (NoAresta**) malloc(num_vertices * sizeof(NoAresta*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    NoAresta *novo = (NoAresta*) malloc(sizeof(NoAresta));
    novo->destino = v;
    novo->peso = peso;
    novo->proximo = g->listas[u];
    g->listas[u] = novo;
}

void liberar_grafo(GrafoListaPonderado *g) {
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
    free(g);
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

    if (esq < heap->tamanho && heap->dados[esq].distancia < heap->dados[menor].distancia) {
        menor = esq;
    }

    if (dir < heap->tamanho && heap->dados[dir].distancia < heap->dados[menor].distancia) {
        menor = dir;
    }

    if (menor != idx) {
        trocar_nos(heap, idx, menor);
        submeter_heap_abaixo(heap, menor);
    }
}

void submeter_heap_acima(MinHeap *heap, int idx) {
    while (idx > 0 && heap->dados[idx].distancia < heap->dados[(idx - 1) / 2].distancia) {
        trocar_nos(heap, idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

bool esta_no_min_heap(MinHeap *heap, int vertice) {
    return heap->posicao[vertice] < heap->tamanho && heap->posicao[vertice] != -1;
}

void inserir_min_heap(MinHeap *heap, int vertice, int distancia) {
    if (heap->tamanho == heap->capacidade) return;

    int i = heap->tamanho;
    heap->dados[i].vertice = vertice;
    heap->dados[i].distancia = distancia;
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

void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia) {
    int i = heap->posicao[vertice];
    if (i == -1) return;

    heap->dados[i].distancia = nova_distancia;
    submeter_heap_acima(heap, i);
}

void liberar_min_heap(MinHeap *heap) {
    if (!heap) return;
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    MinHeap *heap = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        pred[v] = -1;
        inserir_min_heap(heap, v, dist[v]);
    }

    dist[origem] = 0;
    diminuir_chave(heap, origem, dist[origem]);

    while (heap->tamanho > 0) {
        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        if (dist[u] == INF) break;

        NoAresta *aresta = g->listas[u];
        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;

            if (esta_no_min_heap(heap, v) && dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
                diminuir_chave(heap, v, dist[v]);
            }
            aresta = aresta->proximo;
        }
    }

    liberar_min_heap(heap);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (origem == destino) {
        printf("%d", origem);
        return;
    }

    if (pred[destino] == -1) {
        printf("Sem caminho de %d para %d\n", origem, destino);
        return;
    }

    int *caminho = (int*) malloc((destino + 1) * sizeof(int));
    int tam = 0;
    int atual = destino;

    while (atual != -1) {
        caminho[tam++] = atual;
        atual = pred[atual];
    }

    for (int i = tam - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    free(caminho);
}