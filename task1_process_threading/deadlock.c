// Task 1 - Section 4: Deadlock

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_b = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg) {
    pthread_mutex_lock(&lock_a);
    printf("Thread 1: Locked A, waiting for B...\n");
    usleep(300000);              // Wait before trying to lock B
    pthread_mutex_lock(&lock_b); // Program stops here because of deadlock
    printf("Thread 1: Both locks acquired.\n");
    pthread_mutex_unlock(&lock_b);
    pthread_mutex_unlock(&lock_a);
    return NULL;
}

void *thread2(void *arg) {
    pthread_mutex_lock(&lock_b);
    printf("Thread 2: Locked B, waiting for A...\n");
    usleep(300000);
    pthread_mutex_lock(&lock_a); // Program stops here because of deadlock
    printf("Thread 2: Both locks acquired.\n");
    pthread_mutex_unlock(&lock_a);
    pthread_mutex_unlock(&lock_b);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    sleep(2); // Wait for the deadlock to occur
    printf("\nBoth threads are still waiting.\n");
    printf("Deadlock detected.\n");

    return 0;
}