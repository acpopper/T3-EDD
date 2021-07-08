#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma once

typedef struct edge {
    int src;
    int dest;
    int weight;
    int orden;
} Edge;

typedef struct graph {
    int V, E;
    Edge* edges;
} Graph;

typedef struct subset {
    int rep;
    int rango;
} Subset;

Graph* init_Graph(int V, int E);
int find(Subset* subsets, int i);
void Union(Subset* subsets, int x, int y, int* cdreps, int index_centro);
int comparar(const void* a, const void* b);
void ModifiedKruskal(Graph* graph, int n_clientes, FILE* output);
void destroy_graph(Graph* graph);