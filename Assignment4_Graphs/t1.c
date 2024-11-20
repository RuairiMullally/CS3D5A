#include "t1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void dfs_recursive(Graph* g, int origin, bool* visited);
static char val2char(int val);

node* create_node(int v){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}


Graph* create_graph(int num_nodes){ // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    new_graph->num_vertices = num_nodes;
    new_graph->adj_list = malloc(num_nodes * sizeof(node*));

    for(int i = 0; i < num_nodes; i++){
        new_graph->adj_list[i] = NULL;
    }
    return new_graph;

}
void add_edge(Graph *g, int from, int to){ // adds an un-directed edge
    node* insert_node = create_node(to);
    insert_node->next = g->adj_list[from];
    g->adj_list[from] = insert_node;

    // insert_node = create_node(from);
    // insert_node->next = g->adj_list[to];
    // g->adj_list[to] = insert_node;
}

void bfs(Graph* g, int origin){ //implements breath first search and prints the results
    //max is defined as length of graph
    const int maximum = g->num_vertices;
    int* queue = (int*)malloc(maximum * maximum * sizeof(int));
    int front = 0; 
    int back = 0;

    bool* visited = (bool*)calloc(maximum, sizeof(bool));
    visited[origin] = true;
    queue[back++] = origin;

    while(front < back){
        int head = queue[front++];
        printf("%c", val2char(head));

        node* current = g->adj_list[head];
        while(current != NULL){
            int neighbour = current->vertex;
            if(!visited[neighbour]){
                queue[back++] = neighbour;
                visited[neighbour] = true;
            }
            current = current->next;
        }
    }
}

void dfs(Graph* g, int origin){ //implements depth first search and prints the results
    const int maximum = g->num_vertices;
    bool* visited = (bool*)calloc(maximum, sizeof(bool));
    
    dfs_recursive(g, origin, visited);
    free(visited);

}

void dfs_recursive(Graph* g, int origin, bool* visited){
    visited[origin] = true;
    printf("%c", val2char(origin));
    node* head = g->adj_list[origin];
    while(head){
        int neighbour = head->vertex;
        if(!visited[neighbour]){
            dfs_recursive(g, neighbour, visited);
        }
        head = head->next;
    }
}

void print_graph(Graph* g){
    for(int i = 0; i < g->num_vertices; i++){
        node* head = g->adj_list[i];
        printf("Vertex %c: ", val2char(i));
        while(head){
            printf("%c -> ", val2char(head->vertex));
            head = head->next;
        }
        printf("NULL\n");
    }
}

static char val2char(int val){
    if (val < 0 || val > 25) {
        return '\0';
    }
    return 'A' + val;
}

void delete_graph(Graph* g){
    if(g == NULL){
        return;
    }

    for(int i = 0; i < g->num_vertices; i ++){
        node* head = g->adj_list[i];
        while(head){
            node* tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    free(g->adj_list);
    free(g);
    printf("\nGraph deleted.\n");
}
