// Aditya Mitra
// 20BCE2044

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int diff(int , int );
void sort(int*, int );
void scan(int , int , int*, int );

// Main Function
int main()
{
    // Declaring variables

    // No. of cylinders
    int cylinders;
    
    // Current Head Position
    int curr_head;
    
    // No. of requests
    int req_cnt;

    // Accepting No. of cylinders
    //printf("Number of Cylinders:");
    scanf("%d", &cylinders);

    // Accepting the current head position
    //printf("Current Head Position:");
    scanf("%d", &curr_head);

    // Accepting requests
    //printf("Number of Requests");
    scanf("%d", &req_cnt);

    // Initialize request Queue
    int *req_q = (int *)malloc(sizeof(int) * req_cnt);

    //printf("q of pending request");
    // Accept request Queue
    for (int i = 0; i < req_cnt; i++)
    {
        scanf("%d", &req_q[i]);
    }

    // print answers and call the scan function
    printf("Totak Seek time (distance):\n");
    scan(cylinders, curr_head, req_q, req_cnt);

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

// Sorting the Queue using Insertion Sort 
void sort(int *arr, int n)
{
    int i, ele, j;
    for (i = 1; i < n; i++)
    {
        ele = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > ele)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = ele;
    }
}

// Function to pereform SCAN 
void scan(int cylinders, int head, int *q, int cnt)
{
    // Corting the queue
    sort(q, cnt); 

    // Location in queue
    printf("%d", diff(head, cylinders - 1) + diff(cylinders - 1, q[0]));
}
