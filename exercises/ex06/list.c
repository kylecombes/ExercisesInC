/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
*
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {
    if (*list == NULL) return -1;
    Node *oldHead = *list;
    int val = oldHead->val;
    *list = oldHead->next;
    free(oldHead);
    return val;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {
    Node *second = *list;
    Node *head = (Node *)malloc(sizeof(Node));
    head->val = val;
    head->next = second;
    *list = head;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {
    Node *prev;
    // Initialize the current node to be the first node in the list
    Node *curr = *list;
    // Move along the list until we find a node with the value we're looking for
    while (curr != NULL && curr->val != val) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return 0;
    }
    if (prev != NULL) {
        prev->next = curr->next;
        free(curr);
    } else { // Removing the first element in a list
        *list = curr->next;
    }

    return 1;
}


/* Reverses the elements of the list.
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
    Node *prev = *list;
    Node *current = prev->next;
    prev->next = NULL;
    Node *next;
    while (current != NULL) {
        // Keep track of the next node in the old list
        next = current->next;
        // Flip the direction the current node points
        current->next = prev;
        // Move the node pointers down the line
        prev = current;
        current = next;
    }
    *list = prev;
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    Node **list = &head;
    print_list(list);

    int retval = pop(list);
    print_list(list);

    push(list, retval+10);
    print_list(list);

    remove_by_value(list, 3);
    print_list(list);

    remove_by_value(list, 7);
    print_list(list);

    reverse(list);
    print_list(list);
}
