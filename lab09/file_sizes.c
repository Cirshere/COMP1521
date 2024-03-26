// Takes arguments, prints the filename name and size in bytes of
// files. Print total size at the end.
// Christopher Hoang, z5259780
// 02/08/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "%s: <path> ...\n", argv[0]);
        exit(1);
    }
    
    long total = 0;
    
    for (int i = 1; i < argc; i++) {
        
        struct stat sb;
        
        stat(argv[i], &sb);
        
        printf("%s: %ld bytes\n", argv[i], sb.st_size); 
        
        total += sb.st_size;
    }
    
    printf ("Total: %ld bytes\n", total);
    
    


    return 0;
}
