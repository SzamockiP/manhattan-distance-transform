#include "manhattan_distance_transform.h"
#include "common.h"

// 2 pass algorithm
void manhattan_distance_transform(int* input_array, int* output_array){
    // Forward pass
    int i, j, idx, row_offset, neighbour_idx;

    const int INF = ARRAY_SIZE * ARRAY_SIZE;

    // Output array initialization
    for (i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++) {
        output_array[i] = INF;
    }

    // Forward pass
    row_offset = 0;
    for(i = 0; i < ARRAY_SIZE; i++){
        for(j = 0; j < ARRAY_SIZE; j++){
            idx = row_offset + j;

            if (i > 0) {
                neighbour_idx = idx - ARRAY_SIZE;
                // Check top neighbour
                if (input_array[neighbour_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from top
                    int candidate = output_array[neighbour_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }

            if (j > 0) {
                neighbour_idx= idx - 1;
                // Check left neighbour
                if (input_array[neighbour_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from left
                    int candidate = output_array[neighbour_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }
        }
        row_offset += ARRAY_SIZE;
    }

    row_offset = (ARRAY_SIZE - 1) * ARRAY_SIZE;
    for(i = ARRAY_SIZE - 1; i >= 0; i--){
        for(j = ARRAY_SIZE - 1; j >= 0; j--){
            idx = row_offset + j;

            if (i < ARRAY_SIZE - 1) {
                neighbour_idx = idx + ARRAY_SIZE;
                // Check bottom neighbour
                if (input_array[neighbour_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from bottom
                    int candidate = output_array[neighbour_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }

            if (j < ARRAY_SIZE - 1) {
                neighbour_idx = idx + 1;
                // Check right neighbour
                if (input_array[neighbour_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from right
                    int candidate = output_array[neighbour_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }
        }
        row_offset -= ARRAY_SIZE;
    }
}