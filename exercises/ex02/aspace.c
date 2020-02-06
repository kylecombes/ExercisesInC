/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void run_me() {
    int var = 4;
    printf("run_me: var points to %p\n", &var);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *q = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("q points to %p\n", q);
    printf ("s points to %p\n", s);

    run_me();

    void *a = malloc(16);
    void *b = malloc(16);
    printf ("a points to %p\n", a);
    printf ("b points to %p\n", b);
    // Difference of 20 bytes

    return 0;
}
