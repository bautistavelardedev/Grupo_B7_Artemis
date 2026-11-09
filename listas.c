#include "listas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int agregar_evento(NodoEvento **inicio, const char *descripcion,
                double tiempo, double altura, double velocidad) {
    NodoEvento *nuevo = malloc(sizeof(NodoEvento));
    if (nuevo == NULL) return 0;

    snprintf(nuevo->dato.descripcion, sizeof(nuevo->dato.descripcion),
            "%s", descripcion);
    nuevo->dato.tiempo = tiempo;
    nuevo->dato.altura = altura;
    nuevo->dato.velocidad = velocidad;
    nuevo->siguiente = NULL;

    if (*inicio == NULL) {
        *inicio = nuevo;
    } else {
        NodoEvento *actual = *inicio;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    return 1;
}

void mostrar_eventos(const NodoEvento *inicio) {
    int numero = 1;
    const NodoEvento *actual = inicio;
    while (actual != NULL) {
        printf("%d. %-30s t=%9.2f s | h=%12.2f m | v=%9.2f m/s\n",
            numero, actual->dato.descripcion, actual->dato.tiempo,
            actual->dato.altura, actual->dato.velocidad);
        actual = actual->siguiente;
        numero++;
    }
}

const NodoEvento *buscar_evento(const NodoEvento *inicio, int posicion) {
    int numero = 1;
    const NodoEvento *actual = inicio;
    while (actual != NULL) {
        if (numero == posicion) return actual;
        actual = actual->siguiente;
        numero++;
    }
    return NULL;
}

void liberar_eventos(NodoEvento **inicio) {
    NodoEvento *actual = *inicio;
    while (actual != NULL) {
        NodoEvento *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *inicio = NULL;
}
