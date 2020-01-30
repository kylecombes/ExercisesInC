#include <stdio.h>

int main() {
    // This line will converted to assembly both with and without the -O2 flag
    // when x is referenced in the following line. If x is never accessed, then
    // only the non-optimized compilation will generate assembly code.
    int x = 5;
    //printf("Hello, World! %d\n", x);
    // This line is converted to assembly in the non-optimized compilation, but
    // not when the -O2 flag is used.
    int y = x + 1;
    // When the following line is added, both x and y are kept in the assembly
    // code in the non-optimized version. In the optimized version, y is
    // set to be 6 from the get-go and x is dropped entirely.
    printf("And our number is: %d", y);
    return 0;
}
