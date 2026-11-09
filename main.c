#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

int main(void) {
    Configuracion config;
    Mision historial[MAX_MISIONES] = {0}; /* Arreglo estatico */
    int cantidad = 0, proximo_numero = 1, opcion, posicion, confirmar;

    configuracion_inicial(&config);
    do {
        puts("\n========== ARTEMIS SLS ==========");
        puts("1. Configurar mision");
        puts("2. Ejecutar lanzamiento");
        puts("3. Consultar historial");
        puts("4. Eliminar una mision del historial");
        puts("5. Restaurar valores originales");
        puts("0. Salir");
        opcion = leer_entero("Seleccione una opcion", 0, 5);

        switch (opcion) {
            case 1:
                configurar_mision(&config);
                break;
            case 2:
                if (cantidad == MAX_MISIONES) {
                    puts("Historial completo (20 misiones). Elimine alguna para continuar.");
                } else if (!configuracion_valida(&config)) {
                    puts("ERROR: configuracion invalida.");
                } else if (!ejecutar_mision(&config, &historial[cantidad], proximo_numero)) {
                    puts("ERROR: no se pudo reservar memoria para los eventos.");
                } else {
                    mostrar_mision(&historial[cantidad]);
                    cantidad++;
                    proximo_numero++;
                }
                break;
            case 3:
                mostrar_historial(historial, cantidad);
                break;
            case 4:
                if (cantidad == 0) {
                    puts("No hay misiones para eliminar.");
                } else {
                    posicion = leer_entero("Posicion a eliminar (0 para cancelar)", 0, cantidad);
                    if (posicion != 0) {
                        confirmar = leer_entero("Confirmar eliminacion? (1=Si, 0=No)", 0, 1);
                        if (confirmar == 1) {
                            eliminar_mision(historial, &cantidad, posicion - 1);
                            puts("Mision eliminada del historial.");
                        }
                    }
                }
                break;
            case 5:
                configuracion_inicial(&config);
                puts("Valores originales restaurados.");
                break;
            case 0:
                puts("Fin de la simulacion.");
                break;
        }
    } while (opcion != 0);

    liberar_historial(historial, cantidad);
    return 0;
}
