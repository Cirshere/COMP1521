// Program that removes all ASCII characters

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    char *filename = argv[1];
    
    FILE *fp = fopen(filename, "r");
    FILE *ftemp = fopen("temp.txt", "w+");
    
    int ch = fgetc(fp);
    
    while (ch != EOF) {
    
        if (ch >= 0 && ch <= 127) {
            fputc(ch, ftemp);                           
        }
    
        ch = fgetc(fp);
    }
    
    fclose(fp);
    fclose(ftemp);
    
    rename("temp.txt", argv[1]);
    
    return 0;

}
