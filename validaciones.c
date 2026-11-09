#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

static int obtener_linea(char *buffer,size_t capacidad){
    size_t n; int ch;
    if(!fgets(buffer,(int)capacidad,stdin)) return 0;
    n=strlen(buffer);
    if(n && buffer[n-1]=='\n') buffer[n-1]='\0';
    else {while((ch=getchar())!='\n' && ch!=EOF){} puts("Entrada demasiado larga. Intente otra vez."); return -1;}
    return 1;
}
static int parsear_real(const char *texto,double *resultado){
    char *fin; double valor;
    while(isspace((unsigned char)*texto)) texto++;
    if(!*texto) return 0;
    errno=0; valor=strtod(texto,&fin);
    if(texto==fin || errno==ERANGE || !isfinite(valor)) return 0;
    while(isspace((unsigned char)*fin)) fin++;
    if(*fin) return 0;
    *resultado=valor; return 1;
}
double leer_real(const char *mensaje,double minimo,double maximo){
    char linea[128]; double valor; int estado;
    for(;;){
        printf("%s [%.2f a %.2f]: ",mensaje,minimo,maximo);
        estado=obtener_linea(linea,sizeof(linea));
        if(estado==0){puts("\nFin de entrada. Saliendo."); exit(0);}
        if(estado<0) continue;
        if(!parsear_real(linea,&valor)){puts("ERROR: ingrese un numero valido (use punto decimal).");continue;}
        if(valor<minimo || valor>maximo){puts("ERROR: valor fuera del rango permitido.");continue;}
        return valor;
    }
}
int leer_entero(const char *mensaje,int minimo,int maximo){
    char linea[128],*fin; long valor; int estado;
    for(;;){
        printf("%s [%d a %d]: ",mensaje,minimo,maximo);
        estado=obtener_linea(linea,sizeof(linea));
        if(estado==0){puts("\nFin de entrada. Saliendo.");exit(0);}
        if(estado<0) continue;
        char *inicio=linea;
        while(isspace((unsigned char)*inicio)) inicio++;
        if(!*inicio){puts("ERROR: debe ingresar un entero.");continue;}
        errno=0;valor=strtol(inicio,&fin,10);
        while(isspace((unsigned char)*fin)) fin++;
        if(errno==ERANGE || fin==inicio || *fin || valor<minimo || valor>maximo){puts("ERROR: entero invalido o fuera de rango.");continue;}
        return (int)valor;
    }
}
void esperar_enter(void){char linea[128];puts("Presione ENTER para continuar..."); if(!fgets(linea,sizeof(linea),stdin)) clearerr(stdin);}
