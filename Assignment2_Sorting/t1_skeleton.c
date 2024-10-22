#include <stdio.h>
#include <stdlib.h>
#include "t1.h"

int is_unique(int *array, int size, int i, int num);

//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    for(int i = 0; i < size; i++){
        array[i] = i;
    }
    
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    for(int i = 0; i < size; i++){
        array[i] = size - i - 1;
    }
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    int num = rand() % 10;
    for(int i = 0; i < size; i++){
        array[i] = num;
    }
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    int num = 0;
    for(int i = 0; i < size; i++){
        num = rand() % size;
        array[i] = num;
    }
    
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    int num = 0;
    int inserted = 0;
    for(int i = 0; i < size; i++){
        num = rand() % size;
        inserted = is_unique(array, size, i, num);

        while(!inserted){
            num = rand() % size;
            inserted = is_unique(array, size, i, num);
        }

        array[i] = num;
    }
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int is_unique(int *array, int size, int i, int num){
    for(int k = 0; k < i; k++){
        if(array[k] == num){
            return 0;
        }
    }
    return 1;
}