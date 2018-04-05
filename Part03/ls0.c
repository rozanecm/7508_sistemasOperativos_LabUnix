#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     //necessary for free()
#include <sys/stat.h>
#include <errno.h>

void free_res(DIR* dir, int argc, char* path){
    closedir(dir);
    if(argc == 1){
        free(path);
    }
}

int main(int argc, char* argv[]){
    /* evaluate num of args */
    char* path;
    if(argc == 1){
        /* path is current path */
        path = get_current_dir_name();
    }else{
        path = argv[1];
    }

    /* check that given path is a dir */
    //TODO correct verification. Currently not working.
    /*
    struct stat buf;
    stat(path, &buf);
    if(S_ISDIR(buf.st_mode)){
        write(1, "Given path is not a dir.\n", 25);
        _exit(1);
    }
    */

    DIR* dir_ptr = opendir(path);
    if(dir_ptr == NULL){
        perror("Error occurred opening dir.");
        write(1, "An error occurred during command execution.\n", 44);
        /* exit with error exit code */
        _exit(1);
    }
    struct dirent* read_dir = readdir(dir_ptr);
    int current_errno = errno;
    while(read_dir != NULL){
        if(current_errno != errno){
            /* theres an error */
            write(1, "An error occurred during command execution.\n", 44);
            free_res(dir_ptr, argc, path);
            _exit(1);
        }
        printf("%s\n", read_dir->d_name);
        read_dir = readdir(dir_ptr);
        current_errno = errno;
    }
    free_res(dir_ptr, argc, path);
}

