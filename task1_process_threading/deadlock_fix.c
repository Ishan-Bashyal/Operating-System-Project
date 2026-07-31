// Task 1 - Section 5: Deadlock Prevention

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_b = PTHREAD_MUTEX_INITIALIZER;

void *thread1_fixed(void *arg) {
    pthread_mutex_lock(&lock_a);   // Lock A first
    usleep(300000);
    pthread_mutex_lock(&lock_b);   // Then lock B

    printf("Thread 1: Both locks acquired.\n");

    pthread_mutex_unlock(&lock_b);
    pthread_mutex_unlock(&lock_a);
    return NULL;
}

void *thread2_fixed(void *arg) {
    pthread_mutex_lock(&lock_a);   // Lock A first
    usleep(300000);
    pthread_mutex_lock(&lock_b);   // Then lock B

    printf("Thread 2: Both locks acquired.\n");

    pthread_mutex_unlock(&lock_b);
    pthread_mutex_unlock(&lock_a);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1_fixed, NULL);
    pthread_create(&t2, NULL, thread2_fixed, NULL);

    pthread_join(t1, NULL);   // Wait for both threads
    pthread_join(t2, NULL);

    printf("\nBoth threads finished.\n");
    printf("Deadlock prevented.\n");

    return 0;
}