#include "classes.h"

// Creates a graph with V vertices and E edges
Graph* init_Graph(int V, int E){
  Graph* graph = malloc(sizeof(Graph));
  *graph = (Graph) {
    .V=V,
    .E=E,
    .edges=calloc(E, sizeof(Edge))
  };

  return graph;
}

int find(Subset* subsets, int i){
    if(subsets[i].rep != i){
        subsets[i].rep = find(subsets, subsets[i].rep);
    }
    return subsets[i].rep;
}

void Union(Subset* subsets, int x, int y, int* cdreps, int index_centro){
    if(subsets[x].rango < subsets[y].rango){
        subsets[x].rep = y;
        if(index_centro!=-1){
            cdreps[index_centro] = y;
        }
        
    }
    else if(subsets[x].rango > subsets[y].rango){
        subsets[y].rep = x;
        if(index_centro!=-1){
            cdreps[index_centro] = x;
        }
    }   
    else{
        subsets[y].rep = x;
        if(index_centro!=-1){
            cdreps[index_centro] = x;
        }
        subsets[x].rango++;
    }
}
// Usada en quicksort, extraida de GeeksforGeeks
int comparar(const void* a, const void* b){
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

// Funcion adaptada de GeeksforGeeks
void ModifiedKruskal(Graph* graph, int n_clientes, FILE* output){
    int V = graph->V;
    Edge* result = malloc(V*sizeof(Edge));
    int e = 0; // Cantidad de clientes conectados a un CD
    int i = 0; // Por si nos pasamos de las aristas, termina el while
    
    int cdreps[V - n_clientes];
    for(int i=0; i<(V-n_clientes); i++){
        cdreps[i] = n_clientes+i;
    }

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), comparar);

    // Instancio los conjuntos disjuntos como vertices individuales
    Subset* subsets = malloc(V*sizeof(Subset));
    for(int v = 0; v < V; v++){
        subsets[v].rep = v;
        subsets[v].rango = 0;
    }

    // Mientras falten clientes por asignar y el grafo siga teniendo edges
    while(e < n_clientes && i < graph->E){
        Edge next_edge = graph->edges[i];
        i+=1;
        int x = find(subsets, next_edge.src); //Recordar que find encuentra el representante
        int y = find(subsets, next_edge.dest);
        
        // Vemos si origen y/o destino ya estan conectados a algun CD
        // Aprovechamos de rescatar el indice del CD para nuestro arreglo
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
        // Si por lo menos alguno de los conjuntos le falta conectarse a un CD (su representante no calza con nuestro arreglo 
        // de CD's),
        // O bien si ambos no forman ciclos (representantes distintos)
        // Se agrega al resultado del MST
        if(x != y && (!x_asignado || !y_asignado)){
            result[e] = next_edge;
            e+=1;
            // Se unen los conjuntos
            Union(subsets, x, y, cdreps, index_centro);
        }
    }
    // Escribimos el output
    int costofinal = 0;
    for (i = 0; i < e; ++i){
        costofinal += result[i].weight;
    }
    fprintf(output, "%i\n", costofinal);
    for (i = 0; i < e; ++i){
        fprintf(output, "%i\n", result[i].orden);
    }

    // Liberamos la memoria una vez escrito el output
    free(subsets);
    free(result);
    return;
}

void destroy_graph(Graph* graph){
    free(graph->edges);
    free(graph);
}