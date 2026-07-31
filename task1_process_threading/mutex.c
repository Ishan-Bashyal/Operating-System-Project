//Task 1 - Section 3: Fixing the Race Condition with a Mutex


#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3
#define ITERATIONS  1000

long counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *safe_increment(void *arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&lock);     //only one thread may enter here at a time
        counter++;
        pthread_mutex_unlock(&lock);   //release so the next waiting thread can enter
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, safe_increment, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    long expected = NUM_THREADS * ITERATIONS;
    printf("Expected final counter: %ld\n", expected);
    printf("Actual final counter:   %ld\n", counter);
    printf("Correct every time now: %s\n", (counter == expected) ? "YES" : "NO");
    return 0;
}
