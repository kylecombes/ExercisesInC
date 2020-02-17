/*
 A simple implementation of the tee command.

 Created by Kyle Combes for Software Systems at Olin College.
*/

#include <stdio.h>
#include <string.h>

/**
 * Sets all of the elements in an array to be 0.
 * @param array the array to clean
 * @param size the length of the array
 */
void clear_array(char *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

/**
 * Reads lines from stdin and prints them to stdout and any files given.
 * @param append whether or not to append the new data to the files
 * @param files the files to write to
 * @param numFiles the number of files
 */
void read_from_stdin_until_eol(char append, FILE *files[], int numFiles) {
    char input[100];
    clear_array(input, 100);

    while (fgets(input, 100, stdin) != NULL) {
        // Print to stdout
        puts(input);

        // Write to files
        for (int i = 0; i < numFiles; i++) {
            fputs(input, files[i]);
        }
    }
}

/**
 * Closes a list of FILE *
 * @param files the files to close
 * @param numFiles the number of files
 */
void close_files(FILE *files[], int numFiles) {
    for (int i = 0; i < numFiles; i++) {
        fclose(files[i]);
    }
}

/**
 * Attempts to open a list of files.
 * @param filePaths the paths to the files to open
 * @param files the array to save the resulting list of FILE * to
 * @param numFiles the number of files to open
 * @param append whether or not to append to the files or to just overwrite
 * their content
 * @return whether or not all files were opened successfully
 */
int open_files(char *filePaths[], FILE *files[], int numFiles, char append) {
    char *accessMode = append ? "a" : "w";
    for (int i = 0; i < numFiles; i++) {
        FILE * file = fopen(filePaths[i], accessMode);
        if (file == NULL) {
            fprintf(stderr, "Error: Could not open file '%s'.\n", filePaths[i]);
            return -1;
        } else {
            files[i] = file;
        }
    }
    return 0;
}

int main (int argc, char *argv[]) {
    // Subtract 1 for because the first arg is the program name
    int numArgs = argc - 1;

    if (numArgs > 0) { // tee was called with some arguments
        // Check if the -a flag was specified
        char append = strcmp(argv[1], "-a") == 0;

        // Subtract 1 for the "-a", if needed
        int numFiles = append ? numArgs-1 : numArgs;

        // Skip past the "./tee" and "-a" (if applicable) components of argv
        char **filePaths = append ? argv+2 : argv+1;

        FILE *files[numFiles];
        if (open_files(filePaths, files, numFiles, append) != 0) {
            return -1;
        }
        read_from_stdin_until_eol(append, files, numFiles);
        close_files(files, numFiles);
    } else { // tee was called with no arguments
        FILE *files[0];
        read_from_stdin_until_eol(0, files, 0);
    }
}
