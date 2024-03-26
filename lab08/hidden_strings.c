// Takes argument (filename), reads files and prints sequences of length >= 4
// Christopher Hoang, z5259780
// 26/07/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    
    char *filename = argv[1];
    
    FILE *fp = fopen(filename, "r");
    
    int ch = fgetc(stdin);
    
    while (ch != EOF) {
        
        fputc(ch, fp);
        ch = fgetc(stdin);
    }

    return 0;
}
