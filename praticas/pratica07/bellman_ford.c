#include "bellman_ford.h"

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

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;
            NoAresta *aresta = g->listas[u];
            while (aresta != NULL) {
                int v = aresta->destino;
                int peso = aresta->peso;
                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }
                aresta = aresta->proximo;
            }
        }
    }

    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;
        NoAresta *aresta = g->listas[u];
        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;
            if (dist[u] + peso < dist[v]) {
                reconstruir_ciclo_negativo(v, pred, V);
                return 0;
            }
            aresta = aresta->proximo;
        }
    }

    return 1;
}

void reconstruir_ciclo_negativo(int vertice_ciclo, int *pred, int V) {
    int v = vertice_ciclo;
    for (int i = 0; i < V; i++) {
        v = pred[v];
    }

    int *ciclo = (int*) malloc((V + 1) * sizeof(int));
    int tam = 0;
    int inicio = v;

    ciclo[tam++] = v;
    v = pred[v];

    while (v != inicio && tam <= V) {
        ciclo[tam++] = v;
        v = pred[v];
    }
    ciclo[tam++] = inicio;

    printf("Ciclo de custo negativo detectado: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d", ciclo[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    free(ciclo);
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