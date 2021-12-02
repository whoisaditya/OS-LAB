// Aditya Mitra
// 20BCE2044

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

// Maximum items a producer can produce or a consumer can consume
#define max_items 5

// Size of the buffer
#define buffer_size 5

// Initializing the required variables
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[buffer_size];
pthread_mutex_t mutex;

// Producer Function
void *producer(void *pno)
{
    int item;
    for (int i = 0; i < max_items; i++)
    {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item at %d\n", *((int *)pno), in);
        in = (in + 1) % buffer_size;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

// Consumer Function
void *consumer(void *cno)
{
    for (int i = 0; i < max_items; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item from %d\n", *((int *)cno), out);
        out = (out + 1) % buffer_size;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

// Main Funtion i.e. Driver Function
int main()
{
    pthread_t pro, con[3];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);

    int a = 1; //Just used for numbering the producer and consumer
    int b[3] = {1, 2, 3};

    pthread_create(&pro, NULL, (void *)producer, (void *)&a);

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&b[i]);
    }

    pthread_join(pro, NULL);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}