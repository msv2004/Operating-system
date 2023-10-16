#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t child_pid = fork();

  if (child_pid < 0) {
    perror("fork() failed");
    return 1;
  }
  pid_t current_pid = getpid();

  pid_t parent_pid = getppid();

  if (child_pid == 0) {
    printf("Child process:\n");
    printf("PID: %d\n", current_pid);
    printf("Parent PID: %d\n", parent_pid);
  } else {
    printf("Parent process:\n");
    printf("PID: %d\n", current_pid);
    printf("Parent PID: %d\n", parent_pid);
  }

  return 0;
}

//output:
//Parent process:
//PID: 25762
//Parent PID: 25755
//Child process:
//PID: 25763
//Parent PID: 25762
