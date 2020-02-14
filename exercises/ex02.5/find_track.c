/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

/**
 * Match string against the extended regular expression in
 * pattern, treating errors as no match.
 * @param string the string to search
 * @param pattern the pattern to use when checking the string
 * @return 1 for match, 0 for no match
 */

int match(const char *string, char *pattern)
{
    int status;
    regex_t re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "An error was encountered when compiling a regex for "
                         "the pattern '%s'.\n", pattern);
        exit(1);
    }
    // Look for our pattern in the string
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    // Free the memory allocated to the pattern buffer
    regfree(&re);
    // Check our result code
    if (status == 0) { // Match!
        return(1);
    }
    // No match :(
    return(0);
}

/**
 * Finds all tracks that match the given pattern and prints the track number
 * and title of all matches.
 * @param pattern the regex pattern to match
*/
void find_track_regex(char pattern[])
{
    for (int i = 0; i < NUM_TRACKS; ++i) {
        if (match(tracks[i], pattern)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    /*
    char search_for[80];

    /* take input from the user and search *
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    find_track(search_for);*/
    find_track_regex("[A-F]");

    return 0;
}
