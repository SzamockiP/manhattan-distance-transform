#include "manhattan_distance_transform.h"
#include "common.h"

void manhattan_distance_transform(int* input_array, int* output_array){

    int i, j, idx, is_neighbour, row_offset, neighbour_idx;

    const int INF = ARRAY_SIZE * ARRAY_SIZE;

    // Iteration 1: initialization – neighbour marking
    row_offset = 0;
    for(i = 0; i < ARRAY_SIZE; i++) {
        for(j = 0; j < ARRAY_SIZE; j++) {
            idx = row_offset + j;
            is_neighbour = 0;
            // Top check
            if(i > 0 && input_array[idx - ARRAY_SIZE] != input_array[idx])
                is_neighbour = 1;
            // Bottom check
            if(i < ARRAY_SIZE - 1 && input_array[idx + ARRAY_SIZE] != input_array[idx])
                is_neighbour = 1;
            // Left check
            if(j > 0 && input_array[idx - 1] != input_array[idx])
                is_neighbour = 1;
            // Right check
            if(j < ARRAY_SIZE - 1 && input_array[idx + 1] != input_array[idx])
                is_neighbour = 1;

            output_array[idx] = is_neighbour ? 0 : INF;
        }
        row_offset += ARRAY_SIZE;
    }

    // Iteration 2: Top to bottom
    row_offset = ARRAY_SIZE;
    for(i = 1; i < ARRAY_SIZE; i++) {
        for(j = 0; j < ARRAY_SIZE; j++) {
            idx = row_offset + j;
            neighbour_idx = idx - ARRAY_SIZE;
            if(output_array[neighbour_idx] + 1 < output_array[idx])
                output_array[idx] = output_array[neighbour_idx] + 1;
        }
        row_offset += ARRAY_SIZE;
    }

    // Iteration 3: Left to right
    row_offset = 0;
    for(i = 0; i < ARRAY_SIZE; i++) {
        for(j = 1; j < ARRAY_SIZE; j++) {
            idx = row_offset + j;
            neighbour_idx = idx - 1;
            if(output_array[neighbour_idx] + 1 < output_array[idx])
                output_array[idx] = output_array[neighbour_idx] + 1;
        }
        row_offset += ARRAY_SIZE;
    }

    // Iteration 4: Bottom to top
    row_offset = (ARRAY_SIZE - 2) * ARRAY_SIZE;
    for(i = ARRAY_SIZE - 2; i >= 0; i--) {
        for(j = 0; j < ARRAY_SIZE; j++) {
            idx = row_offset + j;
            neighbour_idx = idx + ARRAY_SIZE;
            if(output_array[neighbour_idx] + 1 < output_array[idx])
                output_array[idx] = output_array[neighbour_idx] + 1;
        }
        row_offset -= ARRAY_SIZE;
    }

    // Iteration 5: Right to left
    row_offset = 0;
    for(i = 0; i < ARRAY_SIZE; i++) {
        for(j = ARRAY_SIZE - 2; j >= 0; j--) {
            idx = row_offset + j;
            neighbour_idx = idx + 1;
            if(output_array[neighbour_idx] + 1 < output_array[idx])
                output_array[idx] = output_array[neighbour_idx] + 1;
        }
        row_offset += ARRAY_SIZE;
    }
}