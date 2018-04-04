#include <unistd.h>

int main(int argc, char* argv[]){
    /* Implementar rm0 que elimina un archivo regular.
     * Pre-condicion: el archivo existe y es regular. */

    /* check num of args */
    if(argc != 2){
        write(1, "Incorrect number of args received.\n", 35);
        _exit(1);
    }
    unlink(argv[1]);
}
