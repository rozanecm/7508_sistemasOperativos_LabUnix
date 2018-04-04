#include <unistd.h>
#include <sys/fcntl.h>

void my_write(int fd, const void *buf, size_t count){
    size_t bytes_written = 0;
    while(bytes_written < count){
        bytes_written += write(fd, buf+bytes_written, count-bytes_written);
    }
}

int main(int argc, char*argv[]){
    /* Se pide: Implementar cp0 que copia los contenidos de un archivo a otro. 
     * Utilizar para esta implementación las syscalls básicas de entrada y 
     * salida, esto es: open(2), read(2), write(2) y close(2).
     *
     * Pre-condición: el archivo de origen existe y es regular. El archivo 
     * destino no existe.
     * */

    /* check for correct num. of args. */
    if(argc != 3){
        write(1, "ERROR! Se deben recibir dos args.!\n", 35);
        _exit(1);
    }

    /* open files */
    int fd_origin = open(argv[1], O_RDONLY);
    int fd_des = open(argv[2], O_CREAT, 436);
    /* as newly created file can't have data written on it, we must close it
     * and re open it again. 
     * */
    close(fd_des);

    /* open destination file again, now as write only */
    fd_des = open(argv[2], O_WRONLY);
    
    /* copy */
    int chunk_size = 1024;      //read by 1Kb chunks
    char buf[chunk_size];
    int read_bytes;
    while((read_bytes = read(fd_origin, &buf, chunk_size)) > 0){
       my_write(fd_des, &buf, read_bytes);
    }

    /*close files */
    close(fd_origin);
    close(fd_des);
}
