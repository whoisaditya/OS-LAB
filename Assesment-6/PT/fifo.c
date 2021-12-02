// Author: 20BDS0392, Pranjal Timsina
// FIFO Page Replacement Algorithm
#include <stdio.h>
#include <stdlib.h>

// get the input page string
void get_input(int * page_string, int page_string_size) {
    printf("Reference string\n");
    for (int i = 0; i < page_string_size; i++) {
        scanf("%d", &page_string[i]);
    }
}

void first_in_first_out(int *string, int frame_size, int string_len) {
    // init frames and page faults
    int *frames = malloc(frame_size * sizeof(int));
    int page_faults = 0;

    // initialize each frame with a dummy value
    for (int i = 0; i < frame_size; i++) {
        frames[i]=-1;
    }

    int frame_ind = 0; // first frame index

    for (int i = 0; i < string_len; i++) {  // iterate throught the reference string
        int curr = string[i]; // store the current input
        int hit = 0; // flag for hit or miss

        for(int j = 0; j < frame_size; j++) { // check if page hit
            if (curr==frames[j]) {
                hit = 1; // if page hit break loop
                break;
            }
        }

        if (hit == 0) { // if page miss use FIFO replacement policy
            frame_ind = (frame_ind + 1) % frame_size; // MODULO increment
            frames[frame_ind] = curr;
            page_faults++; // increment page faults
        }
    }
    printf("Page Faults\n%d", page_faults);
}

int main() {
    int frame_size;
    printf("Size of frame\n");
    scanf("%d", &frame_size);

    int page_string_size;
    printf("Length of the reference string\n");
    scanf("%d", &page_string_size);

    int* page_string = (int*) malloc(page_string_size * sizeof(int));
    get_input(page_string, page_string_size);
    // int page_string [] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};

    // printf("\nFirst in First out policy:\n");
    first_in_first_out(page_string, frame_size, page_string_size);
    return 0;
}
