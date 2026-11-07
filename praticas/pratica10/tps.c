#include "tps.h"

MatrizDistancias* criar_matriz_distancias(int num_vertices) {
    MatrizDistancias *m = (MatrizDistancias*) malloc(sizeof(MatrizDistancias));
    m->num_vertices = num_vertices;
    m->custos = (int**) malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++) {
        m->custos[i] = (int*) calloc(num_vertices, sizeof(int));
    }
    return m;
}

void liberar_matriz_distancias(MatrizDistancias *m) {
    if (!m) return;
    for (int i = 0; i < m->num_vertices; i++) {
        free(m->custos[i]);
    }
    free(m->custos);
    free(m);
}

MatrizDistancias* gerar_matriz_aleatoria(int num_vertices) {
    MatrizDistancias *m = criar_matriz_distancias(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            int peso = 10 + rand() % 90;
            m->custos[i][j] = peso;
            m->custos[j][i] = peso;
        }
    }
    return m;
}

MatrizDistancias* grafo_para_tsp(Grafo *g) {
    int n = g->num_vertices;
    MatrizDistancias *m = criar_matriz_distancias(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                m->custos[i][j] = 0;
            } else if (g->matriz[i][j] == 1) {
                m->custos[i][j] = 1;
            } else {
                m->custos[i][j] = 2;
            }
        }
    }
    return m;
}

static void troar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void permutar_tsp(MatrizDistancias *m, int *p, int l, int r, int *min_custo, int *melhor_caminho) {
    if (l == r) {
        int custo_atual = 0;
        custo_atual += m->custos[0][p[0]];
        for (int i = 0; i < r; i++) {
            custo_atual += m->custos[p[i]][p[i + 1]];
        }
        custo_atual += m->custos[p[r]][0];

        if (custo_atual < *min_custo) {
            *min_custo = custo_atual;
            melhor_caminho[0] = 0;
            for (int i = 0; i <= r; i++) {
                melhor_caminho[i + 1] = p[i];
            }
            melhor_caminho[r + 2] = 0;
        }
        return;
    }

    for (int i = l; i <= r; i++) {
        troar(&p[l], &p[i]);
        permutar_tsp(m, p, l + 1, r, min_custo, melhor_caminho);
        troar(&p[l], &p[i]);
    }
}

int tsp_forca_bruta(MatrizDistancias *m, int *melhor_caminho) {
    int n = m->num_vertices;
    int *p = (int*) malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        p[i] = i + 1;
    }

    int min_custo = INF;
    permutar_tsp(m, p, 0, n - 2, &min_custo, melhor_caminho);

    free(p);
    return min_custo;
}

int tsp_vizinho_mais_proximo(MatrizDistancias *m, int origem, int *caminho) {
    int n = m->num_vertices;
    bool *visitado = (bool*) calloc(n, sizeof(bool));

    int atual = origem;
    caminho[0] = atual;
    visitado[atual] = true;
    int custo_total = 0;

    for (int step = 1; step < n; step++) {
        int proximo = -1;
        int min_d = INF;

        for (int v = 0; v < n; v++) {
            if (!visitado[v] && m->custos[atual][v] < min_d) {
                min_d = m->custos[atual][v];
                proximo = v;
            }
        }

        visitado[proximo] = true;
        caminho[step] = proximo;
        custo_total += min_d;
        atual = proximo;
    }

    caminho[n] = origem;
    custo_total += m->custos[atual][origem];

    free(visitado);
    return custo_total;
}

int tsp_insercao(MatrizDistancias *m, int *caminho) {
    int n = m->num_vertices;
    bool *no_subtour = (bool*) calloc(n, sizeof(bool));
    int *subtour = (int*) malloc((n + 1) * sizeof(int));
    int tam = 0;

    subtour[tam++] = 0;
    no_subtour[0] = true;

    int v_proximo = -1;
    int min_d = INF;
    for (int i = 1; i < n; i++) {
        if (m->custos[0][i] < min_d) {
            min_d = m->custos[0][i];
            v_proximo = i;
        }
    }
    subtour[tam++] = v_proximo;
    no_subtour[v_proximo] = true;
    subtour[tam++] = 0;

    while (tam < n + 1) {
        int k_melhor = -1;
        int dist_k = INF;

        for (int k = 0; k < n; k++) {
            if (no_subtour[k]) continue;
            for (int i = 0; i < tam - 1; i++) {
                if (m->custos[subtour[i]][k] < dist_k) {
                    dist_k = m->custos[subtour[i]][k];
                    k_melhor = k;
                }
            }
        }

        if (k_melhor == -1) break;

        int melhor_pos = -1;
        int min_inc = INF;

        for (int i = 0; i < tam - 1; i++) {
            int u = subtour[i];
            int v = subtour[i + 1];
            int inc = m->custos[u][k_melhor] + m->custos[k_melhor][v] - m->custos[u][v];
            if (inc < min_inc) {
                min_inc = inc;
                melhor_pos = i + 1;
            }
        }

        for (int i = tam; i > melhor_pos; i--) {
            subtour[i] = subtour[i - 1];
        }
        subtour[melhor_pos] = k_melhor;
        no_subtour[k_melhor] = true;
        tam++;
    }

    int custo_total = 0;
    for (int i = 0; i < n; i++) {
        caminho[i] = subtour[i];
        custo_total += m->custos[subtour[i]][subtour[i + 1]];
    }
    caminho[n] = subtour[n];

    free(no_subtour);
    free(subtour);
    return custo_total;
}