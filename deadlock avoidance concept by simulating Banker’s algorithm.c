#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

bool request_resources(int process, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;
        }
    }

    // Try allocating resources temporarily
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system remains in a safe state
    bool safe = is_safe();

    if (!safe) {
        // If the request leads to an unsafe state, roll back
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }

    return safe;
}

bool is_safe() {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // No process found that can be allocated, system is in an unsafe state
        }
    }

    return true; // All processes have been allocated resources safely
}

int main() {
    // Initialize available, maximum, allocation, and need arrays
    int request[MAX_RESOURCES];

    // Fill in the arrays with appropriate values

    // Example: Set available resources
    available[0] = 3;
    available[1] = 3;
    available[2] = 2;

    // Example: Set maximum demand for each process
    maximum[0][0] = 7;
    maximum[0][1] = 5;
    maximum[0][2] = 3;

    // Example: Set allocation for each process
    allocation[0][0] = 0;
    allocation[0][1] = 1;
    allocation[0][2] = 0;

    // Example: Calculate need for each process
    need[0][0] = 7;
    need[0][1] = 4;
    need[0][2] = 3;

    // Example: Simulate a resource request from process 0
    request[0] = 0;
    request[1] = 2;
    request[2] = 0;

    if (request_resources(0, request)) {
        printf("Request granted.\n");
    } else {
        printf("Request denied. Granting request would lead to an unsafe state.\n");
    }

    return 0;
}
