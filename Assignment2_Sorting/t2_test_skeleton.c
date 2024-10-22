#include "t1.h"
#include "t2.h"
#include <stdio.h>



int main()
{
    int array[99];

    fill_ascending(array, 99);
    printArray(array, 99);
    quickSort(array, 99);
    printArray(array, 99);

    fill_descending(array, 99);
    printArray(array, 99);
    quickSort(array, 99);
    printArray(array, 99);

    fill_uniform(array, 99);
    printArray(array, 99);
    quickSort(array, 99);
    printArray(array, 99);

    fill_with_duplicates(array, 99);
    printArray(array, 99);
    quickSort(array, 99);
    printArray(array, 99);

    fill_without_duplicates(array, 99);
    printArray(array, 99);
    quickSort(array, 99);
    printArray(array, 99);

}