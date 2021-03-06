#define _POSIX_C_SOURCE 200809L

#include <unistd.h>

int main(int argc, char* argv[]){
    /* Se pide: Implementar ln0 que permite crear enlaces simbólicos.
     *
     * Pre-condición: no existe un archivo con el nombre del enlace.
     *
     * Syscalls recomendadas: symlink.
     *
     * Pregunta: ¿Qué ocurre si se intenta crear un enlace a un archivo 
     * que no existe?
     * Si ejecutamos el comando ll, se puede ver que el enlace fue creado.
     * Sin embargo, hay que tener en cuenta que el enlace creado apunta 
     * a un archivo inexistente. 
     * */
    
    /* check for correct number of args */
    if (argc != 3){
        write(1, "2 args must be passed.\n", 23);
        _exit(1);
    }

    symlink(argv[1], argv[2]);
}
