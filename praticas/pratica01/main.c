#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    int n = 5;

    
    printf("== Matriz =\n");
    GrafoMatriz *gm = criar_grafo_matriz(n);
    inserir_aresta_matriz(gm, 0, 1);
    inserir_aresta_matriz(gm, 0, 2);
    inserir_aresta_matriz(gm, 1, 3);

    imprimir_matriz(gm); 

    printf("0 e 1 sao adjacentes? %s\n", sao_adjacentes_matriz(gm, 0, 1) ? "Sim" : "Nao");
    printf("Grau do vertice 0: %d\n", grau_matriz(gm, 0));

    remover_aresta_matriz(gm, 0, 1);
    printf("\nApos remover a aresta (0,1):\n");
    imprimir_matriz(gm); 

    liberar_grafo_matriz(gm);

    printf("== Lista ==\n");
    GrafoLista *gl = criar_grafo_lista(n);
    inserir_aresta_lista(gl, 0, 1);
    inserir_aresta_lista(gl, 0, 2);
    inserir_aresta_lista(gl, 1, 3);

    imprimir_lista(gl); 

    liberar_grafo_lista(gl);

    return 0;
}