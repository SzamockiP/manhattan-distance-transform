#include "manhattan_distance_transform.h"
#include "common.h"

// 2 pass algorithm
void manhattan_distance_transform(int* input_array, int* output_array){
    // Forward pass

    const int INF = ARRAY_SIZE * ARRAY_SIZE;

    // Output array initialization
    for (int i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++) {
        output_array[i] = INF;
    }

    // Forward pass
    for(int i = 0; i < ARRAY_SIZE; i++){
        int row_offset = i * ARRAY_SIZE;
        for(int j = 0; j < ARRAY_SIZE; j++){
            int idx = row_offset + j;

            if (i > 0) {
                int top_idx = idx - ARRAY_SIZE;
                // Check top neighbour
                if (input_array[top_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from top
                    int candidate = output_array[top_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }

            if (j > 0) {
                int left_idx = idx - 1;
                // Check left neighbour
                if (input_array[left_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from left
                    int candidate = output_array[left_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }
        }
    }

    for(int i = ARRAY_SIZE - 1; i >= 0; i--){
        int row_offset = i * ARRAY_SIZE;
        for(int j = ARRAY_SIZE - 1; j >= 0; j--){
            int idx = row_offset + j;

            if (i < ARRAY_SIZE - 1) {
                int bottom_idx = idx + ARRAY_SIZE;
                // Check bottom neighbour
                if (input_array[bottom_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from bottom
                    int candidate = output_array[bottom_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }

            if (j < ARRAY_SIZE - 1) {
                int right_idx = idx + 1;
                // Check right neighbour
                if (input_array[right_idx] != input_array[idx]) {
                    output_array[idx] = 0;
                } else {
                    // Propagate value from right
                    int candidate = output_array[right_idx] + 1;
                    if (candidate < output_array[idx])
                        output_array[idx] = candidate;
                }
            }
        }
    }
}