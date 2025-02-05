// Compare two files and prints if identical or not

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    char *filename1 = argv[1];    
    FILE *fp1 = fopen(filename1, "r");    
    char *filename2 = argv[2];   
    FILE *fp2 = fopen(filename2, "r");

    int ch1 = fgetc(fp1);
    int ch2 = fgetc(fp2);
    int i = 0;
    
    while (ch1 != EOF && ch2 != EOF) {
    
        if (ch1 != ch2) {
        
            break;
        
        }
    
        i++;
        ch1 = fgetc(fp1);
        ch2 = fgetc(fp2);
    }
    
    if (ch1 == ch2) {
        printf("Files are identical\n");
    } else if (ch1 == EOF) {
        printf("EOF on %s\n", filename1);
    } else if (ch2 == EOF) {
        printf("EOF on %s\n", filename2);
    } else {
        printf("Files differ at byte %d\n", i);            
    }
    



    return 0;

}
