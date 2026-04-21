#include <stdio.h>
#include "myfuncs.h"

int main(void) {
    int x, y;
    printf("Enter x and y: ");
    scanf("%d %d", &x, &y);
    swap(&x, &y);
    printf("After swap: x = %d, y = %d\n\n", x, y);

    printf("-- link-time interposed --\n");
    fred();
    john();

    printf("\n-- load-time interposed (or original if no LD_PRELOAD) --\n");
    bill();
    sam();

    return 0;
}
