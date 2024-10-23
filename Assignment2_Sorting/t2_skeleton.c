#include <stdio.h> 
#include "t2.h"
#include "t1.h"

int number_comparisons = 0;
int number_swaps = 0;

void swap(int *a, int *b);
int find_min(int *arr, int i, int size);
void callQuickSort(int* arr, int left_bound, int right_bound);
int partition(int* arr, int left_bound, int right_bound);


void selectionSort(int arr[], int size) 
{ 
    number_comparisons = 0;
    int min_index;
    for(int i = 0; i < size; i++){
        min_index = find_min(arr, i, size);
        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
        }
    }
  
} 

void insertionSort(int arr[], int size) 
{ 
    number_comparisons = 0;
    for(int i = 0; i < size - 1; i++){
        int k = i;
        number_comparisons ++;

        while((arr[k + 1] < arr[k]) && k >= 0){
            number_comparisons++;
            swap(&arr[k+1], &arr[k]);
            k--;
        }
        // if(k != i){
        //     number_comparisons --;
        // }
  }
  
}

void quickSort(int arr[], int size) 
{ 
    number_comparisons = 0;
    int left = 0;
    int right = size - 1;
    callQuickSort(arr, left, right);

}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    number_swaps++;
}

int find_min(int *arr, int i, int size){
    int min = arr[i];
    int min_index = i;
    for(int k = i+1; k < size; k++){
        number_comparisons++;
        if(arr[k] < min){
            min = arr[k];
            min_index = k;
        }
    }
    return min_index;
}

void callQuickSort(int* arr, int left_bound, int right_bound){
    if(left_bound < right_bound){
        int partition_index = partition(arr, left_bound, right_bound);
        callQuickSort(arr, left_bound, partition_index -1);
        callQuickSort(arr, partition_index + 1, right_bound); 
    }
}

int partition(int* arr, int left_bound, int right_bound){
    int pivot = arr[right_bound];
    int i = left_bound;
    int j = right_bound - 1;
    while(1){
        while(arr[i] <= pivot && i < right_bound){
            i++;
            number_comparisons++;
        }
        while(arr[j] >= pivot && j > left_bound){
            j--;
            number_comparisons++;
        }
        if(i >= j){
            swap(&arr[i], &arr[right_bound]);
            return i; // Return the partition index
        }
        swap(&arr[i], &arr[j]);
    } 
}

