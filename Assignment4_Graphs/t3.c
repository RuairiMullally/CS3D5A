#ifndef MAX_STR_LEN
#define MAX_STR_LEN 100
#endif
#include "t3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

VertexInfo* create_vertex(FILE* csv, char* buffer, int max_field_len, int* field_return);
int next_field(FILE *csv, char *buffer, int max_len);
void add_edge(Graph *g, int from, int to, int weight);
Graph* create_graph(int num_nodes);
int get_vertex_index(int vertex_id, VertexInfo* vertices, Graph* g);
int get_min_distance(Graph* g, int* distance, bool* visited, int* min_val);


int load_edges ( char *fname , Graph* g, VertexInfo* vertices){
    FILE *csv = fopen(fname, "r"); // open CSV
    if (csv == NULL) { perror("Error opening vertices file!\n"); return -1; }
    
    char c;
    int lines = 0;
    for (c = getc(csv); c != EOF; c = getc(csv)){//count number of vertices
        if (c == '\n'){lines++;}
    }
    rewind(csv);

    char buffer[MAX_STR_LEN];
    int field_return;

    fgets(buffer, sizeof(buffer), csv);

    for (int i = 0; i < lines; i++) {

        int i = 0;
        char field_buffer[MAX_STR_LEN];
        int vertex1, vertex2, weight;

        while (i < 3) {
            field_return = next_field(csv, field_buffer, MAX_STR_LEN);
            switch (i) {
                case 0: vertex1 = atoi(field_buffer); break; // Parse vertex1
                case 1: vertex2 = atoi(field_buffer); break; // Parse vertex2
                case 2: weight = atoi(field_buffer); break;  // Parse weight
            }
            i++;
        }
        //printf("%i %i %i", vertex1, vertex2, weight);
        add_edge(g, get_vertex_index(vertex1, vertices, g), get_vertex_index(vertex2, vertices, g), weight);
    }
    printf("Loaded %i Edges.\n", lines);
    return 1;
}
VertexInfo* load_vertices ( char *fname , Graph** g){
    FILE *csv = fopen(fname, "r"); // open CSV
    if (csv == NULL) { perror("Error opening vertices file!\n"); return NULL; }
    
    char c;
    int lines = 0;
    for (c = getc(csv); c != EOF; c = getc(csv)){//count number of vertices
        if (c == '\n'){lines++;}
    }
    rewind(csv);
    *g = create_graph(lines);

    char buffer[MAX_STR_LEN];
    int field_return;

    fgets(buffer, sizeof(buffer), csv);
    VertexInfo* vertices = (VertexInfo*)malloc(lines * sizeof(VertexInfo));

    for (int i = 0; i < lines; i++) {
        VertexInfo* vertex = create_vertex(csv, buffer, MAX_STR_LEN, &field_return);
        if (vertex == NULL) {
            perror("Error creating vertex");
            fclose(csv);
            free(vertices);
            return NULL;
        }
        vertices[i] = *vertex;
        free(vertex); // Free the temporary vertex created by create_vertex
    }
    printf("\nLoaded %i vertices.\n", lines);
    return vertices;
}

void shortest_path(Graph* g, VertexInfo* vertices, int start_id, int target_id){
    int start_index = get_vertex_index(start_id, vertices, g);
    int target_index = get_vertex_index(target_id, vertices, g);

    if (start_index == -1 || target_index == -1) {
        printf("Invalid start or target vertex ID.\n");
        return;
    }

    const int vertices_count = g->num_vertices;
    bool* visited = (bool*)calloc(vertices_count, sizeof(bool));
    int* distance = (int*)malloc(vertices_count * sizeof(int));  //shortest distances
    int* predecessor = (int*)malloc(vertices_count * sizeof(int)); //to reconstruct path
    int* path = (int*)malloc(vertices_count * sizeof(int)); //path reconstruction array


    //initialize
    for (int i = 0; i < vertices_count; i++) {
        distance[i] = INT_MAX;
        predecessor[i] = -1;
    }
    distance[start_index] = 0;

    for (int k = 0; k < vertices_count; k++) {
        // Find the vertex with the minimum distance
        int min_index = -1;
        int min_distance = INT_MAX;

        min_index = get_min_distance(g, distance, visited, &min_distance);

        if (min_index == -1) {
            break;
        }

        visited[min_index] = true;

        //update neighbour distances
        for (int j = 0; j < vertices_count; j++) {
            if (g->adj_matrix[min_index][j] > 0 && !visited[j] &&
                distance[min_index] + g->adj_matrix[min_index][j] < distance[j]) {
                distance[j] = distance[min_index] + g->adj_matrix[min_index][j];
                predecessor[j] = min_index;
            }
        }
    }

    //print the shortest path if it exists
    if (distance[target_index] == INT_MAX) {
        printf("No path between %s and %s.\n",
               vertices[start_index].name, vertices[target_index].name);
    } else {
        printf("Shortest path from %s to %s (distance: %d):\n",
               vertices[start_index].name, vertices[target_index].name, distance[target_index]);

        //reconstruct path
        int current = target_index;
        int path_length = 0;

        while (current != -1) {
            path[path_length++] = current;
            current = predecessor[current];
        }

        //print path in reverse
        for (int i = path_length - 1; i >= 0; i--) {
            printf("%-10d %-30s %-12.8f %-12.8f\n",
                vertices[path[i]].stop_id,
                vertices[path[i]].name,
                vertices[path[i]].latitude,
                vertices[path[i]].longitude);
        }
        printf("\n");
    }

    //free allocated memory
    free(visited);
    free(distance);
    free(predecessor);
    free(path);
} 

