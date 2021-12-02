// Least Recently Used (LRU) Page Replacement Algorithm
// 20BCE2044 Aditya Mitra

#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int *fr_st;
    int st_size;
    int st_top; 
};

// When the cache misses, the item at the bottom is removed, and all data is moved from position i to i -1
void move_data(struct Stack stack, int new_data)
{
    // Loop to shift data
    for (int i = 0; i < stack.st_size - 1; i++)
    {
        stack.fr_st[i] = stack.fr_st[i + 1];
    }

    // Add new data to Frame
    stack.fr_st[stack.st_size - 1] = new_data; 
}

// When cache flags, it must be refreshed the data and the flag is moved from position i to position st_size - 1
void refresh_data(struct Stack stack, int current_index)
{
    // Start at the position of the data
    int i = current_index; 

    // Temporary variable for swapping
    int temp;          

    // While i is not at Top
    while (i < stack.st_size - 1)
    { 
        // Swap Data                      
        temp = stack.fr_st[i + 1]; 
        stack.fr_st[i + 1] = stack.fr_st[i];
        stack.fr_st[i] = temp;

        // Increment i
        i++; 
    }
}

// Main LRU Function
void lru(int *str, int fr_size, int str_len)
{
    // Declare a Stack
    struct Stack stack;

    // Initialize Stack Size
    stack.st_size = fr_size;

    // Initialze Page Fault
    int pg_faults = 0; 

    // Initialze Frame 
    stack.fr_st = malloc(sizeof(int) * fr_size); 

    // Initialize Stack Top to -1
    stack.st_top = -1;                                   

    // Initialize Each Frame to -1
    
    for (int i = 0; i < fr_size; i++)
    {
        //printf("Initializing Frames\n");
        stack.fr_st[i] = -1;
    }

    // Iterate through Reference String
    for (int i = 0; i < str_len; i++)
    {
        int current = str[i];
        //printf("%d\n", current);  

        // Flag Variable for hit or miss
        int flag = 0; 

        for (int j = 0; j < fr_size; j++)
        {
            // Check for Page Flag
            if (current == stack.fr_st[j])
            { 
                flag = 1;

                // Float up operation if page hit occurs
                refresh_data(stack, j);
                break;
            }
        }

        // If page miss
        if (flag == 0)
        { 
            // If Page is not Fully Initialized
            if (stack.st_top < 2)
            {
                stack.st_top++;

                // Add Data to Frame
                stack.fr_st[stack.st_top] = current; 
            }
            // Else do the sink down operation
            else
            {
                move_data(stack, current);
            }

            // Increment Page Fault
            pg_faults++; 
        }
    }

    // Print Page Faults
    printf("Page Faults\n%d", pg_faults);
}


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

    lru(pg_str, fr_size, pg_str_size);
    return 0;
}
