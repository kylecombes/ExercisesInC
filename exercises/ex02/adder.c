/*
 * Adds number entered by the user.
 *
 * Created by Kyle Combes for Software Systems (SP20).
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 10

/**
 * Checks if a string is a valid integer. Negative numbers are permitted.
 * @param s the string to check
 * @return 1 if the string is numeric, 0 otherwise
 */
int is_numeric(char *s) {
    // The first character can be numeric or a minus sign (-)
    if (!isdigit(s[0]) && s[0] != '-') {
        return 0;
    }
    // The rest have to be numeric
    for (int i = 1; i < strlen(s); ++i) {
        if (!isdigit(s[i]) && s[i] != EOF) {
            return 0;
        }
    }
    return 1;
}

/**
 * Reads a number from stdin and attempts to parse it as an integer.
 * @param res a pointer to where valid input should be stored
 * @return 'v' if the user entered a valid integer, 'i' if it the input was
 * invalid, or 'e' if the user pressed Control-D
 */
char get_number_from_user(int *res) {
    char input[9];
    int scanf_result = scanf("%8s", input);
    if (scanf_result == 0) { // Check if input invalid
        return 'i';
    } else if (scanf_result == EOF) { // User pressed Control-D
        return 'e';
    }
    if (!is_numeric(input)) {
        return 'i';
    }
    *res = atoi(input);
    return 'v';
}

/**
 * Sums the elements in an array.
 * @param number_array numbers to sum
 * @return the sum of the elements of the array
 */
int sum_array(int number_array[]) {
    int sum = 0;
    for (int i = 0; i < MAX_TERMS; ++i) {
        sum += number_array[i];
    }
    return sum;
}

void main() {
    puts("This program will add a series of numbers.\n\n");
    puts("Please enter each of your numbers on a new line. To exit, press "
         "Ctrl-D.");
    puts("Input: ");

    int numbers[MAX_TERMS];
    for (int i = 0; i < MAX_TERMS; ++i) {
        numbers[i] = 0;
    }

    int count = 0;
    int input = 0;
    while (1) {
        char res = get_number_from_user(&input);
        if (res == 'v') {
            if (count == MAX_TERMS) {
                puts("You have already entered the maximum allowed number of "
                     "integers. Please press Control-D to sum them.");
            } else {
                numbers[count] = input;
                count++;
            }
        } else if (res == 'i') {
            puts("Please enter a valid integer or press Ctrl-D to exit.");
        } else { // Ctrl-D was pressed
            int sum = sum_array(numbers);
            printf("The sum of the numbers you entered is %d.", sum);
            break;
        }
    }
}
