// Aditya Mitra
// 20BCE2044

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Utility function to return the aboslute dist of two numbers
int diff(int a, int b)
{
    if (a > b)
    {
        return a - b;
    }
    else
    {
        return b - a;
    }
}

// function that calculates the total distance travelled
void fcfs(int cylinder_count, int head, int *q, int count)
{
    // Loop vairable
    int i;

    // Initialize distance travelled as 0
    int c = head;

    // Initialize current position as the head
    int dist = 0;

    // Interate through all the requests in the queue
    for (i = 0; i < count; i++)
    {
        // Distance = Absoulute difference 
        dist += diff(c, q[i]); 

        // Set current position to appropriate location
        c = q[i];                     
    }

    // Output
    printf("%d", dist);
}

// Driver function
int main()
{
    // Loop variable
    int i;

    // Declare variables
    int cylinder_count, curr_head, req_count;

    //printf("Total Number of Cylinders:");
    scanf("%d", &cylinder_count);
    
    //printf("Current Head Position:");
    scanf("%d", &curr_head);

    //printf("Number of request");
    scanf("%d", &req_count);

    // Declare the request queue
    int *req_q = (int *)malloc(sizeof(int) * req_count);

    //printf("Queue of pending requests:");

    // Accept requests
    for (i = 0; i < req_count; i++)
    {
        scanf("%d", &req_q[i]);
    }

    printf("Totak Seek time (dist):\n");

    // call the fcfs function
    fcfs(cylinder_count, curr_head, req_q, req_count);

    return 0;
}