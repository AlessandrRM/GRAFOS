#include <stdio.h>
#include "grafo_matriz.h"

int main() {
    int numero_vertices = 0;
    
    GrafoMatriz grafo;
    inicializer(&grafo, numero_vertices);

    exibir_matriz(&grafo);

    inserir_aresta(&grafo, 0, 1);
    inserir_aresta(&grafo, 0, 2);
    inserir_aresta(&grafo, 0, 3);
    inserir_aresta(&grafo, 1, 4);
    inserir_aresta(&grafo, 1, 5);
    inserir_aresta(&grafo, 2, 3);
    inserir_aresta(&grafo, 2, 6);
    inserir_aresta(&grafo, 3, 6);
    inserir_aresta(&grafo, 7, 4);
    inserir_aresta(&grafo, 7, 5);
    inserir_aresta(&grafo, 7, 6);

    printf("Matriz de Adjacência:\n");
    exibir_matriz(&grafo);

    return 0;
}