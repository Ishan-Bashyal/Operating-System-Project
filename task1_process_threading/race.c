//Task 1 - Section 2: Race Condition

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define ITERATIONS  1000

long counter = 0;

void *unsafe_increment(void *arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        long temp = counter;   // read the current value
        usleep(0);              // force a scheduling gap so the race is reliable
        counter = temp + 1;     // write back an updated value -- but another thread may have changed counter in between
                                    
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, unsafe_increment, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    long expected = NUM_THREADS * ITERATIONS;
    printf("Expected final counter: %ld\n", expected);
    printf("Actual final counter:   %ld\n", counter);
    printf("Race condition occurred: %s\n", (counter != expected) ? "YES" : "NO");
    return 0;
}
