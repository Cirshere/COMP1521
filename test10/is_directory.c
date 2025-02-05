// Takes 1 argument as a pathname. If it exists and is a directory, print 1,
// otherwise print 0.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

    FILE *fp =  fopen(argv[1], "r");
    if (fp == NULL) {
        printf("0\n");
        exit(0);
    }

    struct stat sb;
    lstat(argv[1], &sb);
    
    if (sb.st_mode & S_IFDIR) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;

}
