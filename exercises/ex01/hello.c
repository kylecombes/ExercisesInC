#include <stdio.h>

int test(char c);

int test(char c) {
    if (c == 'a') {
        return 5;
    } else if (c == 'b') {
        return 2;
    }
}

int main() {
    int x = 5;
    int *p;
    *p = x + 1;
    return 0;
}
