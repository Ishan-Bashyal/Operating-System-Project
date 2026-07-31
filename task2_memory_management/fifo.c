// Task 2 - Section 1: FIFO Page Replacement

#include <stdio.h>

#define REF_LEN 13
int reference_string[REF_LEN] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

int find_in_frames(int frames[], int count, int page) {
    for (int i = 0; i < count; i++)
        if (frames[i] == page) return i;
    return -1;
}

int fifo(int refs[], int ref_len, int num_frames, int verbose) {
    int frames[num_frames];
    int count = 0;
    int oldest = 0;   // Next frame to replace
    int faults = 0;

    for (int i = 0; i < ref_len; i++) {
        int page = refs[i];

        if (find_in_frames(frames, count, page) != -1) {
            if (verbose)
                printf("Page %d: Hit\n", page);
            continue;
        }

        faults++;

        if (count < num_frames) {
            frames[count] = page;      //empty slot available
            count++;
            if (verbose)
                printf("Page %d: Fault (loaded)\n", page);
        } else {
            if (verbose)
                printf("Page %d: Fault (replaced %d)\n", page, frames[oldest]);
            frames[oldest] = page;      //overwrite the oldest page
            oldest = (oldest + 1) % num_frames;     //next page to evict
        }
    }

    return faults;
}

int main(void) {
    printf("Reference String: ");
    for (int i = 0; i < REF_LEN; i++)
        printf("%d ", reference_string[i]);
    printf("\n\n");

    int num_frames = 3;
    printf("FIFO with %d frames\n", num_frames);

    int faults = fifo(reference_string, REF_LEN, num_frames, 1);

    printf("\nTotal page faults: %d\n", faults);
    printf("Hit ratio: %.0f%%\n", 100.0 * (REF_LEN - faults) / REF_LEN);
    printf("Fault ratio: %.0f%%\n", 100.0 * faults / REF_LEN);

    return 0;
}