// Takes filename as argument, counts no. of bytes of valid ASCII and
// print counts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    
    FILE *fp = fopen(argv[1], "r");
    
    int ch = fgetc(fp);
    int total =  0;
    
    while (ch != EOF) {
        
        if (ch >= 0 && ch <= 127) {
            total++;
        }
        
        ch = fgetc(fp);
    }
    
    printf("%s contains %d ASCII bytes\n", argv[1], total);
    
    fclose(fp);
    
    return 0;
}
