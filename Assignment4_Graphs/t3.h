#ifndef T3_H_
#define T3_H_
#define MAX_STR_LEN 100

typedef struct Graph{
    int num_vertices;
    int** adj_matrix;
} Graph;

typedef struct {
    int stop_id;
    char name[MAX_STR_LEN];
    double latitude;
    double longitude;
} VertexInfo;

int load_edges ( char *fname, Graph* g, VertexInfo* vertices ); //loads the edges from the CSV file of name fname
VertexInfo* load_vertices ( char *fname , Graph** g);  //loads the vertices from the CSV file of name fname
void shortest_path(Graph* g, VertexInfo* vertices, int start_id, int target_id); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( Graph* graph, VertexInfo* vertices ) ; // frees any memory that was used

#endif