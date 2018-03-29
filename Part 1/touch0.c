#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    if (argc != 2){
        //TODO print error msg
        _exit(1);
    }
    /* 436 is the bit mask which gives the following permissions: 
     *      USER:   read, write
     *      GROUP:  read, write
     *      OTHERS: read
     * */
    int fd = open(argv[1], O_CREAT, 436);
    close(fd);
}
