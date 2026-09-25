#ifndef DAG_H
#define DAG_H

typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct GrafoLista {
    int num_vertices;
    No **adj;
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
int eh_dag(GrafoLista *g);

#endif