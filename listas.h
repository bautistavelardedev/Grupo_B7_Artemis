#ifndef LISTAS_H
#define LISTAS_H
#include "artemis.h"

/* Recibe doble puntero porque puede cambiar la cabeza de la lista. */
int agregar_evento(NodoEvento **inicio, const char *descripcion,
                double tiempo, double altura, double velocidad);
void mostrar_eventos(const NodoEvento *inicio);
const NodoEvento *buscar_evento(const NodoEvento *inicio, int posicion);
void liberar_eventos(NodoEvento **inicio);

#endif