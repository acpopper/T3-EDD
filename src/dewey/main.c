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

    int V = n_clientes+n_cd;
    int E = n_edges;
    Graph* graph = init_Graph(V, E);

    int* inicio = malloc(E*sizeof(int));
    int* destino = malloc(E*sizeof(int));
    int* costo = malloc(E*sizeof(int));
    for(int i = 0; i < E; i++){
        fscanf(input_file, "%i", &inicio[i]);
        fscanf(input_file, "%i", &destino[i]);
        fscanf(input_file, "%i", &costo[i]);
    }
    for(int i = 0; i < E; i++){
        graph->edges[i].src = inicio[i];
        graph->edges[i].dest = destino[i];
        graph->edges[i].weight = costo[i];
        graph->edges[i].orden = i;
    }
    
    // Aplicamos Kruskal modificado Kuchau!
    ModifiedKruskal(graph, n_clientes, output_file);
    
    // Destruimos nuestros sueños de la infancia
    destroy_graph(graph);
    // Cerramos archivos 
    fclose(input_file);
    fclose(output_file);
    // Liberamos la memoria restante
    free(inicio);
    free(destino);
    free(costo);
    // Terminamos exitosamente
    return 0;
}