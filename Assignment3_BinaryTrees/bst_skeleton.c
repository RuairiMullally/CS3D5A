#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
Tree_Node* create_node(char data);

void tree_insert(Tree_Node** root, char data){
    Tree_Node* current = (*root);
    Tree_Node* previous = current;

    Tree_Node* insert = create_node(data);

    while(current != NULL){
        previous = current;
        if(current->data > data){
            current = current->left;
        }else if(current->data < data){
            current = current->right;
        }else if(current-> data == data){
            break;
        }
    }

    if(previous == NULL){
        *root = insert;
        return;
    }else if(previous->data > data){
        previous->left = insert;
    }else if(previous->data < data){
        previous->right = insert;
    }
}

Tree_Node* create_bst (char data[]){
    Tree_Node* root = NULL;
    // Insert each character
    for (int i = 0; data[i] != '\0' ; i++) {
        tree_insert(&root, data[i]);
    }
    return root;
}

Tree_Node* tree_search(Tree_Node* root, char data){
    while(root != NULL){
        if(root->data == data){
            return root;
        }else if(data > root->data){
            root = root->right;
        }else if(data < root->data){
            root = root->left;
        }
    }
    return NULL;
}

void tree_print_sorted(Tree_Node* root){
    if (root == NULL) {
        return;
    }
    tree_print_sorted((root)->left);
    printf("%c ", (root)->data);
    tree_print_sorted((root)->right);
}

void tree_delete(Tree_Node* root){
    if (root == NULL) {
        return;
    }
    tree_delete((root)->left);
    tree_delete((root)->right);
    free(root);

}

Tree_Node* create_node(char data){
    Tree_Node* new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
