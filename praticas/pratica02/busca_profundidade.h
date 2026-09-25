#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "busca_largura.h"

typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

Pilha* criar_pilha(int capacidade);
void empilhar(Pilha *p, int v);
int desempilhar(Pilha *p);
bool pilha_vazia(Pilha *p);
void destruir_pilha(Pilha *p);

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *d, int *f, int *tempo);
int contar_componentes(GrafoLista *g);
bool tem_ciclo(GrafoLista *g);

#endif 