// Appends to a diary a single line
// Christopher Hoang, z5259780
// 08/08/20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    char *home = getenv("HOME");
    if (home == NULL) {
        home = ".";
    }
    
    int size = strlen(home) + strlen(".diary") + 1 + 1;
    char full_path[size];
    
    snprintf(full_path, size, "%s/.diary", home);
    
    FILE *fp = fopen(full_path, "a+");
    if (fp == NULL) {
        perror(full_path);
        exit(0);
    }
    
    for (int i = 1; i < argc; i++) {
        char *input = argv[i];
        fputs (input, fp);
        fputc (' ', fp);    
    }  
    
    fputc ('\n', fp);


    return 0;

}
