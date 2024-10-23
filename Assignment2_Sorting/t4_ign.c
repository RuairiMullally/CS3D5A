#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 100
#define ARRAY_SIZE 18625

typedef struct game_review{
    char title[MAX_STRING_SIZE];
    char platform[MAX_STRING_SIZE];
    int score;
    int year;
}game_review;

int next_field(FILE *csv, char *buffer, int max_len);
game_review* createNode(int number_fields, FILE* csv, char* buffer, int max_field_len, int* field_return);

void swap(game_review* arr[], int i, int j);
int partition(game_review* arr[], int left_bound, int right_bound);
void callQuickSort(game_review* arr[], int left_bound, int right_bound);
void quickSort(game_review* arr[], int size);

int number_comparisons = 0;
int number_swaps = 0;

int main(){
    game_review* game_reviews[ARRAY_SIZE];
    char buffer[MAX_STRING_SIZE];


    FILE *csv = fopen("t4_ign.csv", "r"); // open CSV
    if (csv == NULL) { printf("Error opening file!\n"); return -1; }

    int field_return = 0;
    int i = -1;
    do{
        game_review* n = createNode(4, csv, buffer, MAX_STRING_SIZE, &field_return);
        if(i == -1){i++;continue;}
        game_reviews[i] = n;
        i++;
    }while(field_return != -1);

    for(int i = 0; i < 18625; i++){
        printf("\n%i %s", game_reviews[i]->score, game_reviews[i]->title);
    }

    quickSort(game_reviews, ARRAY_SIZE);
    printf("\nfinished sorting\n");

    for(int i = ARRAY_SIZE - 10; i < ARRAY_SIZE; i++){
        printf("\n%i, %s, %s, %i", game_reviews[i]->score, game_reviews[i]->title, game_reviews[i]->platform, game_reviews[i]->year);
    }

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

game_review* createNode(int number_fields, FILE* csv, char* buffer, int max_field_len, int* field_return){
    game_review* p = (game_review*)malloc(sizeof(game_review));
    int i = 0;
    do{
        (*field_return) = next_field(csv, buffer, max_field_len);
        
        switch (i) {//allocate attribute into appropriate member
            case 0: strcpy(p->title, buffer); break;
            case 1: strcpy(p->platform, buffer); break; //copy buffer into string
            case 2: p->score = atoi(buffer); break;
            case 3: p->year = atoi(buffer); break;
        }
        i++;
    }while(i < number_fields);

    return p;
}

void quickSort(game_review* arr[], int size) 
{ 
    number_comparisons = 0;
    int left = 0;
    int right = size - 1;
    callQuickSort(arr, left, right);

}

void swap(game_review* arr[], int i, int j){
    game_review* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    number_swaps++;
}


void callQuickSort(game_review* arr[], int left_bound, int right_bound){
    if(left_bound < right_bound){
        int partition_index = partition(arr, left_bound, right_bound);
        callQuickSort(arr, left_bound, partition_index -1);
        callQuickSort(arr, partition_index + 1, right_bound); 
    }
}

int partition(game_review* arr[], int left_bound, int right_bound){
    int pivot = arr[right_bound]->score;
    int i = left_bound;
    int j = right_bound - 1;
    while(1){
        while((arr[i]->score) <= pivot && i < right_bound){
            i++;
            number_comparisons++;
        }
        while((arr[j]->score) >= pivot && j > left_bound){
            j--;
            number_comparisons++;
        }
        if(i >= j){
            swap(arr, i, right_bound);
            return i; // Return the partition index
        }
        swap(arr, i, j);
    } 
}