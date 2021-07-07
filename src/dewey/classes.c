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
    printf("1. i=%i\n", i);
    if(subsets[i].parent != i){
        printf("2. i=%i\n", i);
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    printf("3. i=%i\n", i);
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
    printf("Edges sorted\n");
    // Instancio los conjuntos disjuntos como vertices individuales
    Subset* subsets = malloc(V*sizeof(Subset));
    for(int v = 0; v < V; v++){
        // printf("subset v = %i\n", v);
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    // for(int v = 0; v < V; v++){
    //     printf("subset p %i r %i\n", subsets[v].parent, subsets[v].rank);
    // }
    // Se crean bien
    printf("Subsets created\n");
    // for(int j=0; j<graph->E; j++){
    //     printf("EDGE src %i dest %i costo %i\n", graph->edges[j].src, graph->edges[j].dest, graph->edges[j].weight);
    // }

    // Mientras los edges sean menor a V-1 y el grafo siga teniendo edges
    // while(e < V-1 && i < graph->E){
    //     // printf("e=%i i=%i\n", e, i);
    //     // Para cada edge, de menor a mayor, veo si forma ciclos o no
    //     Edge next_edge = graph->edges[i]; //Recordar que find encuentra el representante
    //     i+=1;
    //     printf("Find start\n");
    //     int x = find(subsets, next_edge.src);
    //     int y = find(subsets, next_edge.dest);
    //     printf("Find end\n");

    //     // Si edge no forma ciclo (distinto representante), se agrega
    //     if(x != y){
    //         result[e] = next_edge;
    //         e+=1;
    //         // Se unen los vertices 
    //         // Union(subsets, x, y);
    //     }
    //     // Else discard the next_edge
    // }

    // int minimumCost = 0;
    // for (i = 0; i < e; ++i){
    //     printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    //     minimumCost += result[i].weight;
    // }
    // printf("Minimum Cost Spanning tree : %d",minimumCost);

    // Retornamos el array de edges
    printf("Returning MST\n");
    free(subsets);
    return result;
}

void destroy_graph(Graph* graph){
    free(graph->edges);
    free(graph);
}