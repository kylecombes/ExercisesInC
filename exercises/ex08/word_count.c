//
// Created by Kyle Combes for Software Systems at Olin College of Engineering.
//

#include <stdio.h>
#include <glib.h>

GHashTable *hashTable;

void print_hash_entry(void *k, void *v, void *data) {
    gchar *key = (gchar *) k;
    int *value = (int *) v;
    printf("%s: %d times\n", key, *value);
}

void print_hash_table() {
    g_hash_table_foreach(hashTable, print_hash_entry, NULL);
}

void process_line(char *line, size_t len) {
    gchar **tokens = g_strsplit(line, " ", len);

    gchar *key;
    while (tokens[0]) {
        key = tokens[0];
        // Check if token (string) is in map
        if (g_hash_table_contains(hashTable, key)) {
            // If so, increment count
            int *val = (int *)g_hash_table_lookup(hashTable, key);
            *val += 1;
        } else {
            // Insert this new word into the hash table and set its count to 1
            int *newVal = (int *)malloc(sizeof(int));
            *newVal = 1;

            g_hash_table_insert(hashTable, key, newVal);
        }
        ++tokens;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("USAGE: word_count FILE.");
        return -1;
    }

    FILE *file = fopen(argv[1], "r");

    char chunk[128];

    // Store the chunks of text into a line buffer
    size_t len = sizeof(chunk);
    char *line = malloc(len);
    if (line == NULL) {
        perror("Unable to allocate memory for the line buffer.");
        return 1;
    }

    hashTable = g_hash_table_new(g_str_hash, g_str_equal);

    // "Empty" the string
    line[0] = '\0';

    while (fgets(chunk, len, file) != NULL) {
        // Resize the line buffer if necessary
        size_t len_used = strlen(line);
        size_t chunk_used = strlen(chunk);

        if (len - len_used < chunk_used) {
            len *= 2;
            if ((line = realloc(line, len)) == NULL) {
                perror("Unable to reallocate memory for the line buffer.");
                free(line);
                return 1;
            }
        }

        // Copy the chunk to the end of the line buffer
        strncpy(line + len_used, chunk, len - len_used);
        len_used += chunk_used;

        // Check if line contains '\n', if yes process the line of text
        if (line[len_used - 1] == '\n') {
            line[len_used - 1] = NULL;
            process_line(line, len);
            // "Empty" the line buffer
            line[0] = '\0';
        }
    }

    print_hash_table();

    return 0;
}
