// Saves directory tree as a single file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int save();
int recreate();

int main (int argc, char *argv[]) {

    if (argc == 3) {
        save()
    } else if (argc == 2) {
        recreate();
    }
    
    return 0;
}

int save() {
    
    FILE *fp = fopen(argv[1], "a");
    
    struct stat sb;
    lstat(argv[2], &sb);
    
    if (sb.st_mode & S_IFDIR) {
        fputc('d', fp);
    } else {
        fputc('-', fp);
    }
    
    if (sb.st_mode & S_IRUSR) {
        fputc('r', fp);
    } else {
        fputc('-', fp);
    }
    
    if (sb.st_mode & S_IWUSR) {
        fputc('w', fp);
    } else {
        fputc('-', fp);
    }

    if (sb.st_mode & S_IXUSR) {
        fputc('x', fp);
    } else {
        fputc('-', fp);
    }

    if (sb.st_mode & S_IRGRP) {
        fputc('r', fp);
    } else {
        fputc('-', fp);
    }

    if (sb.st_mode & S_IWGRP) {
        fputc('w', fp);
    } else {
        fputc('-', fp);
    }
    
    if (sb.st_mode & S_IXGRP) {
        fputc('x', fp);
    } else {
        fputc('-', fp);
    }
    
    if (sb.st_mode & S_IROTH) {
        fputc('r', fp);
    } else {
        fputc('-', fp);
    }    
    
    if (sb.st_mode & S_IWOTH) {
        fputc('w', fp);
    } else {
        fputc('-', fp);
    }    

    if (sb.st_mode & S_IXOTH) {
        fputc('x', fp);
    } else {
        fputc('-', fp);
    }
    
    fputc(' ', fp);
    
    fputs(sb.st_nlink, fp);
    fputc(' ', fp);    
    
    fputs(sb.st_uid, fp);
    fputc(' ', fp);
    
    fputs(sb.st_gid, fp);
    fputc(' ', fp);
    
    fputs(sb.st_size, fp);    
    fputc(' ', fp);
            
    return 0;
}

int recreate() {
    
    
    return 0;
}
