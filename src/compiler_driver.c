#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source-file>\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    if (!strstr(input_file, ".c")) {
        fprintf(stderr, "Error: Input file must have a .c extension\n");
        return 1;
    }

    // Generate assembly file name
    char asm_file[256];
    snprintf(asm_file, sizeof(asm_file), "%s.s", input_file);

    // Generate executable file name
    char executable_file[256];
    snprintf(executable_file, sizeof(executable_file), "%s", input_file);
    executable_file[strlen(executable_file) - 2] = '\0';  // Remove `.c`

    // Compile the C file to assembly (placeholder logic here)
    FILE *asm_output = fopen(asm_file, "w");
    if (!asm_output) {
        perror("fopen");
        return 1;
    }
    fprintf(asm_output, "This is placeholder assembly code\n");
    fclose(asm_output);

    // Assemble and link using gcc
    char command[512];
    snprintf(command, sizeof(command), "gcc -o %s %s", executable_file, input_file);

    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Error: Failed to compile %s\n", input_file);
        remove(asm_file);  // Clean up assembly file
        return 1;
    }

    // Success
    printf("Compilation successful. Executable: %s\n", executable_file);
    return 0;
}
