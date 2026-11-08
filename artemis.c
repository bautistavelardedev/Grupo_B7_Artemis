#include <stdio.h>
#include <math.h>
#include "artemis.h"

void configuracion_inicial(Configuracion *c) {
    *c = (Configuracion){A1_DEF, A2_DEF, T1_DEF, H_DEF, GRAVEDAD};
}

void mostrar_configuracion(const Configuracion *c) {
    printf("\n--- CONFIGURACION INICIAL ---\n");
    printf("Aceleracion fase 1: %.2f m/s2\n", c->a1);
    printf("Aceleracion fase 2: %.2f m/s2\n", c->a2);
    printf("Tiempo de separacion SRB: %.2f s\n", c->t1);
    printf("Altura de apagado: %.2f m\n", c->altura);
    printf("Gravedad: %.2f m/s2\n", c->g);
}

int configuracion_valida(const Configuracion *c) {
    double altura_desacople;

    if (c == NULL) return 0;
    if (!isfinite(c->a1) || !isfinite(c->a2) || !isfinite(c->t1) ||
        !isfinite(c->altura) || !isfinite(c->g)) return 0;
    if (c->a1 <= 0 || c->a2 <= 0 || c->t1 <= 0 ||
        c->altura <= 0 || c->g <= 0) return 0;

    altura_desacople = 0.5 * c->a1 * c->t1 * c->t1;
    return isfinite(altura_desacople) && c->altura > altura_desacople;
}

int ejecutar_mision(const Configuracion *c, Mision *m, int numero) {
    double distancia_segunda_fase;

    if (m == NULL || !configuracion_valida(c)) return 0;

    /* fase 1: MRUV desde el reposo hasta separar los SRB. */
    m->v1 = c->a1 * c->t1;
    m->y1 = 0.5 * c->a1 * c->t1 * c->t1;

    /* fase 2 MRUV hasta alcanzar la altura de apagado. */
    distancia_segunda_fase = c->altura - m->y1;
    m->v2 = sqrt(m->v1 * m->v1 + 2.0 * c->a2 * distancia_segunda_fase);
    m->t2 = (m->v2 - m->v1) / c->a2;

    /* ascenso con gravedad constante. */
    m->hmax = c->altura + m->v2 * m->v2 / (2.0 * c->g);
    m->gs = c->a1 / c->g;

    if (!isfinite(m->v2) || !isfinite(m->t2) ||
        !isfinite(m->hmax) || !isfinite(m->gs)) return 0;

    m->numero = numero;
    m->config = *c;
    return 1;
}

void mostrar_mision(const Mision *m) {
    printf("\n========== REPORTE MISION %d ==========\n", m->numero);
    printf("Rapidez al desacople SRB: %.2f m/s\n", m->v1);
    printf("Altura al desacople SRB: %.2f m\n", m->y1);
    printf("Duracion de la segunda fase: %.2f s\n", m->t2);
    printf("Rapidez al apagado de motores: %.2f m/s\n", m->v2);
    printf("Altura maxima ideal: %.2f m (%.2f km)\n", m->hmax, m->hmax / 1000.0);
    printf("Aceleracion primera fase: %.3f g\n", m->gs);
    puts("NOTA: modelo vertical ideal con gravedad constante y sin resistencia del aire.");
}
