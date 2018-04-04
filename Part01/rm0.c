#include <unistd.h>

int main(int argc, char* argv[]){
    /* Implementar rm0 que elimina un archivo regular.
     * Pre-condicion: el archivo existe y es regular. */
    unlink(argv[1]);
}
