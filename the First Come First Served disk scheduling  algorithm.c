#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total seek time
int calculateSeekTime(int requestSequence[], int n, int initialPosition) {
    int seekTime = 0;

    for (int i = 0; i < n; i++) {
        seekTime += abs(requestSequence[i] - initialPosition);
        initialPosition = requestSequence[i];
    }

    return seekTime;
}

int main() {
    int n, initialPosition;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialPosition);

    int requestSequence[n];

    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requestSequence[i]);
    }

    int totalSeekTime = calculateSeekTime(requestSequence, n, initialPosition);

    printf("Total seek time: %d\n", totalSeekTime);

    return 0;
}
