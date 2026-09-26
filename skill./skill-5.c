#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

void parse(char *input) {
    char token[MAX];
    int i = 0, j = 0;
    char quote = 0;

    while (input[i] != '\0') {

        if (input[i] == '\'' || input[i] == '"') {
            quote = input[i++];
            j = 0;

            while (input[i] != '\0' && input[i] != quote)
                token[j++] = input[i++];

            if (input[i] == quote)
                i++;

            token[j] = '\0';

            printf("Quoted: %s\n", token);
        }

        else if (input[i] != ' ' && input[i] != '\n') {
            j = 0;

            while (input[i] != '\0' &&
                   input[i] != ' ' &&
                   input[i] != '\'' &&
                   input[i] != '"' &&
                   input[i] != '\n') {
                token[j++] = input[i++];
            }

            token[j] = '\0';

            printf("Token: %s\n", token);
        }

        else {
            i++;
        }
    }
}

int main() {
    char input[MAX];

    printf("Enter input: ");
    fgets(input, MAX, stdin);

    if (strlen(input) <= 1) {
        printf("Empty input\n");
        return 0;
    }

    printf("\nParsing Result:\n");
    parse(input);

    return 0;
}
