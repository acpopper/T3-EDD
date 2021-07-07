#include "classes.h"

// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E){
    Graph* graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = malloc(sizeof(Edge));
    return graph;
}

int find(Subset* subsets, int i){
    if(subsets[i].parent != i){
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset* subsets, int x, int y){
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    if(subsets[xroot].rank < subsets[yroot].rank){
        subsets[xroot].parent = yroot;
    }
    else if(subsets[xroot].rank > subsets[yroot].rank){
        subsets[yroot].parent = xroot;
    }   
    else{
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
// Usada en quicksort
int comparar(const void* a, const void* b){
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

Edge* KruskalMST(Graph* graph){
    int V = graph->V;
    Edge* result = malloc(V*sizeof(Edge)); // This will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges
 
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), comparar);
 
    // Instancio los conjuntos disjuntos como vertices individuales
    Subset* subsets = malloc(V*sizeof(Subset));
    for(int v = 0; v < V; v++){
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Mientras los edges sean menor a V-1 y el grafo siga teniendo edges
    while(e < V-1 && i < graph->E){
        // Para cada edge, de menor a mayor, veo si forma ciclos o no
        Edge next_edge = graph->edges[i++]; //Recordar que find encuentra el representante
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
 
        // Si edge no forma ciclo (distinto representante), se agrega
        if(x != y){
            result[e++] = next_edge;
            // Se unen los vertices 
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    // int minimumCost = 0;
    // for (i = 0; i < e; ++i){
    //     printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    //     minimumCost += result[i].weight;
    // }
    // printf("Minimum Cost Spanning tree : %d",minimumCost);

    // Retornamos el array de edges
    free(subsets);
    return result;
}

void destroy_graph(Graph* graph){
    free(graph->edges);
    free(graph);
}