#include "t1.h"
#include <stdio.h>
#define ARRAY_SIZE 10



int main()
{
    int array[ARRAY_SIZE];
    fill_ascending(array, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);

    fill_descending(array,ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);

    fill_uniform(array, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);

    fill_with_duplicates(array, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);

    fill_without_duplicates(array, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);
    

    return 0;
}