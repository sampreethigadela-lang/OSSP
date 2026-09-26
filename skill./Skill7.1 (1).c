#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char cmd[50], path[1000], *dir;
    pid_t pid;

    printf("Enter command: ");
    scanf("%49s", cmd);

    strcpy(path, getenv("PATH"));
    dir = strtok(path, ":");

    while (dir != NULL) {
        char file[200];
        sprintf(file, "%s/%s", dir, cmd);

        if (access(file, X_OK) == 0) {
            printf("Executable found: %s\n", file);

            pid = fork();

            if (pid == 0) {
                execl(file, cmd, NULL);
                perror("Execution failed");
                exit(1);
            }
            else if (pid > 0) {
                waitpid(pid, NULL, 0);
                printf("Child process completed.\n");
            }
            else {
                perror("Fork failed");
            }

            return 0;
        }

        dir = strtok(NULL, ":");
    }

    printf("Command not found.\n");
    return 0;
}
