#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int arrayLength){
    int i;
    for(i = 0; i < arrayLength; i++){
        if(i > 0){
            printf(" ");
        }
        printf("%d",array[i]);
    }
    printf("\n");
}

void swap(int index1, int index2, int *array);

void partition(int *array, int length){
    int i, j;
    /* Leftmost pivot */
    int pivot = array[0];
    /* Impelment partition here */
    i = 0;
    j = length - 1;
    while (i != j) {
        if (array[i] > pivot && pivot > array[j] && i < j) {
            swap(i, j, array);
        }
        i++;
        j--;
    }
    swap(0, i, array);
    
    
    /* ------------------------ */
}

void swap(int index1, int index2, int *array){
    printf("Swapping index %d, containing %d and index %d, containing %d\n", index1, array[index1], index2, array[index2]);
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

int main(int argc, char **argv){
    int array[] = {5, 6, 3, 8, 1, 2, 7, 4, 9};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    printf("Before: ");
    printArray(array, arrayLength);
    
    partition(array, arrayLength);
    
    printf("After: ");
    printArray(array, arrayLength);
    return 0;
}