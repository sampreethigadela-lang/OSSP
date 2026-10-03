#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

int main() {
    char path[PATH_MAX];
    char current[PATH_MAX];
    char previous[PATH_MAX] = "";

    while (1) {
        getcwd(current, sizeof(current));
        printf("\nCurrent Directory: %s\n", current);

        printf("Enter directory (type exit to quit): ");
        fgets(path, sizeof(path), stdin);
        path[strcspn(path, "\n")] = '\0';

        if (strcmp(path, "exit") == 0)
            break;

        if (strcmp(path, "-") == 0) {
            if (strlen(previous) == 0) {
                printf("No previous directory.\n");
                continue;
            }
            strcpy(path, previous);
        }

        strcpy(previous, current);

        if (chdir(path) == 0) {
            getcwd(current, sizeof(current));
            printf("Directory Changed Successfully.\n");
            printf("New Directory: %s\n", current);
        } else {
            perror("Error");
        }
    }

    return 0;
}
