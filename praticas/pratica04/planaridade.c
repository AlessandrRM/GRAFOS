#include "planaridade.h"

static const int k5_u[10] = {0, 0, 0, 0, 1, 1, 1, 2, 2, 3};
static const int k5_v[10] = {1, 2, 3, 4, 2, 3, 4, 3, 4, 4};

static const int k33_a[9] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
static const int k33_b[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

static bool dfs_path_k5(int pair_idx, int curr, int target, int used_nodes, int *b, int mat[10][10], int n);

static bool solve_k5_pairs(int pair_idx, int used_nodes, int *b, int mat[10][10], int n) {
    if (pair_idx == 10) return true;
    int u = b[k5_u[pair_idx]];
    int v = b[k5_v[pair_idx]];
    return dfs_path_k5(pair_idx, u, v, used_nodes, b, mat, n);
}

static bool dfs_path_k5(int pair_idx, int curr, int target, int used_nodes, int *b, int mat[10][10], int n) {
    if (curr == target) {
        return solve_k5_pairs(pair_idx + 1, used_nodes, b, mat, n);
    }
    for (int next = 0; next < n; next++) {
        if (!mat[curr][next]) continue;
        if (next == target) {
            if (dfs_path_k5(pair_idx, next, target, used_nodes, b, mat, n)) return true;
        } else {
            if (used_nodes & (1 << next)) continue;
            bool is_branch = false;
            for (int i = 0; i < 5; i++) {
                if (b[i] == next) {
                    is_branch = true;
                    break;
                }
            }
            if (is_branch) continue;
            if (dfs_path_k5(pair_idx, next, target, used_nodes | (1 << next), b, mat, n)) return true;
        }
    }
    return false;
}

static bool tem_k5_subdivisao(int mat[10][10], int n) {
    if (n < 5) return false;
    int b[5];
    for (b[0] = 0; b[0] < n; b[0]++) {
        for (b[1] = b[0] + 1; b[1] < n; b[1]++) {
            for (b[2] = b[1] + 1; b[2] < n; b[2]++) {
                for (b[3] = b[2] + 1; b[3] < n; b[3]++) {
                    for (b[4] = b[3] + 1; b[4] < n; b[4]++) {
                        if (solve_k5_pairs(0, 0, b, mat, n)) return true;
                    }
                }
            }
        }
    }
    return false;
}

static bool dfs_path_k33(int pair_idx, int curr, int target, int used_nodes, int *a, int *b, int mat[10][10], int n);

static bool solve_k33_pairs(int pair_idx, int used_nodes, int *a, int *b, int mat[10][10], int n) {
    if (pair_idx == 9) return true;
    int u = a[k33_a[pair_idx]];
    int v = b[k33_b[pair_idx]];
    return dfs_path_k33(pair_idx, u, v, used_nodes, a, b, mat, n);
}

static bool dfs_path_k33(int pair_idx, int curr, int target, int used_nodes, int *a, int *b, int mat[10][10], int n) {
    if (curr == target) {
        return solve_k33_pairs(pair_idx + 1, used_nodes, a, b, mat, n);
    }
    for (int next = 0; next < n; next++) {
        if (!mat[curr][next]) continue;
        if (next == target) {
            if (dfs_path_k33(pair_idx, next, target, used_nodes, a, b, mat, n)) return true;
        } else {
            if (used_nodes & (1 << next)) continue;
            bool is_branch = false;
            for (int i = 0; i < 3; i++) {
                if (a[i] == next || b[i] == next) {
                    is_branch = true;
                    break;
                }
            }
            if (is_branch) continue;
            if (dfs_path_k33(pair_idx, next, target, used_nodes | (1 << next), a, b, mat, n)) return true;
        }
    }
    return false;
}

static bool tem_k33_subdivisao(int mat[10][10], int n) {
    if (n < 6) return false;
    int a[3], b[3];
    for (int i = 0; i < (1 << n); i++) {
        int cnt = 0;
        for (int k = 0; k < n; k++) if ((i >> k) & 1) cnt++;
        if (cnt != 3) continue;
        int idx_a = 0;
        for (int k = 0; k < n; k++) if ((i >> k) & 1) a[idx_a++] = k;

        for (int j = 0; j < (1 << n); j++) {
            if (i & j) continue;
            int cnt_b = 0;
            for (int k = 0; k < n; k++) if ((j >> k) & 1) cnt_b++;
            if (cnt_b != 3) continue;
            int idx_b = 0;
            for (int k = 0; k < n; k++) if ((j >> k) & 1) b[idx_b++] = k;

            if (solve_k33_pairs(0, 0, a, b, mat, n)) return true;
        }
    }
    return false;
}

bool eh_planar_euler(GrafoLista *g) {
    int n = g->num_vertices;
    int m = 0;
    for (int i = 0; i < n; i++) {
        No *adj = g->listas[i];
        while (adj) {
            m++;
            adj = adj->prox;
        }
    }
    m /= 2;

    if (n <= 2) return true;
    return m <= (3 * n - 6);
}

bool eh_planar(GrafoLista *g) {
    if (!eh_planar_euler(g)) return false;

    int n = g->num_vertices;
    if (n > 10) return true;

    int mat[10][10] = {{0}};
    for (int i = 0; i < n; i++) {
        No *adj = g->listas[i];
        while (adj) {
            if (adj->vertice < 10) {
                mat[i][adj->vertice] = 1;
            }
            adj = adj->prox;
        }
    }

    if (tem_k5_subdivisao(mat, n)) return false;
    if (tem_k33_subdivisao(mat, n)) return false;

    return true;
}