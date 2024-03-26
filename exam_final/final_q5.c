// Takes two names of environment as arguments. Print 1 iff both are the same
// value, otherwise print 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

    char *env1 = getenv(argv[1]);
    char *env2 = getenv(argv[2]);
    
    if (env1 == env2) {
        printf("1\n");
    
    } else { 
        printf ("0\n"); 
    }

    return 0;
}
