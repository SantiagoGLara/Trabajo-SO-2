#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISPOSITIVOS 10

typedef struct {
    int id;
    char nombre[50];
    char tipo[50];
    int estado;
} Dispositivo;

Dispositivo dispositivos[MAX_DISPOSITIVOS];
int num_dispositivos = 0;

void agregar_dispositivo() {
    if (num_dispositivos < MAX_DISPOSITIVOS) {
        Dispositivo nuevo_dispositivo;
        nuevo_dispositivo.id = num_dispositivos + 1;
        printf("Ingrese el nombre del dispositivo: ");
        scanf("%s", nuevo_dispositivo.nombre);
        printf("Ingrese el tipo de dispositivo: ");
        scanf("%s", nuevo_dispositivo.tipo);
        nuevo_dispositivo.estado = 0;
        dispositivos[num_dispositivos] = nuevo_dispositivo;
        num_dispositivos++;
        printf("Dispositivo agregado exitosamente.\n");
    } else {
        printf("No se pueden agregar más dispositivos. Límite alcanzado.\n");
    }
}

void mostrar_dispositivos() {
    if (num_dispositivos == 0) {
        printf("No hay dispositivos registrados.\n");
        return;
    }
    printf("Lista de dispositivos:\n");
    printf("ID\tNombre\t\tTipo\t\tEstado\n");
    for (int i = 0; i < num_dispositivos; i++) {
        printf("%d\t%s\t\t%s\t\t%s\n", dispositivos[i].id, dispositivos[i].nombre, dispositivos[i].tipo, (dispositivos[i].estado == 1) ? "Activo" : "Inactivo");
    }
}

void cambiar_estado_dispositivo() {
    int id;
    printf("Ingrese el ID del dispositivo a cambiar el estado: ");
    scanf("%d", &id);
    if (id > 0 && id <= num_dispositivos) {
        dispositivos[id - 1].estado = !dispositivos[id - 1].estado;
        printf("Estado del dispositivo cambiado.\n");
    } else {
        printf("ID de dispositivo inválido.\n");
    }
}

int main() {
    int opcion;
    do {
        printf("\nManejador de Dispositivos\n");
        printf("1. Agregar dispositivo\n");
        printf("2. Mostrar dispositivos\n");
        printf("3. Cambiar estado de dispositivo\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregar_dispositivo();
                break;
            case 2:
                mostrar_dispositivos();
                break;
            case 3:
                cambiar_estado_dispositivo();
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}