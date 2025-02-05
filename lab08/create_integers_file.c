// Accepts 3 arguments (1. Filename, beginning of range ints, end of range ints)
// Christopher Hoang, z5259780
// 24/07/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main (int argc, char *argv[]) {
    
   
    char *filename = argv[1];
    
    FILE *fp = fopen(filename, "w");
    
    int lower = atoi (argv[2]);
    int higher = atoi (argv[3]);
    
    while (lower <= higher) {
    
        fprintf(fp, "%d\n", lower);
    
        lower++;
    }
    
    fclose(fp);


    return 0;
}
