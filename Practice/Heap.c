//heapsort and priority queue
#include <stdio.h>
#include <math.h>
int SIZE;

int left_child_index(int index){
    return (2*index);
}

int right_child_index(int index){
    return (2*index) + 1;
}

int parent_index(int index){
    return floor(index/2);
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int* heap, int index, int heap_size){ //O(log(n))
    int left = left_child_index(index);
    int right = right_child_index(index);

    int largest = index;

    if(left <= heap_size && heap[left] > heap[index]){
        largest = left;
    }

    if(right <= heap_size && heap[right] > heap[largest]){
        largest = right;
    }

    if(largest != index){
        swap(&heap[largest], &heap[index]);
        max_heapify(heap, largest, heap_size);
    }
}

void build_max_heap(int* heap, int heap_size){
    int k = floor(heap_size/2);
    for(int i = k; i > 0; i--){
        //printf("%i ", i);
        max_heapify(heap, i, heap_size);
    }
}

void heap_sort(int* heap, int heap_size){
    build_max_heap(heap, heap_size);

    for(int i = heap_size; i > 1; i--){
        swap(&heap[1], &heap[i]);
        max_heapify(heap, 1, i - 1);
    }


}



int main(){
    int heap[8] = {0, 50, 30, 40, 10, 5, 20, 15};
    heap_sort(heap, 7);

    for(int i = 0; i < 8; i++){
        printf("%i ", heap[i]);
    }
    return 0;
}