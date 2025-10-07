#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // create a child process

    if (pid == 0) {
        // Child process: replace its code with the 'top' program
        execlp("top", "top", NULL);
        printf("This will not print if exec succeeds.\n");
    } else if (pid > 0) {
        // Parent process
        printf("Parent still running...\n");
    } else {
        // fork() failed
        perror("fork failed");
    }

    return 0;
}
