#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESS 100

int main() {
    int blockSizes[MAX_BLOCKS], processSizes[MAX_PROCESS];
    int m, n; // Number of memory blocks and processes
    int allocation[MAX_PROCESS];

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the sizes of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSizes[i]);
    }

    printf("Enter the sizes of processes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSizes[i]);
    }

    for (int i = 0; i < n; i++) {
        allocation[i] = -1; // Initialize as unallocated

        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                allocation[i] = j;
                blockSizes[j] -= processSizes[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i, processSizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i]);
        } else {
            printf("Not Allocated\n");
        }
    }

    return 0;
}
