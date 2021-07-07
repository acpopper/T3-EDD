#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "classes.h"


int main(int argc, char** argv)
{
    // Revisamos los argumentos
    if(argc != 3) {
        printf("Modo de uso: %s <network.txt> <output.txt>\n", argv[0]);
        return 1;
    }
    /* Abrimos el archivo de input */
    FILE *input_file = fopen(argv[1], "r");
    /* Abrimos el archivo de output */
    FILE *output_file = fopen(argv[2], "w");

    int n_clientes;
    fscanf(input_file, "%d", &n_clientes);
    int n_cd;
    fscanf(input_file, "%d", &n_cd);
    int n_edges;
    fscanf(input_file, "%d", &n_edges);

    // printf("%i %i %i\n", n_clientes, n_cd, n_edges);

    int V = n_clientes+n_cd;
    int E = n_edges;
    Graph* graph = createGraph(V, E);

    // int inicio;
    // int destino;
    // int costo;
    for (int i = 0; i < E; i++){
        fscanf(input_file, "%d", &graph->edges[i].src);
        fscanf(input_file, "%d", &graph->edges[i].dest);
        fscanf(input_file, "%d", &graph->edges[i].weight);
        // graph->edges[i].src = inicio;
        // graph->edges[i].dest = destino;
        // graph->edges[i].weight = costo;
        printf("%i %i %i\n", graph->edges[i].src, graph->edges[i].dest, graph->edges[i].weight);
    } //grafo se construye bien

    Edge* resultado = malloc((V-1)*sizeof(Edge));
    for(int j=0; j<graph->E; j++){
        printf("EDGE src %i dest %i costo %i\n", graph->edges[j].src, graph->edges[j].dest, graph->edges[j].weight);
    }
    printf("Iniciando Kruskal\n");
    KruskalMST(graph);
    printf("Destruyendo grafo...\n");
    destroy_graph(graph);
    free(resultado);
    fclose(input_file);
    fclose(output_file);
    // Terminamos exitosamente
    printf("Terminado sin errores\n");
    return 0;
}