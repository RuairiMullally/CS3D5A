#include "t2.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

static char val2char(int val);
int get_min_distance(Graph* g, int* distance, bool* visited);

Graph* create_graph(int num_nodes){
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    new_graph->num_vertices = num_nodes;

    new_graph->adj_matrix = (int**)malloc(num_nodes * sizeof(int*));
    for(int i = 0; i < num_nodes; i++){
        new_graph->adj_matrix[i] = (int*)calloc(num_nodes, sizeof(int));
    }
    return new_graph;
}

void add_edge(Graph *g, int from, int to, int weight){
    if(from < 0 ||from >= g->num_vertices || to < 0 || to >= g->num_vertices){
        printf("Invalid edge from %i to %i.\n", from, to);
        return;
    }
    g->adj_matrix[from][to] = weight;
    g->adj_matrix[to][from] = weight;

}

void print_graph(Graph* g){
    for(int i = 0; i < g->num_vertices; i ++){
        printf("%c: ", val2char(i));
        for(int j = 0; j < g->num_vertices; j++){
            printf("%i ", g->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(Graph* g, int origin){
    const int vertices = g->num_vertices;
    bool* visited = (bool*)calloc(vertices, sizeof(bool));
    int* distance = (int*)malloc(vertices * sizeof(int));

    distance[origin] = 0;
    for(int i = 1; i < vertices; i++){//initialize distance
        distance[i] = INT_MAX;
    }

    //find shortest path for all nodes 
    int min_index;
    printf("\nTraversal Order: ");
    for(int k = 0; k < vertices; k ++){
        min_index = get_min_distance(g, distance, visited);
    
        visited[min_index] = true;
        printf("%c ", val2char(min_index));

        //update adjacent vertex distances
        for(int j = 0; j < vertices; j++){
            if(g->adj_matrix[min_index][j] > 0 && !visited[j] && distance[min_index] != INT_MAX \
            && distance[min_index] + g->adj_matrix[min_index][j] < distance[j]){
                distance[j] = distance[min_index] + g->adj_matrix[min_index][j];
            }
        }
    }

    printf("\nVertex\tDistance from Source (%c)\n", val2char(origin));
    for (int i = 0; i < vertices; i++) {
        printf("%c\t%d\n", val2char(i), distance[i]);
    }

    free(distance);
    free(visited);
}

void delete_graph(Graph* g){
    if(g == NULL){
        return;
    }

    for(int i = 0; i <g->num_vertices; i++){
        free(g->adj_matrix[i]);
    }
    free(g->adj_matrix);
    free(g);
    printf("\nGraph deleted.\n");
}

static char val2char(int val){
    if (val < 0 || val > 25) {
        return '\0';
    }
    return 'A' + val;
}

int get_min_distance(Graph* g, int* distance, bool* visited){

    int min = INT_MAX;
    int min_index;

    for(int i = 0; i < g->num_vertices; i++){
        if(visited[i] == false && distance[i] <= min){
            if (distance[i] < min || min_index == -1 || i < min_index) {
                min = distance[i];
                min_index = i;
            }
        }
    }

    if(min_index >= 0){
        return min_index;
    }else{
        return - 1;
    }

}