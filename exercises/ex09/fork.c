/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

const char *A_STRING = "Hello there!";


// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    double secs = get_seconds();
    char *mallocedC = (char *) malloc(sizeof(char));
    sleep(i);
    printf("Hello from child %d.\n", i);
    printf("Child %d has secs addr (stack) of %p\n", i, &secs);
    printf("Child %d has mallocedC addr (heap) of %p\n", i, mallocedC);
    printf("Child %d has A_STRING (const) addr of %p\n", i, &A_STRING);
    /*
     Output:
        Creating child 0.
        Creating child 1.
        Hello from the parent.
        Hello from child 0.
        Child 0 has secs addr (stack) of 0x7ffe6a13d198
        Child 0 has mallocedC addr (heap) of 0x55e64b537670
        Child 0 has A_STRING (const) addr of 0x55e64a2b0010
        Child 30873 exited with error code 0.
        Hello from child 1.
        Child 1 has secs addr (stack) of 0x7ffe6a13d198
        Child 1 has mallocedC addr (heap) of 0x55e64b537670
        Child 1 has A_STRING (const) addr of 0x55e64a2b0010
        Child 30874 exited with error code 1.
        Elapsed time = 1.002449 seconds.
     Since the virtual addresses are the same but each process must not have
     access to the other processes' data, then the processes must have different
     memory segments.

     I can't think of a way to check whether or not they share the same code and
     static segments. They should share the code segment, per the last comment
     on https://www.geeksforgeeks.org/fork-memory-shared-bw-processes-created-using/,
     and (also per that comment) it seems that static should be shared until
     one of them changes their copy.
     */
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
