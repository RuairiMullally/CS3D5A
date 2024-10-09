#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//constants
#define ARRAY_SIZE 59 //is a prime
#define MAX_STRING_SIZE 20
//structure of data in array
typedef struct person{
    char name[MAX_STRING_SIZE]; // MAX_STRING_SIZE
    int frequency;
} person;
//functions
int hash1(char* s);
int hash3(char* s); 
int hashi(char* s, int array_len, int i);
int next_field(FILE *csv, char *buffer, int max_len);
int insertTermDH(person* people, char* buffer, int array_len, int* collisions, int* unique_collisions); //double hashing
int searchArrayDH(person* people, char* s, int array_len);



int main(){
    char buffer[MAX_STRING_SIZE]; // contains input from csv
    int field_return; // return value of nextField, checks for new lines
    int uniqueness; // return value of insertTermDH, 1 = new insert, 0 = duplicate/increase freq
    int collisions = 0; // total number of collisions in insersion
    int unique_collisions = 0; // number of unique collisions (first insersion of that string)
    person people[ARRAY_SIZE]; //array of structure type of size ARRAY_SIZE


    //initialize people array to empty
    for(int i = 0; i < ARRAY_SIZE; i++){
        people[i].frequency = 0;
        people[i].name[0] = '\0';
    }
    //open CSV file
    FILE *csv = fopen("names.csv", "r"); // open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return -1; }

    do{ //main process
        field_return = next_field(csv, buffer, MAX_STRING_SIZE); // get next field from CSV
        uniqueness = insertTermDH(people, buffer, ARRAY_SIZE, &collisions, &unique_collisions); // insert that field to hash table
    }while(field_return != -1); //while not at end of file
    
    printf("\nTotal Collisions: %i", collisions);
    printf("\nUnique Collisions: %i", unique_collisions);
    
    char search_term[MAX_STRING_SIZE];
    do{ // allow users to search for data
        printf("\n\nEnter term to get frequency of type quit to escape: ");
        fgets(search_term, MAX_STRING_SIZE, stdin); // Read the string from stdin
        //replace the newline so strings can be compared
        char* pos = strrchr(search_term, '\n');
        *pos = '\0';
        //search for term in table
        if(strcmp(search_term, "quit")){
            int search_freq = searchArrayDH(people, search_term, ARRAY_SIZE);
            printf("Frequency of %s: %i",search_term, search_freq);
        }
    }while(strcmp(search_term, "quit"));
    
    return 0;
}


int searchArrayDH(person* people, char* s, int array_len){
    int position = hash1(s);
    int probes = 0;

    while(probes < array_len){
        if(people[position].frequency == 0){//dh probes mean a gap will not exist if was inserted
            printf("\nString not found!\n"); 
            return -1;
        }
        if(strcmp(people[position].name, s) == 0){
            return (people[position].frequency);
        }else{
            probes++;
            position = hashi(s, array_len, probes);
        }
        
    }
}

int insertTermDH(person* people, char* buffer, int array_len, int* collisions, int* unique_collisions){
    int probes = 0;
    int hashnum1 = hash1(buffer);
    printf("\nName: %s hash(%i)",buffer, hashnum1);
    
    while(1){
        if(people[hashnum1].frequency == 0){
            people[hashnum1].frequency = 1;
            strcpy(people[hashnum1].name, buffer);
            (*unique_collisions) += probes;
            return 1; //unique insertion
        }else if(strcmp(people[hashnum1].name, buffer) == 0){
            people[hashnum1].frequency++;
            return 0; //not unique insertion
        }else {
            (*collisions)++; // increase collision counter
            probes++;
            printf(" +");
            

            hashnum1 = hashi(buffer, array_len, probes);
            printf(" hashi(%i)", hashnum1);
        }
    }
}

int hash3(char* s){
    int hash = 0;
    while(*s){
        hash = 1 + (hash + (*s) -'A') % (ARRAY_SIZE - 1);
        s++;
    }
    return hash;
}

int hash1(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s - 'A') %  ARRAY_SIZE;
        s++;
    }
    return hash;
}

int hashi(char* s, int array_len, int i){
    return (hash1(s) + (i * hash3(s))) % array_len;
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