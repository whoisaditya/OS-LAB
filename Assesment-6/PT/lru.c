// Author: 20BDS0392, Pranjal Timsina
// FIFO Page Replacement Algorithm
#include <stdio.h>
#include <stdlib.h>

// when the cache misses,. the item at the bottom is removed, and all data
// moves from position i to i -1
// eg : frame: 2, 3, 6 | new data = 5 -> cache miss
// new frame: 3, 6, 5
void sink_down(int * stack, int stack_size, int stack_top, int new_data) {
    for (int i = 0; i < stack_size - 1; i++) {
        // loop to shift data
        stack[i] = stack[i+1];
    }
    stack[stack_size - 1] = new_data; // add new data to frame
}


// when cache hits, it must be refreshed
// the data that is hit floats up
// it moves from position i to position stack_size - 1
void float_up(int* stack, int stack_size, int stack_top, int curr_index) {
    int i = curr_index; // start at the position of the data
    int temp; // temp variable for swap
    while (i < stack_size - 1) {  // while i is not at top
        temp = stack[i+1]; // swap data
        stack[i+1] = stack[i];
        stack[i] = temp;
        i++; // increment i
    }
}


// main lru function
void lru(int *string, int frame_size, int string_len) {
    int page_faults = 0; // init frames and page faults
    int *frames_stack = malloc(sizeof(int) * frame_size); // init frame
    int stack_top = -1; // variable for stack top

    // initialize each frame with a dummy value
    for (int i = 0; i < frame_size; i++) {
        frames_stack[i] = -1;
    }


    // read page reference string
    for (int i = 0; i < string_len; i++) {
        // printf("Data: %d\t", string[i]); // print curr data
        int curr = string[i];
        int hit = 0; // flag for hit or miss

        for(int j = 0; j < frame_size; j++) {
            if (curr==frames_stack[j]) { // check for page hit
                hit = 1;
                // do float up operation if page hit
                float_up(frames_stack, frame_size, stack_top, j);
                break;
            }
        }

        if (hit == 0) { // if page miss
            if (stack_top < 2) { // if page is not fully initialized
                stack_top++;
                frames_stack[stack_top] = curr; // add data directly to frame
            } else {
                // else do the sink down operation
                sink_down(frames_stack, frame_size, stack_top, curr);
            }
            page_faults++; // increment page fault
        }
    }
    printf("Page Faults\n%d", page_faults); // print page faults
}

// get the input page string
void get_input(int * page_string, int page_string_size) {
    printf("Reference string\n");
    for (int i = 0; i < page_string_size; i++) {
        scanf("%d", &page_string[i]);
    }
}

int main() {
    int frame_size = 3;
    printf("Size of frame\n");
    scanf("%d", &frame_size);

    int page_string_size;
    printf("Length of reference string\n");
    scanf("%d", &page_string_size);

    int* page_string = (int*) malloc(page_string_size * sizeof(int));
    get_input(page_string, page_string_size);
    // int page_string [] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};

    lru(page_string, frame_size, page_string_size);
    return 0;
}
