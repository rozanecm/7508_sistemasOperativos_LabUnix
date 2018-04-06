#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>

void write_command(const char* path){
    FILE* f = fopen(path, "r");
    if(f == NULL){
        perror("error opening comm: ");
    }
    int pid, ppid, pgrp, session, tty_nr, tpgid;
    char comm[256];
    unsigned int flags;
    char state;
    fscanf(f, "%d %s %c %d %d %d %d %d %u", &pid, comm, &state, &ppid, &pgrp, 
            &session, &tty_nr, &tpgid, &flags);
    
    printf("%6d %20s %5c %4d %4d %8d %8d %8d %20u\n", pid, comm, state, ppid, 
            pgrp, session, tty_nr, tpgid, flags);

    fclose(f);
}

int main(){
    DIR* dir_ptr = opendir("/proc");
    /* error checking */
    if(dir_ptr == NULL){
        perror("An error occurred during command execution\n");
        _exit(EXIT_FAILURE);
    }

    /* print column headers */
    printf("%6s %20s %5s %4s %4s %8s %8s %8s %20s\n", "PID", "COMMAND", 
            "STATE", "PPID", "PGRP", "SESSION", "TTY_NR", "PTGID", "FLAGS");

    /* read dir */
    struct dirent* read_dir = readdir(dir_ptr);
    while(read_dir != NULL){
        if(isdigit(*read_dir->d_name)){
            /* case: dir corresponds to process */
            char path[267];
            sprintf(path, "/proc/%s/stat", read_dir->d_name);
            write_command(path);
        }
        read_dir = readdir(dir_ptr);
    }
    /* close dir */
    if(closedir(dir_ptr) == -1){
        perror("An error occurred during command execution.\n");
        _exit(EXIT_FAILURE);
    }
}
