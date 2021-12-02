// Aditya Mitra
// 20BCE2044

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declaring the necessary functions
int diff(int, int);
int clos(int, int, int *);
void sstf(int, int, int *, int);

int main()
{
    // Declaring variables

    // No. of cylinders
    int cylinders;

    // curr Head Position
    int curr_head;

    // No. of requests
    int req_cnt;

    // Accepting No. of cylinders
    // printf("Number of Cylinders:");
    scanf("%d", &cylinders);

    // Accepting the curr head position
    // printf("curr Head Position:");
    scanf("%d", &curr_head);
    
    // Accepting requests
    // printf("Number of Requests");
    scanf("%d", &req_cnt);


    // Initialize request Queue
    int *req_q = (int *)malloc(sizeof(int) * req_cnt);

    //printf("q of pending request");
    // Accept request Queue
    for (int i = 0; i < req_cnt; i++)
    {
        scanf("%d", &req_q[i]);
    }

    // printf("Totak Seek time (distance):\n");
    sstf(cylinders, curr_head, req_q, req_cnt);

    return 0;
}

// Absolute difference between two numbers
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

// Finds the closest request
int clos(int curr, int size, int *q)
{
    int low = 9999, abs_c = diff(low, curr);
    int ind = -1;
    for (int i = 0; i < size; i++)
    {
        if (diff(q[i], curr) < diff(low, curr))
        {
            low = q[i];
            ind = i;
        }
    }

    q[ind] = 9999;
    return low;
}

// Function to implement SSTF
void sstf(int cylinders, int head, int *q, int cnt)
{
    int nxt, dist = 0;
    for (int i = 0; i < cnt; i++)
    {
        nxt = clos(head, cnt, q);
        dist += diff(nxt, head);
        head = nxt;
    }

    printf("%d", dist);
}