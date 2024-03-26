// Takes 1 arguement (name of enviro variable). If varible is non-empty
// print 1, otherwise print 0.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    char *path = getenv(argv[1]);
    if (path == NULL){
        printf ("0\n");
        exit(0);
    }
    
    int len = strlen(argv[1]); 

    

    if (strlen (path) < len) {
        printf ("0\n");
    } else {
        printf ("1\n");
    }
    
    return 0;

}
