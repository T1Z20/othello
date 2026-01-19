#include <stdio.h>
#include "othello.h"



int main(int argc, char const *argv[]) {
    //verifica que el nombre del archivo este como argumento 
    if (argc != 2) {
        printf("Uso: %s <archivo_entrada>\n", argv[0]);
        return 1;
    }
    //En caso de estarlo intenta abrirlo 
    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
    //si es posible , procesa el mismo 
    validarYprocesar_archivo(archivo);
    // cierra el archivo 
    fclose(archivo);
    return 0;
}