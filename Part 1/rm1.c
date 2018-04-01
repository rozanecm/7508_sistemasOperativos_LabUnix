#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[]){
    /* check number of args received. */
    if(argc != 2){
        write(1, "file to remove should be passed as arg.\n", 40);
    }

    struct stat buf;
    if(stat(argv[1], &buf) == -1){
        write(1, "An error occurred retrieving information from path.\n", 51);
        _exit(1);
    }

    if(buf.st_mode == S_IFDIR){
        /* print error msg */
        perror("cannot remove ");
        perror(argv[1]);
        perror(": Is a directory");

        /* set errno */
        errno = 1;

        /* exit with error code */
        _exit(1);
    }

    if(unlink(argv[1]) == -1){
        write(1, "An error occurred removing file.\n", 33);
    }
}
