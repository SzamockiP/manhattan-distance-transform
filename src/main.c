#include "common.h"
#include "manhattan_distance_transform.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
    const size_t array_size = ARRAY_SIZE * ARRAY_SIZE;

    // Input array initialization
    // int* value_array = malloc(array_size * sizeof(int));
    int* value_array = aligned_alloc(sizeof(int), array_size * sizeof(int));


    // Output array initialization
    // int* dt_array = malloc(array_size * sizeof(int));
    int* dt_array = aligned_alloc(sizeof(int), array_size * sizeof(int));

    manhattan_distance_transform(value_array, dt_array);

    for(int i = 0; i < ARRAY_SIZE; i++){
        int row = i * ARRAY_SIZE;

        for(int j = 0; j < ARRAY_SIZE; j++){
            printf("%d ",value_array[row + j]);
        }

        printf("   ");

        for(int j = 0; j < ARRAY_SIZE; j++){
            printf("%d ",dt_array[row + j]);
        }
        printf("\n");
    }



    return 0;
}
