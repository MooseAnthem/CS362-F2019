#ifndef CUSTOM_ASSERT
#define CUSTOM_ASSERT

#include <stdio.h>
#include <stdlib.h>

#define PASS 1
#define FAILURE 0

void customAssert(char message[], int assertion) {
    if(assertion) {
        printf("%s: TRUE\n", message);
    }
    else {
        printf("%s: FALSE\n", message);
    }
}

#endif