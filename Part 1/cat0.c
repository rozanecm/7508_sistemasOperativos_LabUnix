#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

void my_write(void* buf, short count){
	/* On program startup, the integer file descriptors associated with the
	 * streams stdin, stdout, and stderr are 0, 1, and 2, respectively.
	 * The preprocessor symbols STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO
	 * are defined with these values in <unistd.h>.
	 * (Applying freopen(3) to one of these streams can change the file
	 * descriptor number associated with the stream.)
	 * */

	ssize_t num_of_written_bytes = write(STDIN_FILENO, buf, count);
	while(num_of_written_bytes < count){
		num_of_written_bytes += write(STDIN_FILENO, buf + num_of_written_bytes,
                                      count - num_of_written_bytes);
	}
}

int main(int argc, char* argv[]){
	/* Pre-condición: solo se pasa un archivo,
	 * y el archivo existe y tiene permisos de lectura */

	// get file descriptor for file in path
	int fd = open(argv[1], O_RDONLY); 
	
	// read file
	//read by chunks of size 1KB
	size_t count = 1024;	
	char* buf[count];
    short num_of_read_bytes = read(fd, buf, count);
	while(num_of_read_bytes != 0){
		my_write(buf, num_of_read_bytes);
        num_of_read_bytes = read(fd, buf, count);
	}
	close(fd);
}
