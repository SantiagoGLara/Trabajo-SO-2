#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESOS 100
#define NUM_PARTICIONES 10

typedef struct {
    int tamaño;
    int id_de_proceso; 
} Particion;

void imprime_memoria(Particion particiones[], int numero_de_particiones) {
    printf("\nEstado actual de la memoria:\n");
    for (int i = 0; i < numero_de_particiones; i++) {
        if (particiones[i].id_de_proceso == -1) {
            printf("Partición %d: %d KB (Espacio libre)\n", i + 1, particiones[i].tamaño);
        } else {
            printf("Partición %d: %d KB (Asignada al proceso %d)\n", i + 1, particiones[i].tamaño, particiones[i].id_de_proceso);
        }
    }
    printf("\n");
}

int main() {
    int memoria_total;
    Particion particiones[NUM_PARTICIONES];

    // Solicitar el tamaño total de la memoria
    printf("Introduzca el tamaño total de la memoria en KB: ");
    scanf("%d", &memoria_total);

    int tamaño_total_particion = memoria_total/NUM_PARTICIONES;
    printf("La memoria se dividirá en 10 particiones.\n");

    for (int i = 0; i < NUM_PARTICIONES; i++) {
        particiones[i].tamaño=tamaño_total_particion;
        particiones[i].id_de_proceso = -1; 

    }

    if (tamaño_total_particion > memoria_total) {
        printf("Error: El tamaño total de las particiones excede el tamaño de la memoria disponible.\n");
        return 1;
    }

    int opcion;
    do {
        printf("\n--- Menú de opciones ---\n");
        printf("1. Asignar un proceso\n");
        printf("2. Liberar un proceso\n");
        printf("3. Ver el estado actual de la memoria\n");
        printf("4. Salir del programa\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int id_de_proceso, tam_proceso;
                printf("Indique el ID del proceso que desea asignar: ");
                scanf("%d", &id_de_proceso);
                printf("Especifique el tamaño del proceso en KB: ");
                scanf("%d", &tam_proceso);

                int asignado = 0;
                for (int i = 0; i < NUM_PARTICIONES; i++) {
                    if (particiones[i].id_de_proceso == -1 && particiones[i].tamaño >= tam_proceso) {
                        particiones[i].id_de_proceso = id_de_proceso;
                        asignado = 1;
                        printf("El proceso %d fue asignado a la partición %d.\n", id_de_proceso, i + 1);
                        break;
                    }
                }
                if (!asignado) {
                    printf("No hay particiones disponibles para asignar el proceso %d.\n", id_de_proceso);
                }
                break;
            }
            case 2: {
                int id_de_proceso;
                printf("Indique el ID del proceso que desea liberar: ");
                scanf("%d", &id_de_proceso);

                int liberado = 0;
                for (int i = 0; i < NUM_PARTICIONES; i++) {
                    if (particiones[i].id_de_proceso == id_de_proceso) {
                        particiones[i].id_de_proceso = -1;
                        liberado = 1;
                        printf("El proceso %d fue liberado de la partición %d.\n", id_de_proceso, i + 1);
                        break;
                    }
                }
                if (!liberado) {
                    printf("No se encontró el proceso %d en ninguna partición.\n", id_de_proceso);
                }
                break;
            }
            case 3:
                imprime_memoria(particiones, NUM_PARTICIONES);
                break;
            case 4:
                printf("Saliendo del programa. Gracias por usarlo.\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}
