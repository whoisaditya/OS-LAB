// First In First Out Page Replacement Algorithm
// 20BCE2044 Aditya Mitra

#include <stdio.h>
#include <stdlib.h>

// Function to perform FIFO
void fifo(int *str, int fr_size, int str_len)
{
    // Initialize Frames 
    int *frs = malloc(fr_size * sizeof(int));

    // Initialize Page Faults 
    int pg_faults = 0;

    // Initialize each Frame to -1
    for (int i = 0; i < fr_size; i++)
    {
        frs[i] = -1;
    }

    // First Frame index
    int fr_ind = 0; 

    // Iterate through the Reference String
    for (int i = 0; i < str_len; i++)
    {  
        // Store the current input
        int current = str[i]; 

        // Flag Variable for hit or miss
        int flag = 0;          

        for (int j = 0; j < fr_size; j++)
        { 
            // Check if Page hit
            if (current == frs[j])
            {
                // If Page hit break loop
                flag = 1; 
                break;
            }
        }

        // If Page miss then use the FIFO Replacement Policy
        if (flag == 0)
        {
            // MODULO Increment
            fr_ind = (fr_ind + 1) % fr_size; 
            frs[fr_ind] = current;

            // Increment Page Faults
            pg_faults++; 
        }
    }

    // Print Page Faults
    printf("Page Faults\n");
    printf("%d", pg_faults);
}

// Driver Function
int main()
{
    // Frame Size
    int fr_size;

    // Accept Size of Frame
    printf("Size of frame\n");
    scanf("%d", &fr_size);

    // Reference String Size
    int pg_str_size;

    // Accept the length of Reference String
    printf("Length of the reference string\n");
    scanf("%d", &pg_str_size);

    // Page String
    int *pg_str = (int *)malloc(pg_str_size * sizeof(int));

    // Accept the Reference String
    printf("Reference string\n");
    for (int i = 0; i < pg_str_size; i++)
    {
        scanf("%d", &pg_str[i]);
    }
    
    // Call FIFO Function
    fifo(pg_str, fr_size, pg_str_size);

    return 0;
}