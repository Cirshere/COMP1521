// Takes argument, prints 1 if file &HOME/.diary exists and is publically
// readable. Else print 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

    char *home = getenv("HOME");
    if (home == NULL) {
        printf("0\n");
        exit(0);
    } 
    
    int size = strlen(home) + strlen(".diary") + 1 + 1;
    char full_path[size];
    
    snprintf(full_path, size, "%s/.diary", home);
    
    FILE *fp = fopen(full_path, "r");
    if (fp == NULL) {
        printf("0\n");
        exit(0);
    }
    
    struct stat sb;
    lstat (full_path, &sb);
    
    if (sb.st_mode & S_IRGRP && sb.st_mode & S_IROTH) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;

}
