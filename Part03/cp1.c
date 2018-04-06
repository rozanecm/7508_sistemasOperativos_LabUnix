#define _POSIX_C_SOURCE 200809L

#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     //for EXIT codes
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    /* check num of args */
    if(argc != 3){
        write(1, "Incorrect number or arguments.\n", 31);
        _exit(EXIT_FAILURE);
    }
    
    /* open src and dst file */
    int src_fd = open(argv[1], O_RDONLY);
    int dst_fd = open(argv[2], O_CREAT | O_RDWR, 436);

    /* check errors on file opening */
    if((src_fd == -1) || (dst_fd == -1)){
        write(1, "An error occurred opening files.\n", 33);
        if(src_fd != -1)
            close(src_fd);
        if(dst_fd != -1)
            close(dst_fd);
    }
    
    struct stat file_stat;
    if(stat(argv[1], &file_stat) == -1){
        write(1, "An error occurred during command execution.\n", 44);
        close(src_fd);
        close(dst_fd);
        _exit(EXIT_FAILURE);
    }
    int file_len = file_stat.st_size;

    if(ftruncate(dst_fd, file_len) == -1){
        perror("");
        write(1, "An error occurred during command execution.\n", 44);
        close(src_fd);
        close(dst_fd);
        _exit(EXIT_FAILURE);
    }
    
    /* get memory areas for both files */
    char* src_mapped_area = mmap(0 /* If addr is NULL, then the kernel chooses 
                                  the address at which to create the mapping */,
           /* length */ file_len,
           /* prot */ PROT_READ | PROT_WRITE,
           /* flags */ MAP_PRIVATE,
           /* fd */ src_fd,
           /* offset */ 0);

    char* dst_mapped_area = mmap(0 /* If addr is NULL, then the kernel chooses 
                                  the address at which to create the mapping */,
           /* length */ file_len,
           /* prot */ PROT_READ | PROT_WRITE,
           /* flags */ MAP_SHARED,
           /* fd */ dst_fd,
           /* offset */ 0);

    /* check errors on mmap */
    if((src_mapped_area == MAP_FAILED) || (dst_mapped_area == MAP_FAILED)){
        /* error occurred */
        perror("error with mmap");
        write(1, "An error occurred during command execution.\n", 44);
        _exit(EXIT_FAILURE);
    }

    /* copy data */
    memcpy(dst_mapped_area, src_mapped_area, file_len);

    if(((munmap(src_mapped_area, file_len)) == -1) || 
            (munmap(dst_mapped_area, file_len))){
        perror("");
        write(1, "An error occurred during command execution.\n", 44);
    }
    
    /* close files */
    if((close(src_fd) == -1) || (close(dst_fd) == -1)){
        perror("");
        write(1, "An error occurred when closing files.\n", 38);
        _exit(EXIT_FAILURE);
    }
}
