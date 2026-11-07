#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

int main(void) {
    srand(42);
    int tamanhos[] = {5, 8, 10, 12};
    int n_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("=== Experimento: Caixeiro Viajante (TSP) ===\n\n");
    printf("%-4s | %-16s | %-16s | %-16s\n", "N", "FB (Custo/ms)", "VNP (Custo/ms)", "INS (Custo/ms)");
    printf("-----------------------------------------------------------------------\n");

    for (int t = 0; t < n_testes; t++) {
        int n = tamanhos[t];
        MatrizDistancias *m = gerar_matriz_aleatoria(n);

        int *cam_fb = (int*) malloc((n + 1) * sizeof(int));
        clock_t i_fb = clock();
        int c_fb = tsp_forca_bruta(m, cam_fb);
        clock_t f_fb = clock();
        double t_fb = ((double)(f_fb - i_fb) / CLOCKS_PER_SEC) * 1000.0;

        int *cam_vnp = (int*) malloc((n + 1) * sizeof(int));
        clock_t i_vnp = clock();
        int c_vnp = tsp_vizinho_mais_proximo(m, 0, cam_vnp);
        clock_t f_vnp = clock();
        double t_vnp = ((double)(f_vnp - i_vnp) / CLOCKS_PER_SEC) * 1000.0;

        int *cam_ins = (int*) malloc((n + 1) * sizeof(int));
        clock_t i_ins = clock();
        int c_ins = tsp_insercao(m, cam_ins);
        clock_t f_ins = clock();
        double t_ins = ((double)(f_ins - i_ins) / CLOCKS_PER_SEC) * 1000.0;

        printf("%-4d | %4d / %-8.2f | %4d / %-8.2f | %4d / %-8.2f\n",
               n, c_fb, t_fb, c_vnp, t_vnp, c_ins, t_ins);

        free(cam_fb);
        free(cam_vnp);
        free(cam_ins);
        liberar_matriz_distancias(m);
    }

    printf("\n=== Teste de Reducao: Caminho Hamiltoniano para TSP ===\n");
    int n_ham = 6;
    Grafo *g = gerar_grafo_aleatorio(n_ham, 0.6);
    int *caminho_ham = (int*) malloc(n_ham * sizeof(int));

    bool tem_ham = encontrar_caminho_hamiltoniano_bt(g, caminho_ham);
    printf("Grafo com N=%d possui Caminho Hamiltoniano? %s\n", n_ham, tem_ham ? "SIM" : "NAO");

    MatrizDistancias *m_red = grafo_para_tsp(g);
    int *cam_red = (int*) malloc((n_ham + 1) * sizeof(int));
    int c_red = tsp_forca_bruta(m_red, cam_red);
    printf("Custo minimo no TSP reduzido: %d\n", c_red);

    free(caminho_ham);
    free(cam_red);
    liberar_matriz_distancias(m_red);
    liberar_grafo(g);

    return 0;
}