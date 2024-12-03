#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _nodo {
    int valor;
    int prioridad;
    struct _nodo *siguiente;
} nodo;

int numero_aleatorio() {
    return (rand() % 4) + 1;
}

nodo* crear_nodo(int valor, int prioridad) {
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevo->valor = valor;
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertar_final(nodo** cabeza, int valor, int prioridad) {
    nodo* nuevoNodo = crear_nodo(valor, prioridad);
    
    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        nodo* temp = *cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

void imprimir_lista(nodo* cabeza) {
    nodo* temp = cabeza;
    while (temp != NULL) {
        printf("Valor %d (Prioridad %d) -> ", temp->valor, temp->prioridad);
        temp = temp->siguiente;
    }
    printf("NULL\n");
}

void atender_prioridad(nodo** cabeza) {
    if (*cabeza == NULL) {
        printf("No hay elementos para atender.\n");
        return;
    }

    nodo* temp = *cabeza;
    nodo* maxNodo = temp;
    nodo* maxNodoPrevio = NULL;
    nodo* previo = NULL;

    while (temp != NULL) {
        if (temp->prioridad > maxNodo->prioridad) {
            maxNodo = temp;
            maxNodoPrevio = previo;
        }
        previo = temp;
        temp = temp->siguiente;
    }

    printf("Atendiendo valor %d con prioridad %d\n", maxNodo->valor, maxNodo->prioridad);

    if (maxNodoPrevio == NULL) {
        *cabeza = maxNodo->siguiente;
    } else {
        maxNodoPrevio->siguiente = maxNodo->siguiente;
    }

    free(maxNodo);
}

int main() {
    srand(time(NULL));
    nodo* cabeza = NULL;
    int op = 0, valor, prioridad;
    int contador = 1;

    do {
        printf("\n1. Insertar elemento con prioridad\n");
        printf("2. Atender elemento\n");
        printf("3. Mostrar lista de elementos\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                valor = contador++;
                prioridad = numero_aleatorio();
                insertar_final(&cabeza, valor, prioridad);
                break;
            case 2:
                atender_prioridad(&cabeza);
                break;
            case 3:
                imprimir_lista(cabeza);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (op != 4);

    while (cabeza != NULL) {
        atender_prioridad(&cabeza);
    }

    return 0;
}
