#include <stdio.h>
#include "artemis.h"

int main(void) {
    Configuracion config;
    Mision historial[MAX_MISIONES] = {0}; /* Arreglo estatico de misiones */
    int cantidad = 0;
    int proximo_numero = 1;
    char entrada[80];
    char sobrante;
    int opcion, posicion;

    configuracion_inicial(&config);

    do {
        puts("\n===== SIMULADOR ARTEMIS SLS =====");
        puts("1. Ver configuracion inicial");
        puts("2. Simular ascenso del SLS");
        puts("3. Consultar historial");
        puts("4. Eliminar una mision del historial");
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
                if (cantidad >= MAX_MISIONES) {
                    puts("Historial completo: maximo 20 misiones.");
                } else if (ejecutar_mision(&config, &historial[cantidad], proximo_numero)) {
                    mostrar_mision(&historial[cantidad]);
                    cantidad++;
                    proximo_numero++;
                } else {
                    puts("ERROR: no se pudo realizar la simulacion.");
                }
                break;
            case 3:
                mostrar_historial(historial, cantidad);
                if (cantidad > 0) {
                    printf("Ver detalle por posicion (0 para volver): ");
                    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
                        puts("Fin de entrada.");
                        opcion = 0;
                        break;
                    }
                    if (sscanf(entrada, " %d %c", &posicion, &sobrante) != 1 ||
                        posicion < 0 || posicion > cantidad) {
                        puts("Posicion invalida.");
                    } else if (posicion != 0) {
                        mostrar_mision(&historial[posicion - 1]);
                    }
                }
            case 4:
                if (cantidad == 0) {
                    puts("No hay misiones para eliminar.");
                    break;
                }
                mostrar_historial(historial, cantidad);
                printf("Posicion a eliminar (0 para cancelar): ");
                if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
                    puts("Fin de entrada.");
                    opcion = 0;
                    break;
                }
                if (sscanf(entrada, " %d %c", &posicion, &sobrante) != 1 ||
                    posicion < 0 || posicion > cantidad) {
                    puts("Posicion invalida.");
                } else if (posicion != 0 &&
                        eliminar_mision(historial, &cantidad, posicion - 1)) {
                    puts("Mision eliminada del historial.");
                }
                break;
                break;
            case 0:
                puts("Fin del programa.");
                break;
            default:
                puts("Seleccione una opcion entre 0 y 4.");
        }
    } while (opcion != 0);

    return 0;
}
