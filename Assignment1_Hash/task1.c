#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//constants
const int ARRAY_SIZE = 59;
const int MAX_STRING_SIZE = 20;
//structure of data in array
typedef struct person{
    char name[20]; // MAX_STRING_SIZE
    int frequency;
} person;
//functions
int hash1(char* s);
int next_field(FILE *csv, char *buffer, int max_len);
int insertTerm(person* people, char* buffer, int ARRAY_SIZE, int* collisions); //linear probing 
int searchArray(person* people, char* s, int ARRAY_SIZE);


int main(){
    char buffer[20];
    int field_return; // return value of nextField, checks for new lines
    int uniqueness;
    int collisions = 0;
    person people[59]; //array of structure type of size ARRAY_SIZE


    //initialize people array to empty
    for(int i = 0; i < ARRAY_SIZE; i++){
        people[i].frequency = 0;
        strcpy(people[i].name, "                    ");
    }
    //open CSV file
    FILE *csv = fopen("names.csv", "r"); // open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return -1; }

    do{
        field_return = next_field(csv, buffer, 20);
        uniqueness = insertTerm(people, buffer, ARRAY_SIZE, &collisions);
    }while(field_return != -1);
    
    printf("\nTotal Collisions: %i", collisions);
    
    char search_term[20];
    do{
        printf("\n\nEnter term to get frequency of type quit to escape: ");
        fgets(search_term, 20, stdin); // Read the string from stdin
        //replace the newline so strings can be compared
        char* pos = strrchr(search_term, '\n');
        *pos = '\0';
        //search for term in table
        if(strcmp(search_term, "quit")){
            int search_freq = searchArray(people, search_term, 59);
            printf("Frequency or %s: %i",search_term, search_freq);
        }
    }while(strcmp(search_term, "quit"));


    return 0;

    
}


int searchArray(person* people, char* s, int ARRAY_SIZE){
    int position = hash1(s);
    int initial_position = position;
    int loop_done = 0;
    while(1){
        if((position < ARRAY_SIZE)){
            if(strcmp(people[position].name, s) == 0){
                return (people[position].frequency);
            }else{
                position++;
            }
        }else{
            position = 0;
            if(loop_done){printf("\nString not found!\n"); return -1;}
            loop_done = 1;
        }
        
    }
    
}

int insertTerm(person* people, char* buffer, int ARRAY_SIZE, int* collisions){
    int hashnum = hash1(buffer);//gets hash of buffer
    printf("\nName: %s hash(%i)",buffer, hashnum);

    while(1){
        if(hashnum < ARRAY_SIZE){
            if(people[hashnum].frequency == 0){
                people[hashnum].frequency = 1;
                strcpy(people[hashnum].name, buffer);
                return 1; //unique insertion
            }else if(strcmp(people[hashnum].name, buffer) == 0){
                people[hashnum].frequency++;
                return 0; //not unique insertion
            }else {
                hashnum++;
                (*collisions)++; // increase collision counter
                printf(" +");
            }
        }else{
            hashnum = 0;
            (*collisions)++; // increase collision counter
            printf(" +!");
        }
    }
}

int hash1(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s - 'A') %  ARRAY_SIZE;
        s++;
    }
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