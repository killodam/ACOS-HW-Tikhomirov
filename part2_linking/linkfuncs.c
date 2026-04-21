#include <stdio.h>

void fred(void) { printf("[original] fred\n"); }
void john(void) { printf("[original] john\n"); }

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
