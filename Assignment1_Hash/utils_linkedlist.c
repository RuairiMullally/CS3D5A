#define MAX_STRING_LEN 20



typedef struct node{// node in linked list contains the information of 1 person
    int person_id;
    char deposition_id[MAX_STRING_LEN];
    char surname[MAX_STRING_LEN];
    char forename[MAX_STRING_LEN];
    int age;
    char person_type[MAX_STRING_LEN];
    char gender[MAX_STRING_LEN];
    char nationality[MAX_STRING_LEN];
    char religion[MAX_STRING_LEN];
    char occupation[MAX_STRING_LEN];

    Node* next;
}Node;

typedef struct person{// element in array which contains the pointer to the beginning of the linked list
    node* head;
}person;



