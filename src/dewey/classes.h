#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma once

typedef struct edge {
    int src, dest, weight;
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
void Union(Subset* subsets, int x, int y);
int comparar(const void* a, const void* b);
void KruskalMST(Graph* graph);