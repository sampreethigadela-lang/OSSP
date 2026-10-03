#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void echo(char *arg) {
    printf("%s\n", arg);
}

void pwd() {
    char path[200];
    printf("%s\n", getcwd(path, sizeof(path)));
}

int main() {
    char input[100], var[50], value[100];
    
    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    /* Variable Expansion */
    if (input[0] == '$') {
        strcpy(var, input + 1);
        char *v = getenv(var);

        if (v != NULL)
            printf("Expanded value: %s\n", v);
        else
            printf("Undefined variable: %s\n", var);

        return 0;
    }

    /* Built-in Dispatch */
    if (strncmp(input, "echo ", 5) == 0)
        echo(input + 5);

    else if (strcmp(input, "pwd") == 0)
        pwd();

    else if (strcmp(input, "exit") == 0)
        printf("Exiting...\n");

    else
        printf("Invalid command.\n");

    return 0;
}
