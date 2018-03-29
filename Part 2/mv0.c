#include <stdio.h>

int main(int argc, char* argv[]){
    /* Se pide: Implementar mv0, que permite mover un archivo de un directorio a otro.
     *
     * Pre-condición: el archivo destino no existe.
     *
     * Syscalls recomendadas: rename.
     *
     * Pregunta: ¿se puede usar mv0 para renombrar archivos dentro del mismo directorio?
     * */
    rename(argv[1], argv[2]);
}
