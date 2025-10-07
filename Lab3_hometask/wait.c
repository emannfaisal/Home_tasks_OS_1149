#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        execlp("date", "date", NULL);
    } else {
        // Parent process → wait for child to finish
        waitpid(pid, NULL, 0);
        printf("Child finished\n");
    }
    return 0;
}
