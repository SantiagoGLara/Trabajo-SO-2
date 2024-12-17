#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

bool estadoImpresora = false;
char datosImpresora[256];

void abrirImpresora() {
    if (!estadoImpresora) {
        estadoImpresora = true;
        printf("Abriendo impresora...\n");
        sleep(1);
    } else {
        printf("La impresora ya está abierta.\n");
    }
}

void leerBufferImpresora() {
    if (estadoImpresora) {
        printf("Leyendo buffer...\n");
        sleep(1);
        printf("Contenido del buffer: %s\n", datosImpresora);
    } else {
        printf("La impresora está cerrada.\n");
    }
}

void escribirBufferImpresora() {
    if (estadoImpresora) {
        printf("Introduce el texto a imprimir: \n");
        fgets(datosImpresora, sizeof(datosImpresora), stdin);
        datosImpresora[strcspn(datosImpresora, "\n")] = 0; // Eliminar el salto de línea
        printf("Datos cargados.\n");
    } else {
        printf("La impresora está cerrada.\n");
    }
}

void cerrarImpresora() {
    if (estadoImpresora) {
        estadoImpresora = false;
        printf("Cerrando impresora...\n");
        sleep(2);
        printf("Espere...\n");
        sleep(1);
        printf("Impresora cerrada.\n");
    } else {
        printf("La impresora ya está cerrada.\n");
    }
}

int main() {
    int opcion;

    while (true) {
        printf("\n--- Menú de la Impresora ---\n");
        printf("1. Abrir\n");
        printf("2. Leer Buffer\n");
        printf("3. Escribir Buffer\n");
        printf("4. Cerrar\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada inválida. Ingrese un número.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue; // Volver al inicio del bucle
        }
        while (getchar() != '\n'); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                abrirImpresora();
                break;
            case 2:
                leerBufferImpresora();
                break;
            case 3:
                escribirBufferImpresora();
                break;
            case 4:
                cerrarImpresora();
                break;
            case 0:
                printf("Saliendo... Adiós.\n");
                return 0;
            default:
                printf("Opción no válida. Por favor, elija una opción válida.\n");
        }
    }

    return 0;
}