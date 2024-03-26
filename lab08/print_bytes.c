// Prints, byte, decimal and hexdecimal of arguments
// Christopher Hoang, z5259780
// 25/07/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    if (argc != 2) {
        fprintf (stderr, "Expected %s: <file_name>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror ("Couldn't open argv[1] for printing");
        exit(1);
    }
    
    
    int ch = fgetc(fp);
    int i = 0;
    while (ch != EOF) {
        printf("byte %4d: %3d 0x%02x ", i, ch, ch);
        if ((ch >= 65 && ch <= 127) || ch == ' ') {
            printf("'%c'", ch);
        }
        
        printf("\n");
        
        ch = fgetc(fp);
        i++;
    }    
    

    return 0;
}
