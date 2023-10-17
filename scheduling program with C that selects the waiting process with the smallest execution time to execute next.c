#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int PID;
    int execution_time;
} Process;

typedef struct Queue {
    struct Process *head;
    struct Process *tail;
} Queue;

Process *create_process(int PID, int execution_time) {
    Process *process = malloc(sizeof(Process));
    process->PID = PID;
    process->execution_time = execution_time;
    return process;
}
void enqueue(Queue *queue, Process *process) {
    if (queue->head == NULL) {
        queue->head = queue->tail = process;
    } else {
        queue->tail->next = process;
        queue->tail = process;
    }
}

Process *dequeue(Queue *queue) {
    Process *process = queue->head;
    if (queue->head == queue->tail) {
        queue->head = queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }
    return process;
}
Process *find_shortest_job(Queue *queue) {
    Process *process = queue->head;
    Process *shortest_job = process;
    while (process != NULL) {
        if (process->execution_time < shortest_job->execution_time) {
            shortest_job = process;
        }
        process = process->next;
    }
    return shortest_job;
}

void schedule_next_process(Queue *queue) {
    Process *process = find_shortest_job(queue);
    printf("Scheduling process with PID %d\n", process->PID);
    dequeue(queue);
}

int main() {
    Queue *queue = malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;

    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    for (int i = 0; i < num_processes; i++) {
        int execution_time;
        printf("Enter the execution time for process %d: ", i + 1);
        scanf("%d", &execution_time);

        Process *process = create_process(i + 1, execution_time);
        enqueue(queue, process);
    }
    while (queue->head != NULL) {
        schedule_next_process(queue);
    }

    free(queue);

    return 0;
}
