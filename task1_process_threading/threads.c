//Task 1 - Section 1: Basic Multithreading (minimum 3 concurrent threads)

#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

void *worker(void *arg) {
    long id = (long)arg;
    for (int i = 0; i < 3; i++) {
        printf("Thread %ld: Step %d\n", id, i + 1);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    printf("Creating %d threads...\n", NUM_THREADS);
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, (void *)i);
    }

    //wait for all threads to finish before the program exits
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished.\n");
    return 0;
}
