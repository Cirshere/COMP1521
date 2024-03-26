// Takes arguments as pathanmes. Prints the permissions of the files
// or directory.
// Christopher Hoang, z5259780
// 02/08/2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "%s: <path>...\n", argv[1]);
    }
    
    for (int i = 1; i < argc; i++) {
    
        struct stat sb;
        
        lstat(argv[i], &sb);
        
        if (sb.st_mode & S_IFDIR) {
            printf ("d");            
        } else {
            printf ("-");
        }
        
        if (sb.st_mode & S_IRUSR) {
            printf("r");
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IWUSR) {
            printf("w");
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IXUSR) {
            printf("x");
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IRGRP) {
            printf("r");
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IWGRP) {
            printf("w");
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IXGRP) {
            printf("x");
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IROTH) {
            printf("r");    
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IWOTH) {
            printf("w");
        } else {
            printf("-");
        }
        
        if (sb.st_mode & S_IXOTH) {
            printf("x");
        } else {
            printf("-");
        }
        
        printf(" %s\n", argv[i]);
    
    }

    return 0;

}
