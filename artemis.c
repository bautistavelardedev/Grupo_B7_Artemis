#include "artemis.h"
#include "listas.h"
#include "validaciones.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

void configuracion_inicial(Configuracion *c) {
    *c = (Configuracion){A1_DEF, A2_DEF, T1_DEF, H_DEF, GRAVEDAD};
}

int configuracion_valida(const Configuracion *c) {
    double y1;
    if (!isfinite(c->a1) || !isfinite(c->a2) || !isfinite(c->t1) ||
        !isfinite(c->altura) || !isfinite(c->g)) return 0;
    if (c->a1 <= 0 || c->a2 <= 0 || c->t1 <= 0 ||
        c->g <= 0 || c->altura <= 0) return 0;
    y1 = 0.5 * c->a1 * c->t1 * c->t1;
    return isfinite(y1) && c->altura > y1;
}

int ejecutar_mision(const Configuracion *c, Mision *m, int numero) {
    double distancia;
    memset(m, 0, sizeof(*m));
    m->numero = numero;
    m->config = *c;

    m->v1 = c->a1 * c->t1;
    m->y1 = 0.5 * c->a1 * c->t1 * c->t1;
    distancia = c->altura - m->y1;
    m->v2 = sqrt(m->v1 * m->v1 + 2 * c->a2 * distancia);
    m->t2 = (m->v2 - m->v1) / c->a2;
    m->hmax = c->altura + m->v2 * m->v2 / (2 * c->g);
    m->gs = c->a1 / c->g;

    /* Los eventos se insertan en orden al final de la unica lista. */
    if (!agregar_evento(&m->eventos, "Despegue", 0, 0, 0) ||
        !agregar_evento(&m->eventos, "Separacion de SRB", c->t1, m->y1, m->v1) ||
        !agregar_evento(&m->eventos, "Apagado de motores", c->t1 + m->t2, c->altura, m->v2) ||
        !agregar_evento(&m->eventos, "Altitud maxima (modelo ideal)",
                        c->t1 + m->t2 + m->v2 / c->g, m->hmax, 0)) {
        liberar_eventos(&m->eventos);
        return 0;
    }
    m->cantidad_eventos = 4;
    return 1;
}

void mostrar_mision(const Mision *m) {
    printf("\n========== REPORTE MISION %d ==========\n", m->numero);
    mostrar_eventos(m->eventos);
    printf("\nRapidez al desacople: %.2f m/s\n", m->v1);
    printf("Altura al desacople: %.2f m\n", m->y1);
    printf("Duracion segunda fase: %.2f s\n", m->t2);
    printf("Rapidez al apagado: %.2f m/s\n", m->v2);
    printf("Altura maxima ideal: %.2f m (%.2f km)\n", m->hmax, m->hmax / 1000);
    printf("Aceleracion primera fase: %.3f g\n", m->gs);
    puts("NOTA: modelo vertical ideal con gravedad constante y sin resistencia del aire.");
}

void mostrar_historial(const Mision historial[], int cantidad) {
    int opcion, evento;
    if (cantidad == 0) {
        puts("Aun no hay misiones registradas.");
        return;
    }
    puts("\nPos | Mision | a1(m/s2) | t1(s) | v2(m/s) | hmax(km)");
    for (int i = 0; i < cantidad; i++) {
        printf("%3d | %6d | %8.2f | %5.1f | %7.2f | %9.2f\n",
            i + 1, historial[i].numero, historial[i].config.a1,
            historial[i].config.t1, historial[i].v2, historial[i].hmax / 1000);
    }
    opcion = leer_entero("Ver detalle (0 para volver)", 0, cantidad);
    if (opcion == 0) return;
    mostrar_mision(&historial[opcion - 1]);
    evento = leer_entero("Consultar evento individual (0 para volver)",
                        0, historial[opcion - 1].cantidad_eventos);
    if (evento != 0) {
        const NodoEvento *encontrado = buscar_evento(historial[opcion - 1].eventos, evento);
        if (encontrado != NULL) {
            printf("Evento encontrado: %s | t=%.2f s | h=%.2f m | v=%.2f m/s\n",
                encontrado->dato.descripcion, encontrado->dato.tiempo,
                encontrado->dato.altura, encontrado->dato.velocidad);
        }
    }
}

void eliminar_mision(Mision historial[], int *cantidad, int posicion) {
    /* Primero se libera la lista de eventos de esa mision. */
    liberar_eventos(&historial[posicion].eventos);
    /* Despues se compacta el arreglo estatico. */
    for (int i = posicion; i < *cantidad - 1; i++) {
        historial[i] = historial[i + 1];
    }
    (*cantidad)--;
    historial[*cantidad] = (Mision){0};
}

void liberar_historial(Mision historial[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        liberar_eventos(&historial[i].eventos);
    }
}

void configurar_mision(Configuracion *c) {
    Configuracion nueva = *c;
    puts("\n--- CONFIGURACION DE MISION ---");
    puts("Los limites son didacticos, para evitar entradas fisicamente incoherentes.");
    nueva.a1 = leer_real("Aceleracion primera fase (m/s2)", 1, 40);
    nueva.t1 = leer_real("Tiempo de desacople SRB (s)", 1, 300);
    nueva.a2 = leer_real("Aceleracion segunda fase (m/s2)", 1, 30);
    nueva.altura = leer_real("Altura de apagado (m)", 1000, 1000000);
    nueva.g = leer_real("Gravedad (m/s2)", 1, 20);
    if (!configuracion_valida(&nueva)) {
        puts("ERROR: la altura de apagado debe superar la alcanzada al separar los SRB.");
        puts("Se conserva la configuracion anterior.");
        return;
    }
    *c = nueva;
    puts("Configuracion guardada correctamente.");
}
