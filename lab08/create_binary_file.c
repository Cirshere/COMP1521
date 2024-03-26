// Takes at least one argument, Creates file of name and bytes of following arg
// Christopher Hoang, z5259780
// 26/07/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    char *filename = argv[1];
    
    FILE *fp = fopen(filename, "w");
    
    if (fp == NULL) {
        return 0;
    }
    
    
    
    int i = 2;
    
    while (i < argc) {
        
        int byte = atoi(argv[i]);
        fputc(byte, fp);
        i++;
    }

    return 0;
}
