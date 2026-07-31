// Task 2 - Section 3: Comparing FIFO vs LRU

#include <stdio.h>

#define REF_LEN 13
int reference_string[REF_LEN] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

int find_in_frames(int frames[], int count, int page) {
    for (int i = 0; i < count; i++)
        if (frames[i] == page) return i;
    return -1;
}

int fifo(int refs[], int ref_len, int num_frames) {
    int frames[num_frames];
    int count = 0, oldest = 0, faults = 0;

    for (int i = 0; i < ref_len; i++) {
        int page = refs[i];

        if (find_in_frames(frames, count, page) != -1)
            continue;

        faults++;

        if (count < num_frames) {
            frames[count++] = page;
        } else {
            frames[oldest] = page;
            oldest = (oldest + 1) % num_frames;
        }
    }

    return faults;
}

int lru(int refs[], int ref_len, int num_frames) {
    int frames[num_frames], last_used[num_frames];
    int count = 0, faults = 0;

    for (int i = 0; i < ref_len; i++) {
        int page = refs[i];
        int pos = find_in_frames(frames, count, page);

        if (pos != -1) {
            last_used[pos] = i;   // Update the last used time
            continue;
        }

        faults++;

        if (count < num_frames) {
            frames[count] = page;
            last_used[count] = i;
            count++;
        } else {
            int idx = 0;

            // Find the least recently used page
            for (int j = 1; j < num_frames; j++)
                if (last_used[j] < last_used[idx])
                    idx = j;

            frames[idx] = page;
            last_used[idx] = i;
        }
    }

    return faults;
}

void compare(int num_frames) {
    int f = fifo(reference_string, REF_LEN, num_frames);
    int l = lru(reference_string, REF_LEN, num_frames);

    printf("Frames: %d\n", num_frames);
    printf("FIFO - Faults: %d | Fault Ratio: %.0f%% | Hit Ratio: %.0f%%\n",
           f, 100.0 * f / REF_LEN, 100.0 * (REF_LEN - f) / REF_LEN);
    printf("LRU  - Faults: %d | Fault Ratio: %.0f%% | Hit Ratio: %.0f%%\n",
           l, 100.0 * l / REF_LEN, 100.0 * (REF_LEN - l) / REF_LEN);

    if (l < f)
        printf("LRU performed better.\n\n");
    else if (f < l)
        printf("FIFO performed better.\n\n");
    else
        printf("Both gave the same result.\n\n");
}

int main(void) {
    printf("Reference String: ");

    for (int i = 0; i < REF_LEN; i++)
        printf("%d ", reference_string[i]);

    printf("\n\n");

    compare(3);
    compare(4);

    return 0;
}