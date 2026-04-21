#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

void bill(void) {
    printf("[load-time interposed] bill is called\n");
    void (*orig)(void) = dlsym(RTLD_NEXT, "bill");
    if (orig) orig();
}

void sam(void) {
    printf("[load-time interposed] sam is called\n");
    void (*orig)(void) = dlsym(RTLD_NEXT, "sam");
    if (orig) orig();
}
