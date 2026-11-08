#include <stdio.h>
#include "artemis.h"

int main(void) {
    Configuracion config;
    Mision mision;
    char entrada[80];
    char sobrante;
    int opcion;

    configuracion_inicial(&config);

    do {
        puts("\n===== SIMULADOR ARTEMIS SLS =====");
        puts("1. Ver configuracion inicial");
        puts("2. Simular ascenso del SLS");
        puts("0. Salir");
        printf("Seleccione una opcion: ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            puts("Fin de entrada.");
            break;
        }
        if (sscanf(entrada, " %d %c", &opcion, &sobrante) != 1) {
            puts("Opcion invalida.");
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                mostrar_configuracion(&config);
                break;
            case 2:
                if (ejecutar_mision(&config, &mision, 1)) {
                    mostrar_mision(&mision);
                } else {
                    puts("ERROR: no se pudo realizar la simulacion.");
                }
            case 0:
                puts("Fin del programa.");
                break;
            default:
                puts("Seleccione 0 o 1.");
        }
    } while (opcion != 0);

    return 0;
}
