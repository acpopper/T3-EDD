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
    if(subsets[i].parent != i){
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset* subsets, int x, int y, int* cdreps, int index_centro){
    int xroot = x;
    int yroot = y;
 
    if(subsets[xroot].rank < subsets[yroot].rank){
        subsets[xroot].parent = yroot;
        if(index_centro!=-1){
            cdreps[index_centro] = yroot;
        }
        
    }
    else if(subsets[xroot].rank > subsets[yroot].rank){
        subsets[yroot].parent = xroot;
        if(index_centro!=-1){
            cdreps[index_centro] = xroot;
        }
    }   
    else{
        subsets[yroot].parent = xroot;
        if(index_centro!=-1){
            cdreps[index_centro] = yroot;
        }
        subsets[xroot].rank++;
    }
}
// Usada en quicksort
int comparar(const void* a, const void* b){
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

void ModifiedKruskal(Graph* graph, int n_clientes, FILE* output){
    int V = graph->V;
    Edge* result = malloc(V*sizeof(Edge));
    int e = 0;
    int i = 0;
    // printf("Cantidad cd's %i\n", V-n_clientes);
    int cdreps[V - n_clientes];
    for(int i=0; i<(V-n_clientes); i++){
        cdreps[i] = n_clientes+i;
    }

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), comparar);
    // for(int i=0; i<graph->E; i++){
    //     printf("%i %i %i\n", graph->edges[i].src, graph->edges[i].dest, graph->edges[i].weight);
    // }

    // Instancio los conjuntos disjuntos como vertices individuales
    Subset* subsets = malloc(V*sizeof(Subset));
    for(int v = 0; v < V; v++){
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Mientras falten clientes por asignar y el grafo siga teniendo edges
    while(e < n_clientes && i < graph->E){
        // printf("e:%i ncl:%i i:%i E:%i\n", e, n_clientes , i, graph->E);
        Edge next_edge = graph->edges[i];
        i+=1;
        int x = find(subsets, next_edge.src); //Recordar que find encuentra el representante
        int y = find(subsets, next_edge.dest);
        
        // Si edge no forma ciclo (distinto representante),
        // y si por lo menos un vertice no pertenece al mismo conjunto que algun centro (representante distinto que algun centro),
        // entonces se agrega edge a MST
        bool x_asignado = false;
        bool y_asignado = false;
        int index_centro = -1;
        for(int i=0; i<(V - n_clientes); i++){
            if(x == cdreps[i]){
                x_asignado = true;
                index_centro = i;
            }
            if(y == cdreps[i]){
                y_asignado = true;
                index_centro = i;
            }
        }
        // printf("src %i rep %i dest %i rep %i\n", next_edge.src, x, next_edge.dest, y);
        // printf("xas %i yas %i\n", x_asignado, y_asignado);
        
        if(x != y && (!x_asignado || !y_asignado)){
            // printf("Entra\n");
            result[e] = next_edge;
            e+=1;
            // Se unen los vertices 
            Union(subsets, x, y, cdreps, index_centro);
        }
        // printf("\n");
        // Else discard the next_edge
    }

    int minimumCost = 0;
    for (i = 0; i < e; ++i){
        minimumCost += result[i].weight;
    }
    fprintf(output, "%i\n", minimumCost);
    for (i = 0; i < e; ++i){
        fprintf(output, "%i\n", result[i].orden);
    }

    // Retornamos el array de edges
    // printf("Returning MST\n");
    free(subsets);
    free(result);
    return;
}

void destroy_graph(Graph* graph){
    free(graph->edges);
    free(graph);
}