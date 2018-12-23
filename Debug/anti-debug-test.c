#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void)
{
    printf("getsid: %d\n", getsid(getpid()));
    printf("getppid: %d\n", getppid());
 
        if (getsid(getpid()) != getppid()) {
        printf("traced!\n");
        exit(EXIT_FAILURE);
    }
        printf("OK\n");
 
    return 0;
}