#ifndef ARTEMIS_H
#define ARTEMIS_H

#define MAX_MISIONES 20
#define GRAVEDAD 9.8
#define A1_DEF 20.0
#define A2_DEF 12.5
#define T1_DEF 120.0
#define H_DEF 160000.0

typedef struct {
    double a1, a2, t1, altura, g;
} Configuracion;

typedef struct {
    char descripcion[64];
    double tiempo, altura, velocidad;
} Evento;

/* Una unica lista simplemente enlazada para los eventos del vuelo. */
typedef struct NodoEvento {
    Evento dato;
    struct NodoEvento *siguiente;
} NodoEvento;

typedef struct {
    int numero;
    Configuracion config;
    NodoEvento *eventos;
    int cantidad_eventos;
    double v1, y1, t2, v2, hmax, gs;
} Mision;

void configuracion_inicial(Configuracion *c);
int configuracion_valida(const Configuracion *c);
void configurar_mision(Configuracion *c);
int ejecutar_mision(const Configuracion *c, Mision *m, int numero);
void mostrar_mision(const Mision *m);
void mostrar_historial(const Mision historial[], int cantidad);
void eliminar_mision(Mision historial[], int *cantidad, int posicion);
void liberar_historial(Mision historial[], int cantidad);

#endif
