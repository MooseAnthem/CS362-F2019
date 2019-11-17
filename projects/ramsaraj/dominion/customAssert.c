#ifndef CUSTOM_ASSERT
#define CUSTOM_ASSERT

#include <stdio.h>
#include <stdlib.h>

#define PASS 1
#define FAILURE 0

int customAssert(char message[], int assertion) {
    if(assertion) {
        //printf("%s: TRUE\n", message);
        return 0;
    }
    else {
        printf("%s\n", message);
        return 1;
    }
}

#endif