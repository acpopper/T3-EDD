#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma once

typedef struct edge {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct graph {
    int V, E;
    Edge* edges;
} Graph;

typedef struct subset {
    int parent;
    int rank;
} Subset;

Graph* createGraph(int V, int E);
int find(Subset* subsets, int i);
void Union(Subset* subsets, int x, int y, int* cdreps, int index_centro);
int comparar(const void* a, const void* b);
Edge* ModifiedKruskal(Graph* graph, int centros);
void destroy_graph(Graph* graph);