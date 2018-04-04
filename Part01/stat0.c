#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

ssize_t my_strlen(char* buf){
    ssize_t size = 0;
    while(buf[size] != '\0'){
        size++;
    }
    return size;
}

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

void my_reverse_string(char* buf, int len){
    ssize_t i = 0;
    char c;
    while(i <= len/2){
        c = buf[i];
        buf[i] = buf[len-i-1];
        buf[len-i-1] = c;
        ++i;
    }
}


void uint_to_string(unsigned int src, char* dest){
    int i = 0;
    while(src > 0){
        unsigned int last_digit = src%10;
        /* 0 is 48 in ASCII. All numbers are ordered, so the corresponding ASCII
         * code of a number is the number + 48.
         * */
        unsigned int temp = last_digit + 48;
        dest[i] = (char)temp;
        src /= 10;
        ++i;
    }
    dest[i] = '\0';
    my_reverse_string(dest, i);
}

int main(int argc, char* argv[]){
    /* La implementación de stat0 mostrará únicamente el nombre, 
     * tipo y tamaño del archivo (en bytes). 
     *
     * Implementar stat0 que muestra el nombre, tipo y tamaño en bytes 
     * de un archivo regular o directorio.
     *
     * Pre-condición: el archivo existe, y es un directorio o un archivo regular.
     * */

    /* First, show file's name */
	
    char* out = "File name:\t\t\t";

    my_write(out, my_strlen(out));
    my_write(argv[1], my_strlen(argv[1]));
    my_write("\n", 1);
	
    /* Now show file's type */
	
    struct stat buf;
    stat(argv[1], &buf);

    out = "File type:\t\t\t";
    my_write(out, my_strlen(out));  

    if(S_ISDIR(buf.st_mode)){
        out = "Directory\n";
        my_write(out, my_strlen(out));
    }else if(S_ISREG(buf.st_mode)){
        out = "Regular file\n";
        my_write(out, my_strlen(out));
    }
	
    out = "File size (in bytes):\t\t";
    my_write(out, my_strlen(out));	
    int size = buf.st_size;
    /* We won't need more than five chars to write the number */
    char c_size[] = "aaaaaa";
    uint_to_string(size, c_size);
    my_write(c_size, my_strlen(c_size));
    my_write("\n", 1);
}
