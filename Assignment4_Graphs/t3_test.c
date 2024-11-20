#include <stdio.h>
#include <stdlib.h>
#include "t3.h"
#include <stdio.h>


void print_graph(Graph* g){
    for(int i = 0; i < 20; i ++){
        printf("%i: ", i);
        for(int j = 0; j < 20; j++){
            printf("%i ", g->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

int main (int argc, char *argv[] ) {

    Graph* g;
    VertexInfo* vertices;

	if ( argc < 3 ) {
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if ( ! (vertices = (load_vertices( argv[1], &g) ))) {
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if ( !load_edges( argv[2], g, vertices) ) {
		printf("Failed to load edges\n");		
		return EXIT_FAILURE;
	}

	


    // get the start and end point
    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode);

    
    shortest_path(g, vertices, startingNode, endingNode);
    free_memory(g, vertices);

	return 1;
}