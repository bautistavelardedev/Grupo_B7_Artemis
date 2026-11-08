#ifndef ARTEMIS_H
#define ARTEMIS_H

/* Valores de referencia del problema 1 (ascenso del SLS). */
#define A1_DEF 20.0
#define A2_DEF 12.5
#define T1_DEF 120.0
#define H_DEF 160000.0
#define GRAVEDAD 9.8

typedef struct {
    double a1;
    double a2;
    double t1;
    double altura;
    double g;
} Configuracion;
/* Guarda los resultados de un lanzamiento. */
typedef struct {
    int numero;
    Configuracion config;
    double v1;
    double y1;
    double t2;
    double v2;
    double hmax;
    double gs;
} Mision;

void configuracion_inicial(Configuracion *c);
void mostrar_configuracion(const Configuracion *c);
int configuracion_valida(const Configuracion *c);
int ejecutar_mision(const Configuracion *c, Mision *m, int numero);
void mostrar_mision(const Mision *m);

#endif
