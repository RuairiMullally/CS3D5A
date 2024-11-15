#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//


typedef struct Tree_Node{
    int   doc_id;           // unique identifier for the document
	char *author;			// file name of the document 
    char *name;             // file name of the document    
    int   word_count;
    struct Tree_Node* left;
    struct Tree_Node* right;
} Tree_Node;

struct Tree_Node* root;//database root;
int g_num_comps;
int g_num_searches;
int g_num_insertions_attempted;
int g_num_tree_size;

Tree_Node* create_node(char *name, int word_count, char *author);
int id_creator(char *name, int word_count, char *author);
void bstdb_quit_helper(Tree_Node* previous);
int get_depth(Tree_Node* node);

int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	root = NULL;
	g_num_comps = 0;
	g_num_searches = 0;
	g_num_insertions_attempted = 0;
	g_num_tree_size = 0;
	return 1;
}

int
bstdb_add ( char *name, int word_count, char *author ) {
	// if(word_count <= 0){
	// 	printf("%i", word_count);
	// } there is a problem with the profiler where it sometimes supplies INT_MIN for the word_count
	// it is still inserted correctly but causes an error when it is returned from the search as
	// profiler defines errors as number < 0 
	
	
	g_num_insertions_attempted++;
    Tree_Node* insert = create_node(name, word_count, author);
	int id = -1;
	if(insert){
		 id = insert->doc_id;
		 Tree_Node* current = root;
		 Tree_Node* previous = root;
		 int probe_count = 0;

		while(current != NULL){
			previous = current;
			if(current->doc_id > id){
				current = current->left;
			}else if(current->doc_id < id){
				current = current->right;
			}else if(current->doc_id == id){
				probe_count++;
				id += probe_count; // Increment to probe for a new spot
				insert->doc_id = id;
				current = root; // Start search from the root again
				previous = NULL;
			}
		}

		if(previous == NULL){
			root = insert;
			g_num_tree_size++;
		}else if(previous->doc_id > id){
			previous->left = insert;
			g_num_tree_size++;
		}else if(previous->doc_id < id){
			previous->right = insert;
			g_num_tree_size++;
		}

	}
	if(id == -1){
		printf("ID:%i Name: %s\n", insert->doc_id, insert->name);
	}
	return id;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	g_num_searches++;
	Tree_Node* current = root;
	while(current != NULL){
		g_num_comps++;
        if(current->doc_id == doc_id){
            return current->word_count;
        }else if(doc_id > current->doc_id){
            current = current->right;
        }else if(doc_id < current->doc_id){
            current = current->left;
        }
    }
	printf("ID of missing Word Count Search:%i \n",doc_id);
	return -1;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	g_num_searches++;
	Tree_Node* current = root;
	while(current != NULL){
		g_num_comps++;
        if(current->doc_id == doc_id){
            return current->name;
        }else if(doc_id > current->doc_id){
            current = current->right;
        }else if(doc_id < current->doc_id){
            current = current->left;
        }
    }
	printf("ID of missing Word Name Search:%i \n",doc_id);
	return NULL;
}

void
bstdb_stat ( void ) {
	printf("STAT\n");
    printf("Avg nodes traversed per search  -> %lf\n", (double)g_num_comps/g_num_searches);
    printf("Tree size matches expected? -> %c\n",(( g_num_insertions_attempted == g_num_tree_size)? 'Y' : 'N') );
	printf("Insertions Attempted:%i  Tree Size:%i \n", g_num_insertions_attempted, g_num_tree_size);

	//compare left and right depth to illustrate level of balance
	printf("Left side depth:%i  Right side depth:%i \n", get_depth(root->left), get_depth(root->right));

}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	Tree_Node* start = root;
	bstdb_quit_helper(start);
	printf("BST freed.\n");
}

Tree_Node* create_node(char *name, int word_count, char *author){

    Tree_Node* new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
	size_t len_name;
	//size_t len_author;

	if(new_node){
		int id = id_creator(name, word_count, author);
		new_node->doc_id = id;
		new_node->word_count = word_count;
		new_node->left = NULL;
		new_node->right = NULL;

		len_name = strlen(name)+1;
        new_node->name = calloc(len_name, sizeof(char));
		//the author is always null in the profiler, so author is omitted
		// len_author = strlen(author)+1;
		// new_node->author = calloc(len_author, sizeof(char));
		new_node->author = NULL;

        if (new_node->name) {
            // if calloc was successful, copy the filename into the node
            strcpy( new_node->name, name );
			//the author is always null in the profiler, so author is omitted
			//strcpy( new_node->author, author );
        } else {
            // if calloc failed, release any memory that was allocated
			free(new_node);
            new_node = NULL;
        }
	}else{
		new_node = NULL;
	}
	return new_node;
}

int id_creator(char *name, int word_count, char *author){
	unsigned int id = 0;

	for(int i = 0; i < strlen(name); i ++){
		id = (31 * id + tolower(name[i]));
		//printf("\n %i", id);
	}

	id += word_count;
	
	int id_r = (int)id % INT_MAX;
	id_r = abs(id_r);
	return id_r;
}

void bstdb_quit_helper(Tree_Node* previous){
	Tree_Node* current = previous;
	if (current == NULL) {
        return;
    }
    bstdb_quit_helper((current)->left);
    bstdb_quit_helper((current)->right);
    free(current);
}

int get_depth(Tree_Node* node) {
    if (node == NULL) {
        return 0;
    }

    int left_depth = get_depth(node->left);
    int right_depth = get_depth(node->right);

    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}


    
