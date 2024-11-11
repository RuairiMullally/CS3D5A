#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Tree_Node* create_node(char data);

void tree_insert ( Tree_Node** root, char data ) {

    Tree_Node* current = (*root);
    Tree_Node* previous = current;

    Tree_Node* insert = create_node(data);

    if(current == NULL){
        *root = insert;
        return;
    }

    while(current != NULL){
        previous = current;
        if(current->data < data){
            current = current->left;
        }else if(current->data > data){
            current = current->right;
        }
    }    

    if(current->data < data){
            previous->left = insert;
    }else if(current->data > data){
        previous->right = insert;
    }

}

Tree_Node* create_bst (char data[]){
    // TODO
}

Tree_Node* tree_search(Tree_Node* root, char data){
    //TODO
    return NULL;
}

void tree_print_sorted(Tree_Node* root){
    //TODO
}

void tree_delete(Tree_Node* root){
    //TODO
}

Tree_Node* create_node(char data) {
    Tree_Node* new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/*
    Tree_Node* current = root;
    Tree_Node* insert_node = create_node(data);

    if(current == NULL){
        current = insert_node;
    }

    while(current != NULL){
        if(current->data > data){
            if(current->left == NULL){
                current->left = insert_node;
                return;
            }
            current = current->left;
        }else if(current-> data < data){
            if(current->right == NULL){
                current->right = insert_node;
                return;
            }
            current = current->right;
        }else {
            return;
        }
    }
*/