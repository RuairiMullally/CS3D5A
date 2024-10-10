#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    struct node* next;
}node;

typedef struct person{// element in array which contains the pointer to the beginning of the linked list
    node* head;
}person;

int hash1(char* s, int array_len);
node* createNode(int number_fields, FILE* csv, char* buffer, int max_field_len);
int next_field(FILE *csv, char *buffer, int max_len);

int main(){
    person people[5];
    char buffer[20];
    FILE *csv = fopen("truncated.csv", "r"); // open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return -1; }
    node* n = createNode(10, csv, buffer, 20);
    people[4].head = n;

    int hash = hash1(people[4].head->surname, 5);

    return 0;
}

int hash1(char* s, int array_len){
    printf("\nhash1 %s", s);
    int hash = 0;

    while(*s){
        hash = (hash + (*s) - 'A') %  array_len;
        s++;
    }
    printf(" %i", hash);
    return hash;
}

int next_field(FILE *csv, char *buffer, int max_len) {
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

node* createNode(int number_fields, FILE* csv, char* buffer, int max_field_len){
    node* p = (node*)malloc(sizeof(node));
    p->next = NULL;
    int i = 0;
    int field_return;

    do{
        field_return = next_field(csv, buffer, max_field_len);

        if(field_return == -1){return NULL;}
        
        switch (i) {//allocate attribute into appropriate member
            case 0: p->person_id = atoi(buffer); break; //ascii to int
            case 1: strcpy(p->deposition_id, buffer); break; //copy buffer into string
            case 2: strcpy(p->surname, buffer); break;
            case 3: strcpy(p->forename, buffer); break;
            case 4: p->age = atoi(buffer); break;
            case 5: strcpy(p->person_type, buffer); break;
            case 6: strcpy(p->gender, buffer); break;
            case 7: strcpy(p->nationality, buffer); break;
            case 8: strcpy(p->religion, buffer); break;
            case 9: strcpy(p->occupation, buffer); break;
        }
        i++;
    }while(i < number_fields);

    return p;
}



