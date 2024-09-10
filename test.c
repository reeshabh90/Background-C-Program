#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Fork the current process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("  PID: %d\n", getpid());
        printf("  Parent PID: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent Process:\n");
        printf("  PID: %d\n", getpid());
        printf("  Child PID: %d\n", pid);

        // Exit parent process
        exit(0);
    }

    // If parent process has exited successfully, the code being executed at this point will be of child process only
    do {
        FILE *file = fopen("/tmp/background_process.log", "a");
        if (file != NULL) {
            fprintf(file, "Background process running with PID: %d\n", getpid());
            fclose(file);
        }
        sleep(10);
    } while(1);

    return 0;
}
