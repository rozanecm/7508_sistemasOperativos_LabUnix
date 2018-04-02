#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <utime.h>

int main(int argc, char* argv[]){
    if (argc != 2){
        write(1, "Incorrect num. or args. received.\n", 34);
        _exit(1);
    }
    
    /* 436 is the bit mask which gives the following permissions: 
     *      USER:   read, write
     *      GROUP:  read, write
     *      OTHERS: read
     * */
    int fd = open(argv[1], O_CREAT | O_EXCL, 436);
    if(fd == -1 && errno == EEXIST){
        write(1, "fd = -1...\n", 11);
        /* file already exists */
        fd = open(argv[1], O_RDWR);
        if(fd == -1){
            write(1, "Path specified indicates no file, and an error occurred creating the file.\n", 75);
            _exit(1);
        }

        if(utime(argv[1], NULL) == -1){
            write(1, "An error occurred during the operation.\n", 40);
        }
    }
    close(fd);
}
