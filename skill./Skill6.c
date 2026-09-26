#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char input[100], *args[10];
    int n = 0, i = 0;
    pid_t pid;

    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Parse command
    char *token = strtok(input, " ");
    while (token != NULL && n < 9) {
        args[n++] = token;
        token = strtok(NULL, " ");
    }
    args[n] = NULL;

    printf("\nParsed Arguments:\n");
    for (i = 0; i < n; i++)
        printf("Arg%d: %s\n", i + 1, args[i]);

    // Create child
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } 
    else {
        // Parent
        waitpid(pid, NULL, 0);
        printf("\nChild process completed.\n");
    }

    return 0;
}