void free_memory (Graph* graph, VertexInfo* vertices){

    if (graph != NULL) {
        for (int i = 0; i < graph->num_vertices; i++) {
            free(graph->adj_matrix[i]);
        }
        free(graph->adj_matrix);
        free(graph);
        graph = NULL; 
    }

    if (vertices != NULL) {
        free(vertices);
        vertices = NULL;
    }
    printf("Memory successfully freed.\n");
}


VertexInfo* create_vertex(FILE* csv, char* buffer, int max_field_len, int* field_return){
    VertexInfo* vertex = (VertexInfo*)malloc(sizeof(VertexInfo));
    int i = 0;

    do {
        *field_return = next_field(csv, buffer, max_field_len);

        switch (i) {
            case 0: vertex->stop_id = atoi(buffer); break;
            case 1: strcpy(vertex->name, buffer); break; //copy buffer into string
            case 2: vertex->latitude = atof(buffer); break;
            case 3: vertex->longitude = atof(buffer); break;
        }
        i++;
    } while (i < 4);

    return vertex;
}


int next_field(FILE *csv, char *buffer, int max_len) {//reads next CSV
    for (int n = 0; n < max_len; n++) { // clear the buffer from previous use
        buffer[n] = ' ';
    }
    buffer[max_len - 1] = '\0'; // null terminate buffer

    int i = 0;
    static int inside = 0;//static so it keeps track of changing ""
    
    if (csv == NULL) return -1; // check if the file is valid

    while (i < max_len - 1) { // prevent buffer overflow
        char buff = fgetc(csv);
        if (buff == EOF){
            buffer[i] = '\0';
            return -1; // end of file
        } 

        if ((buff == '"') && inside == 0) { // handle quotes cant believe no bools in C!!!!
            inside = 1;
        } else if ((buff == '"') && inside == 1) {
            inside = 0;
        }

        if (buff == '\n') {
            buffer[i] = '\0'; 
            return 1; // end of entry
        } else if (buff == ',' && inside == 0) {
            buffer[i] = '\0'; 
            return 0; // end of field
        } else if (buff != '"') {
            buffer[i] = buff; 
            i++;
        }
    }

    buffer[i] = '\0'; 
    return 0;
}

void add_edge(Graph *g, int from, int to, int weight){
    if(from < 0 ||from >= g->num_vertices || to < 0 || to >= g->num_vertices){
        printf("Invalid edge from %i to %i.\n", from, to);
        return;
    }
    g->adj_matrix[from][to] = weight;
    g->adj_matrix[to][from] = weight;

}

Graph* create_graph(int num_nodes){
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    new_graph->num_vertices = num_nodes;

    new_graph->adj_matrix = (int**)malloc(num_nodes * sizeof(int*));
    for(int i = 0; i < num_nodes; i++){
        new_graph->adj_matrix[i] = (int*)calloc(num_nodes, sizeof(int));
    }
    return new_graph;
}

int get_vertex_index(int vertex_id, VertexInfo* vertices, Graph* g){
    for(int i = 0; i < g->num_vertices; i++){
        if(vertex_id == vertices[i].stop_id){
            return i;
        }
    }
    return -1;
}

int get_min_distance(Graph* g, int* distance, bool* visited, int* min_val){

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
    *min_val = min;

    if(min_index >= 0){
        return min_index;
    }else{
        return - 1;
    }

}
