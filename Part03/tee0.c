#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void my_write(int fd, void* buf, size_t count){
    size_t bytes_written = 0;
    while(bytes_written < count){
        bytes_written += write(fd, buf+bytes_written, count-bytes_written);
    }
}

int main(int argc, char* argv[]){
    /* check num of args */
    if(argc != 2){
        write(1, "Incorrect number or arguments.\n", 31);
        _exit(1);
    }

    /* by default create file. Then open the file with write permissions. */

    /* 436 is the bit mask which gives the following permissions: 
     *          USER:   read, write
     *          GROUP:  read, write
     *          OTHERS: read
     * */
    int fd = open(argv[1], O_CREAT | O_EXCL, 436);

    /* check for errors */
    if(fd != -1){
        /* if no error occurred */
        close(fd);
    }
    
    fd = open(argv[1], O_WRONLY);

    /* From read(2) man page: On success, the number of bytes read is 
     * returned (zero indicates end of file) */
    ssize_t bytes_read;

    /* read by 1K chunks */
    int buf_size = 1024;
    char buf[buf_size];

    /* fd = 0 indicates stdin */
    while((bytes_read = read(0, &buf, buf_size)) != 0){
        my_write(fd, &buf, bytes_read);
        my_write(1, &buf, bytes_read);
    }
    close(fd);
}
