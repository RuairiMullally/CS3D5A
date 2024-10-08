/*Ruairi Mullally 22336002
To use for future projects:
>adapt the struct appropriately
>change the switch statement conversions appropriately
>change buffer and pokemon_array lengths
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int readCSV(pokemon *pokemon_array, char *file_name , int pokemon_array_len, int max_len);
int next_field(FILE *csv, char *buffer, int max_len);

typedef struct pokemon {
    int id;
    char name[50];
    char type1[20];
    char type2[20];
    int total_stats;
    int hp;
    int attack;
    int defense;
    int special_attack;
    int special_defense;
    int speed;
    int generation;
    char legendary[5];
    char pokedex_entry[150];
} pokemon;

int main() {
    const int max_len = 150;
    char buffer[150]; // buffer for storing fields
    int field_return; // return value of field storer, checks for new lines
    pokemon pokemon_array[1000]; // array to store pokemon structs

    FILE *csv = fopen("pokemon.csv", "r"); // open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return 1; }

    int field_index = 0;
    int pn = -1; // pokemon counter

    do{
        static pokemon p; // pokemon instance, static so it doesnt get cleared between field indexes
        field_return = next_field(csv, buffer, max_len);
        
        printf("%s", buffer); // display pokemon info
        switch (field_index) {//allocate attribute into appropriate member
            case 0: p.id = atoi(buffer); break; //ascii to int
            case 1: strcpy(p.name, buffer); break;// string copy
            case 2: strcpy(p.type1, buffer); break;
            case 3: strcpy(p.type2, buffer); break;
            case 4: p.total_stats = atoi(buffer); break;
            case 5: p.hp = atoi(buffer); break;
            case 6: p.attack = atoi(buffer); break;
            case 7: p.defense = atoi(buffer); break;
            case 8: p.special_attack = atoi(buffer); break;
            case 9: p.special_defense = atoi(buffer); break;
            case 10: p.speed = atoi(buffer); break;
            case 11: p.generation = atoi(buffer); break;
            case 12: strcpy(p.legendary, buffer); break;
            case 13:
                if(pn == -1){ pn++; break;}
                strcpy(p.pokedex_entry, buffer); 
                pokemon_array[pn] = p; // p is formatted so copy into array
                pn++; // increase pokemon count
                break;
        }

        if (field_return == 0) {//if new field (comma)
            field_index++; 
            printf("\n");
        } else if (field_return == 1) { // if new pokemon (return)
            field_index = 0;
            printf("\n\n");
        }
    }while(field_return != -1);

    printf("\n\nLast Pokemon's name: %s\n", pokemon_array[pn - 1].name);
    printf("Last Pokemon's attack: %d\n", pokemon_array[pn - 1].attack);

    //processing
    int running_total = 0;
    for(int i = 0; i < pn; i++){
        //printf("%s\n", pokemon_array[i].name);
        running_total += pokemon_array[i].attack;        
    }
    running_total = running_total / pn;
    printf("\nPokemon average attack power: %d\n", running_total);
    printf("Processing done.\n");

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
        if (buff == EOF) return -1; // end of file

        if ((buff == '"') && inside == 0) { // handle quotes cant believe no bools in C!!!!
            inside = 1;
        } else if ((buff == '"') && inside == 1) {
            inside = 0;
        }

        if (buff == '\n') {
            buffer[i] = '\0'; 
            return 1; // end of pokemon
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

int readCSV(char* filename, char* buffer, int max_string_len){
    FILE *csv = fopen(filename, "r"); // open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return -1; }

    next_field(csv, buffer, max_string_len);

}

/*int readCSV(pokemon *pokemon_array, char *name , int pokemon_array_len, int max_len){

    typedef struct pokemon {
    int id;
    char name[50];
    char type1[20];
    char type2[20];
    int total_stats;
    int hp;
    int attack;
    int defense;
    int special_attack;
    int special_defense;
    int speed;
    int generation;
    char legendary[5];
    char pokedex_entry[150];
} pokemon;

    #define max_len1 = max_len;
    char buffer[150]; // buffer for storing fields
    int field_return; // return value of field storer, checks for new lines

    FILE *csv = fopen("pokemon.csv", "r"); // Open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return 1; }

    int field_index = 0;
    int pn = 0; // pokemon counter

    do{
        static pokemon p; // pokemon instance, static so it doesnt get cleared between field indexes
        field_return = next_field(csv, buffer, max_len);
        
        printf("%s", buffer); // display pokemon info
        switch (field_index) {//allocate attribute into appropriate member
            case 0: p.id = atoi(buffer); break; //ascii to int
            case 1: strcpy(p.name, buffer); break;// string copy
            case 2: strcpy(p.type1, buffer); break;
            case 3: strcpy(p.type2, buffer); break;
            case 4: p.total_stats = atoi(buffer); break;
            case 5: p.hp = atoi(buffer); break;
            case 6: p.attack = atoi(buffer); break;
            case 7: p.defense = atoi(buffer); break;
            case 8: p.special_attack = atoi(buffer); break;
            case 9: p.special_defense = atoi(buffer); break;
            case 10: p.speed = atoi(buffer); break;
            case 11: p.generation = atoi(buffer); break;
            case 12: strcpy(p.legendary, buffer); break;
            case 13:
                strcpy(p.pokedex_entry, buffer); 
                pokemon_array[pn] = p; // p is formatted so copy into array
                pn++; // increase pokemon count
                break;
        }

        if (field_return == 0) {//if comma
            field_index++; 
            printf("\n");
        } else if (field_return == 1) { // if new pokemon
            field_index = 0;
            printf("\n\n");
        }
    }while(field_return != -1);

}*/