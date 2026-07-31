// Task 1 - Section 6: Round Robin CPU Scheduling Simulation

#include <stdio.h>

int main(void) {
    const char *names[3] = {"P1", "P2", "P3"};
    int remaining[3] = {5, 3, 4};   // Burst time for each process
    int queue[3] = {0, 1, 2};       // Ready queue
    int queue_len = 3;
    const int quantum = 2;
    int time_now = 0;

    printf("Round Robin Scheduling (Quantum = %d)\n", quantum);
    printf("Processes: P1=5, P2=3, P3=4\n\n");

    while (queue_len > 0) {
        int idx = queue[0];
        for (int i = 1; i < queue_len; i++)
            queue[i - 1] = queue[i];   // Remove first process
        queue_len--;

        int run_time = (remaining[idx] < quantum) ? remaining[idx] : quantum;
        int start = time_now, end = time_now + run_time;
        time_now = end;
        remaining[idx] -= run_time;

        printf("%s: %d to %d (Remaining: %d)\n",
               names[idx], start, end, remaining[idx]);

        if (remaining[idx] > 0) {
            queue[queue_len] = idx;   // Add back to the queue
            queue_len++;
        } else {
            printf("%s finished at %d\n", names[idx], end);
        }
    }

    printf("\nAll processes finished.\n");
    printf("Total time: %d\n", time_now);

    return 0;
}