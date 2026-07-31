// Task 2 - Section 2: LRU (Least Recently Used) Page Replacement

#include <stdio.h>

#define REF_LEN 13
int reference_string[REF_LEN] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

int find_in_frames(int frames[], int count, int page) {
    for (int i = 0; i < count; i++)
        if (frames[i] == page) return i;
    return -1;
}

int lru(int refs[], int ref_len, int num_frames, int verbose) {
    int frames[num_frames];
    int last_used[num_frames];   // Stores the last time each page was used
    int count = 0;
    int faults = 0;

    for (int i = 0; i < ref_len; i++) {
        int page = refs[i];
        int pos = find_in_frames(frames, count, page);

        if (pos != -1) {
            last_used[pos] = i;   // Update the last used time
            if (verbose)
                printf("Page %d: Hit\n", page);
            continue;
        }

        faults++;

        if (count < num_frames) {
            frames[count] = page;
            last_used[count] = i;
            count++;

            if (verbose)
                printf("Page %d: Fault (loaded)\n", page);
        } else {
            int lru_index = 0;

            // Find the least recently used page
            for (int j = 1; j < num_frames; j++)
                if (last_used[j] < last_used[lru_index])
                    lru_index = j;

            if (verbose)
                printf("Page %d: Fault (replaced %d)\n", page, frames[lru_index]);

            frames[lru_index] = page;
            last_used[lru_index] = i;
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
    printf("LRU with %d frames\n", num_frames);

    int faults = lru(reference_string, REF_LEN, num_frames, 1);

    printf("\nTotal page faults: %d\n", faults);
    printf("Hit ratio: %.0f%%\n", 100.0 * (REF_LEN - faults) / REF_LEN);
    printf("Fault ratio: %.0f%%\n", 100.0 * faults / REF_LEN);

    return 0;
}