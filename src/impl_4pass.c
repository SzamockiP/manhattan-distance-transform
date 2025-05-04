#include "manhattan_distance_transform.h"
#include "common.h"

void manhattan_distance_transform(int* input_array, int* output_array){
    // for(int i = 0; i < ARRAY_SIZE; i++){
    //     int row = i * ARRAY_SIZE;
    //     for(int j = 0; j < ARRAY_SIZE; j++){
    //         output_array[row + j] = input_array[row + j];
    //     }
    // }

    for(int i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++){
        if(i % ARRAY_SIZE != 0)
            output_array[i] = input_array[i];
        else
            output_array[i] = input_array[i];
    }
}