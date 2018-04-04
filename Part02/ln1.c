#define _POSIX_C_SOURCE 200809L

#include <unistd.h>

int main(int argc, char* argv[]){
    /* check num of args */
    if(argc != 3){
        write(1, "Incorrect number of arguments received.\n", 41);
        _exit(1);
    }

    if(link(argv[1], argv[2]) == -1){
        /* handle error */
        write(1, "An error occurred during operation.\n", 36);
        _exit(1);
    }
}
