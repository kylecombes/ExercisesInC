/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// This function creates a new array of integers of length SIZE (5) and sets all
// of its values to 42. It then returns (a pointer to) the array.
// My guess is that this won't work as expected because array is stored
// in the stack and deallocated once the function returns.
int *foo() {
    int i;
    int array[SIZE];

//    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}
// Yeah, gcc warns that the variable I'm returning is in a region of the stack
// due to be deallocated.

// This function creates a new array of integers of length SIZE (5) and sets
// each value to correspond to its index. It returns nothing.
void bar() {
    int i;
    int array[SIZE];

//    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

// The programmer likely intends for the output to be
// 42
// 42
// 42
// 42
// 42
// but that probably isn't going to be the case, since array points to a location
// in the stack that has been deallocated. Since foo() and bar() both allocate
// the same variables, it's possible that the output will be
// 0
// 1
// 2
// 3
// 4
// indicating bar()'s array variable was allocated at the same address in
// memory as foo()'s was.
int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
// Running this results in a segfault, which seems to indicate that I can't
// access a part of memory beyond the last stack frame (even if that memory was
// previously a part of the stack).

// After commenting out the print statements, I still get a segfault. ;(