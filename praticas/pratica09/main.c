#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

int main(void) {
    srand(42);
    int tamanhos[] = {5, 8, 10, 12, 15};
    int n_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("=== Experimento: Cobertura de Vertices ===\n\n");
    printf("%-5s | %-10s | %-14s | %-10s | %-14s\n", "N", "Tam BT", "Tempo BT(ms)", "Tam Guloso", "Tempo Gul(ms)");
    printf("-------------------------------------------------------------------\n");

    for (int t = 0; t < n_testes; t++) {
        int n = tamanhos[t];
        Grafo *g = gerar_grafo_aleatorio(n, 0.5);

        int *cobertura_bt = (int*) calloc(n, sizeof(int));
        int *cobertura_atual = (int*) calloc(n, sizeof(int));
        int tam_bt = n + 1;

        clock_t inicio_bt = clock();
        cobertura_minima_bt(g, 0, cobertura_atual, 0, cobertura_bt, &tam_bt);
        clock_t fim_bt = clock();
        double tempo_bt = ((double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC) * 1000.0;

        int *cobertura_gulosa_arr = (int*) calloc(n, sizeof(int));
        clock_t inicio_gul = clock();
        int tam_guloso = cobertura_gulosa(g, cobertura_gulosa_arr);
        clock_t fim_gul = clock();
        double tempo_gul = ((double)(fim_gul - inicio_gul) / CLOCKS_PER_SEC) * 1000.0;

        printf("%-5d | %-10d | %-14.4f | %-10d | %-14.4f\n", n, tam_bt, tempo_bt, tam_guloso, tempo_gul);

        free(cobertura_bt);
        free(cobertura_atual);
        free(cobertura_gulosa_arr);
        liberar_grafo(g);
    }

    return 0;
}