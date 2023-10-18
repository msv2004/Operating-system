#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

// Shared data
int counter = 0;
pthread_mutex_t mutex;

void *increment(void *thread_id) {
    int tid = *(int *)thread_id;

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        printf("Thread %d: Counter = %d\n", tid, counter);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, increment, &thread_ids[i]) != 0) {
            fprintf(stderr, "Thread creation failed\n");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    printf("Main thread: Counter = %d\n", counter);

    return 0;
}
