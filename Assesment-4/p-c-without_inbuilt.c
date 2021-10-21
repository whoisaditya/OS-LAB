#include <stdio.h>
#include <stdlib.h>

struct variables
{
    int mutex, full, empty, x;
};

// Necessary Functions
int Wait(int);
int Signal(int);

void Producer(struct variables);
void Consumer(struct variables);

// Driver Function
int main()
{
    int n;
    struct variables A;

    A.mutex = 1; 
    A.full = 0;
    A.empty = 3;
    A.x = 0;

    printf("\nMenu\n1.Producer\n2.Consumer\n3.Exit");
    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
        {
            if ((A.mutex == 1) && (A.empty != 0))
            {
                Producer(A);
            }
            else
            {
                printf("Buffer is Full");
            }
            break;
        }
        case 2:
        {
            if ((A.mutex == 1) && (A.full != 0))
            {
                Consumer(A);
            }
            else
            {
                printf("Buffer is Empty");
            }
            break;
        }
        case 3:
        {
            exit(0);
            break;
        }
        }
    }
    return 0;
}

// Wait Function
int Wait(int i)
{
    return (--i);
}

// Signal Function
int Signal(int i)
{
    return (++i);
}

// Producer Function
void Producer(struct variables A)
{
    A.mutex = Wait(A.mutex);
    A.full = Signal(A.full);
    A.empty = Wait(A.empty);

    A.x++;
    printf("\nProducer produces the item %d", A.x);
    A.mutex = Signal(A.mutex);
}

// Consumer Function
void Consumer(struct variables A)
{
    A.mutex = Wait(A.mutex);
    A.full = Wait(A.full);
    A.empty = Signal(A.empty);

    printf("\nConsumer consumes item %d", A.x);
    A.x--;
    A.mutex = Signal(A.mutex);
}