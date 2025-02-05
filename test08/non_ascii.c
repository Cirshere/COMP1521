// Takes filename, if non-ascii print location
// Else print all is ascii

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    char *filename = argv[1];
    
    FILE *fp = fopen(filename, "r");
    
    int i = 0;
    int ch = fgetc(fp);
    
    while (ch != EOF) {
        
        if (ch >= 128 && ch <= 255) {
            printf("%s: byte %d is non-ASCII\n", filename, i);
            return 0;
        }
        
        ch = fgetc(fp);
        i++;
    }

    printf("%s is all ASCII\n", filename);

    return 0;
}
