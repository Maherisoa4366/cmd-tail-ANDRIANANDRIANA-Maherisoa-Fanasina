#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

void tail(FILE *file, int num_lines) {
    char **buffer = malloc(num_lines * sizeof(char *));
    for (int i = 0; i < num_lines; i++) {
        buffer[i] = malloc(MAX_LINE_LEN * sizeof(char));
        buffer[i][0] = '\0';
    }

    int current_line = 0;
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        strcpy(buffer[current_line], line);
        current_line = (current_line + 1) % num_lines;
    }

    for (int i = 0; i < num_lines; i++) {
        int index = (current_line + i) % num_lines;
        if (buffer[index][0] != '\0') {
            printf("%s", buffer[index]);
        }
    }

    for (int i = 0; i < num_lines; i++) {
        free(buffer[i]);
    }
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <num_lines>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int num_lines = atoi(argv[2]);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    tail(file, num_lines);

    fclose(file);
    return 0;
}