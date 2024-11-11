#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

void inorder(struct Tree_Node* root);

int main(){
    char data[] = {'F','L','O','C','C','I','N','A','U','C','I','N','I','H','I','L','I','P','I','L','I','F','I','C','A','T','I','O','N'};

    Tree_Node* root = NULL;

    // Characters to insert into the BST
    char elements[] = {'D', 'B', 'A', 'C', 'F', 'E', 'G'};
    int n = sizeof(elements) / sizeof(elements[0]);

    // Insert each character
    for (int i = 0; i < n; i++) {
        tree_insert(&root, elements[i]);
    }

    inorder(root);

    return 0;
}

void inorder(Tree_Node* root) {
    if (root != NULL) {
        inorder((root)->left);
        printf("%c ", (root)->data);
        inorder((root)->right);
    }
}
