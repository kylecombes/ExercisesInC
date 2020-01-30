/**
 * This code counts playing cards that the user enters.
 *
 * Created by Kyle Combes on 1/25/2020 for the Software Systems class at Olin
 * College of Engineering.
 */

#include <stdio.h>
#include <stdlib.h>

void get_card_name(char *prompt, char *card_name);
int get_card_value(char *prompt);
int count_next_card(int *count);

/**
 * Prompts the user to enter a single card and then stores the user's input in
 * the provided buffer.
 * @param prompt the prompt to display to the user when asking for input
 * @param card_name the buffer in which to store the user's input
 */
void get_card_name(char *prompt, char *card_name) {
    puts(prompt);
    scanf("%2s", card_name);
}

/**
 * Prompts the user to enter a single card and then determines the card's value.
 * Aces are worth 11, face cards are worth 10, and the rest are worth their
 * numeric face value.
 * @param prompt the prompt to display the user when asking for input
 * @return the value of the card ([0, 11]) or -1 if the card is not recognized
 */
int get_card_value(char *prompt) {
    int cardVal;
    char card[3];
    get_card_name(prompt, card);
    /* Parse the inputted string */
    switch (card[0]) {
        case 'X': /* Exit */
        case 'x':
            return 0;
        case 'K':
        case 'k':
        case 'Q':
        case 'q':
        case 'J':
        case 'j':
            return 10;
        case 'A':
        case 'a':
            return 11;
        default:
            /* Attempt to parse the input as an integer */
            cardVal = atoi(card);
            if (1 <= cardVal && cardVal <= 10) {
                return cardVal;
            } else {
                /* Illegal value */
                return -1;
            }
    }
}

/**
 * Asks the user to enter the next card and then updates the count based on the
 * card the user has entered.
 * Question: What is the best way to achieve this functionality (i.e. both
 * sending continue/exit messages and updating an int)?
 * @param count a pointer to the current count. The value will be updated
 * with the new count.
 * @return a status code corresponding to what the user entered (1 for a valid
 * input, 0 for an exit command, or -1 for an invalid input)
 */
int count_next_card(int *count) {
    int cardVal = get_card_value("Enter the card name: ");
    if (cardVal == -1) { /* Invalid input */
        puts("Sorry, your input could not be interpreted as a card.\n"
             "Valid inputs are A, K, Q, J, or a number between 1 and 10.\n"
             "Entering 0 will result in the program terminating.");
        return -1;
    } else if (cardVal == 0) { /* Exit command */
        /* Time to exit */
        return 0;
    } else if (2 < cardVal && cardVal < 7) {
        *count += 1;
    } else if (cardVal == 10) {
        *count -= 1;
    }
    /* Continue running */
    return 1;
}

int main() {
    int count = 0;
    do {
        printf("Count is %d.\n", count);
    }
    while (count_next_card(&count));
    return 0;
}
