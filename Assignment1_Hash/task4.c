#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_LEN 60209 // next prime that is large enough to hold our list
#define MAX_STRING_LEN 100

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
    struct node *next;

    //node* next;
}node;

typedef struct people{// element in array which contains the pointer to the beginning of the linked list
    node* head;
}people;

//functions
int next_field(FILE *csv, char *buffer, int max_len);
node* createNode(int number_fields, FILE* csv, char* buffer, int max_field_len, int* field_return);
void printNode(node* p);
void printTitle();
int hash1(char* s, int array_len);
int hash3(char* s, int array_len); 
int hashi(char* s, int array_len, int i);
int insertTermDHSurname(people* hash_table, node* n, int array_len, int* collisions, int* unique_collisions);

int main(){
    people hash_table[MAX_ARRAY_LEN];
    char buffer[MAX_STRING_LEN];
    int uniqueness;
    int collisions = 0;
    int unique_collisions = 0;
    int field_return;
    //initialize hash table
    for(int k = 0; k < MAX_ARRAY_LEN; k++){
        hash_table[k].head = NULL;
    }
    //open file
    FILE *csv = fopen("people.csv", "r"); // open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return -1; }

    int i = -1;
    do{
        node* n = createNode(10, csv, buffer, MAX_STRING_LEN, &field_return);
        if(i == -1){i++;continue;}
        uniqueness = insertTermDHSurname(hash_table, n, MAX_ARRAY_LEN, &collisions, &unique_collisions);
        //printNode(n);
        i++;
        printNode(n);
    }while(field_return != -1);
    printf("\nCOMPLETE");

return 0;
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
            //printf("\no Crowly EOF");
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

node* createNode(int number_fields, FILE* csv, char* buffer, int max_field_len, int* field_return){
    node* p = (node*)malloc(sizeof(node));
    p->next = NULL;
    int i = 0;
    do{
        (*field_return) = next_field(csv, buffer, max_field_len);

        //if(field_return == 404){return NULL;}
        
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
    //printf("\no Crowly finsihed");
    return p;
}

void printTitle(){
    printf("\n Person ID Deposition ID              Surname             Forename Age Person Type  Gender     Nationality        Religion           Occupation");
}

void printNode(node* p){
    printf("\n %9i %13s %20s %20s %3i %11s %7s %15s %15s %20s", \
    p->person_id, p->deposition_id, p->surname, p->forename, p->age, p->person_type, p->gender, p->nationality, p->religion, p->occupation);
}

int hash3(char* s, int array_len){
    //printf("\nhash3 %s", s);
    int hash = 0;
    while(*s){
        hash = 1 + (hash + (*s) -'A') % (array_len - 1);
        s++;
    }
    //printf(" %i", hash);
    return hash;
}

int hash1(char* s, int array_len){
    //printf("\nhash1 %s", s);
    int hash = 0;

    while(*s){
        hash = (hash + (*s) - 'A') %  array_len;
        s++;
    }
    //printf(" %i", hash);
    return hash;
}

int hashi(char* s, int array_len, int i){
    int hasha = hash1(s, array_len);
    int hashb = hash3(s, array_len);
    int hash = ((hasha + (i * hashb)) % array_len);
    //printf("\nhashi   %s", s);
    //printf(" %i", hash);
    return hash;
}

int insertTermDHSurname(people* hash_table, node* n, int array_len, int* collisions, int* unique_collisions){
    people* HASH_TABLE_COPY = hash_table;
    int probe = 0;
    char*surname = n->surname;
    int hashnum = hash1(surname, array_len);
    printf("\nSurname: %s Hash(%i)", surname, hashnum);
    node* head = NULL;

    while(1){
        if(hash_table[hashnum].head == NULL){//if position is empty, insert node pointer into head of people;
            hash_table[hashnum].head = n;
            (*unique_collisions) += probe;
            return 1; //unique insertion 
        }else if (strcmp((hash_table[hashnum].head->surname), surname) == 0){//else if surnames match
            //printf("\n SAME SURNAME: %s", hash_table[hashnum].head->surname);
            //printf(", %s", surname);
            head = hash_table[hashnum].head;//get the current head
            while(head->next != NULL){// go along nodes until the end
                head = head->next;
            }
            head->next = n;//set the last nodes next to the current insertion
            return 0;
        }else{
            probe ++;
            (*collisions)++; // increase collision counter
            hashnum = hashi(surname, array_len, probe);
            //printf(" + Hash(%i)", hashnum);
        }
    }
    
    

}