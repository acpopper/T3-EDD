#include "classes.h"

// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E){
  Graph* graph = malloc(sizeof(Graph));
  *graph = (Graph) {
    .V=V,
    .E=E,
    .edges=calloc(E, sizeof(Edge))
  };

  return graph;
}

int find(Subset* subsets, int i){
    // printf("1. i=%i\n", i);
    if(subsets[i].parent != i){
        // printf("2. i=%i\n", i);
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    // printf("3. i=%i\n", i);
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

Edge* ModifiedKruskal(Graph* graph, int centros){
    int V = graph->V;
    Edge* result = malloc(V*sizeof(Edge));
    int e = 0;
    int i = 0;
    int clientes_listos = 0;
    // printf("Cantidad cd's %i\n", V-centros);
    int cd_represent[V - centros];
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), comparar);
    // printf("Edges sorted\n");
    // for(int i=0; i<graph->E; i++){
    //     printf("%i %i %i\n", graph->edges[i].src, graph->edges[i].dest, graph->edges[i].weight);
    // }
    // Instancio los conjuntos disjuntos como vertices individuales
    Subset* subsets = malloc(V*sizeof(Subset));
    for(int v = 0; v < V; v++){
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    // printf("Subsets created\n");

    // Mientras falten clientes por asignar y el grafo siga teniendo edges
    while(clientes_listos < centros && i < graph->E){
        Edge next_edge = graph->edges[i]; //Recordar que find encuentra el representante
        i+=1;
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // Si edge no forma ciclo (distinto representante),
        // O si por lo menos un vertice no pertenece al mismo conjunto que un centro (representante distinto que algun centro),
        // entonces se agrega
        if(x != y){
            result[e] = next_edge;
            e+=1;
            // Se unen los vertices 
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    int minimumCost = 0;
    for (i = 0; i < e; ++i){
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost Spanning tree : %d",minimumCost);

    // Retornamos el array de edges
    // printf("Returning MST\n");
    free(subsets);
    return result;
}

void destroy_graph(Graph* graph){
    free(graph->edges);
    free(graph);
}