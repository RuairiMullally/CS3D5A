#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int main(){
    char data[] = {'F','L','O','C','C','I','N','A','U','C','I','N','I','H','I','L','I','P','I','L','I','F','I','C','A','T','I','O','N'};
    //char data[] = {'D', 'B', 'A', 'C', 'F', 'E', 'G'};
    Tree_Node* tree = create_bst(data);
    tree_print_sorted(tree);
    Tree_Node* result = tree_search(tree, 'N');
    printf("True: %c ", result->data);
    tree_delete(tree);
    return 0;
}


