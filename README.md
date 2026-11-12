# Artemis- Grupo B7

## Integrantes del grupo
- Aguilar Cáceres, David Elías - Legajo: 30126
- Bentolila, David Benjamín - Legajo: 30202
- Carballo, Santino - Legajo: 28954
- Luque, Agustín Ignacio - Legajo: 30692
- Velarde, Bautista Facundo - Legajo: 30922

## Comisión
ISI - Comisión 1.2 - 2026

# Enlace al Repositorio de GitHub:
https://github.com/bautistavelardedev/Grupo_B7_Artemis

# Enlace al Video Demo:


## Escenario Asignado:
El proyecto consiste en un simulador por consola desarrollado en lenguaje C, basado en la primera etapa de la misión Artemis de la NASA, específicamente en el despegue y ascenso del cohete Space Launch System (SLS), encargado de impulsar la nave Orion.
La simulación representa el movimiento vertical del cohete desde la plataforma de lanzamiento hasta el apagado de sus motores, considerando dos fases de aceleración constante y una etapa final de ascenso libre.
Etapas de la simulación:
- Despegue: el cohete parte del reposo, desde una altura inicial de 0 metros, y comienza a ascender con una aceleración constante de 20 m/s².
- Separación de los propulsores SRB: transcurridos 120 segundos, los propulsores auxiliares se desacoplan. El programa calcula la velocidad y la altura alcanzadas hasta ese momento.
- Segunda fase de ascenso: el cohete continúa su trayectoria con una aceleración de 12,5 m/s² hasta alcanzar los 160.000 metros de altura, donde se produce el apagado de los motores.
- Ascenso libre: luego del apagado, la nave continúa ascendiendo por inercia mientras la gravedad reduce progresivamente su velocidad hasta alcanzar su altura máxima ideal.
El modelo físico utiliza ecuaciones del Movimiento Rectilíneo Uniformemente Variado (MRUV). Para simplificar los cálculos, se considera un movimiento vertical ideal, sin resistencia del aire y con aceleración gravitatoria constante durante el ascenso libre.

## Funcionamiento:
El programa funciona mediante un menú principal interactivo que permite configurar, ejecutar y administrar simulaciones de lanzamiento del cohete SLS.
Al iniciarse, se cargan automáticamente los parámetros originales del escenario Artemis. A partir de ellos, el usuario dispone de las siguientes opciones:
1. Configurar misión	Modificar los parámetros físicos del lanzamiento.
2. Ejecutar lanzamiento	Realizar los cálculos y generar un reporte de la misión.
3. Consultar historial	Visualizar las misiones realizadas, sus resultados y eventos individuales.
4. Eliminar una misión	Seleccionar y eliminar una misión del historial, previa confirmación.
5. Restaurar valores originales	Recuperar los parámetros predeterminados del escenario.
0. Salir	Finalizar el programa.

## Requisitos:
Compilador de C compatible con C11, como GCC.

Git (opcional, para clonar el repositorio).

Sistema operativo: Windows, Linux o macOS.

Editor de código (recomendado: Visual Studio Code).

Make (opcional, para compilar automáticamente mediante el Makefile incluido).

## Instrucciones de compilación y ejecución
Opción 1: Clonar desde GitHub (recomendado)
1.	Abrir una terminal y clonar el repositorio:
git clone URL-DEL-REPOSITORIO
2.	Ingresar a la carpeta del proyecto:
cd NOMBRE-DEL-REPOSITORIO
3.	Compilar el programa utilizando el Makefile:
make
4.	Ejecutar el simulador:
En Linux o macOS:
./artemis
En Windows, si el ejecutable generado se llama artemis.exe:
.\artemis.exe

Opción 2: Compilación manual con GCC

Si no se dispone de Make, se puede compilar el programa directamente desde la terminal.
En Linux o macOS:
gcc -std=c11 main.c artemis.c listas.c validaciones.c -o artemis -lm ./artemis

En Windows:
gcc -std=c11 main.c artemis.c listas.c validaciones.c -o artemis.exe -lm
 
Para ejecutarlo:
.\artemis.exe

Uso del programa:
Una vez ejecutado, el simulador muestra un menú principal con las opciones disponibles.
Para realizar una simulación, el usuario puede utilizar los parámetros originales o modificarlos desde la opción de configuración. Luego debe seleccionar la opción de ejecutar lanzamiento, que realizará los cálculos físicos y mostrará un reporte con los resultados.
Cada lanzamiento se almacena en el historial, desde donde se pueden consultar los eventos de la misión o eliminar registros. El programa permite realizar nuevas simulaciones hasta que el usuario seleccione la opción de salir.
      python main.py

## Uso de IA:
Se utilizó ChatGPT como herramienta de apoyo durante el desarrollo. Se consultó principalmente para separar tareas en archivos .c y .h, diseñar validaciones de entrada con funciones y comprender el manejo de listas simplemente enlazadas con punteros.
Las consultas fueron concretas: cómo dividir el programa en archivos, cómo pedir y validar números sin que el programa se rompa, cómo recorrer y liberar una lista enlazada, y cómo corregir errores de compilación. El grupo no tenía experiencia previa en C, por lo que la IA fue un apoyo importante para avanzar; aun así, cada integrante revisó y comprendió lo incorporado.
Sin embargo, las respuestas no se incorporaron directamente. Se detectaron propuestas que no se usaban, nombres inconsistentes, variables innecesarias y soluciones que solo cubrían los casos más simples, sin contemplar situaciones límite. Por eso, cada sugerencia fue revisada, adaptada y probada por el grupo con casos válidos e inválidos. Las decisiones finales de diseño e implementación fueron tomadas por los integrantes.
