#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to check if a file has a .c extension
int has_c_extension(const char *filename) {
    return strstr(filename, ".c") != NULL;
}

// Function to remove the .c extension and append a new suffix
void generate_file_name(const char *input_file, char *output_file, const char *suffix) {
    snprintf(output_file, 256, "%s", input_file);
    output_file[strlen(output_file) - 2] = '\0'; // Remove `.c`
    snprintf(output_file + strlen(output_file), 256 - strlen(output_file), "%s", suffix);
}

// Function to preprocess the file using GCC
int preprocess_file(const char *input_file, const char *suffix) {
    char preprocessed_file[256];
    generate_file_name(input_file, preprocessed_file, suffix);

    char command[512];
    snprintf(command, sizeof(command), "gcc -E -P %s -o %s", input_file, preprocessed_file);

    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Error: Failed to preprocess %s\n", input_file);
        remove(preprocessed_file); // Clean up preprocessed file
        return 1;
    }

    return 0;
}

// Function to generate placeholder assembly code
int generate_assembly_file(const char *input_file, const char *suffix) {
    char asm_file[256];
    generate_file_name(input_file, asm_file, suffix);

    FILE *asm_output = fopen(asm_file, "w");
    if (!asm_output) {
        perror("fopen");
        return 1;
    }
    fprintf(asm_output, "This is placeholder assembly code\n");
    fclose(asm_output);

    return 0;
}

// Function to compile and link the file
int compile_and_link(const char *input_file, const char *suffix) {
    char executable_file[256];
    generate_file_name(input_file, executable_file, suffix);

    char command[512];
    snprintf(command, sizeof(command), "gcc -o %s %s", executable_file, input_file);

    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Error: Failed to compile %s\n", input_file);
        return 1;
    }

    printf("Compilation successful. Executable: %s\n", executable_file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source-file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    if (!has_c_extension(input_file)) {
        fprintf(stderr, "Error: Input file must have a .c extension\n");
        return 1;
    }

    if (preprocess_file(input_file, ".i") != 0) {
        return 1;
    }

    if (generate_assembly_file(input_file, ".s") != 0) {
        return 1;
    }

    if (compile_and_link(input_file, "") != 0) {
        return 1;
    }

    return 0;
}
