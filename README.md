# Trabajo-SO
### Santiago Gonzalez Lara <br>Sistemas Operativos<br>Profesor: Eduardo Alcaraz
### trabajo sistemas operativos <br>2 de diciembre de 2024


## Administración de Memoria<br>
### 3.1 Política y filosofía
1. **¿Cuál es la diferencia entre fragmentación interna y externa? Explica cómo cada una afecta el rendimiento de la memoria.**<br>
la fragmentacion interna es cuando un proceso es mas pequeño que su partición asignada, la memoria sobrante de la particion es inutilizable y a eso se le llama fragmentacion interna, en cambio la externa es cuando hay espacios de memoria sobrantes donde ya no cabe un proceso.<br> afecta porque tanto dentro de las particiones como fuera desperdicia pequeños espacios que acumulados podrían ser utilizados para muchos otros procesos.
2. **Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?**<br>
las politicas de reemplazo de pagina se utilizan cuando un programa intenta acceder a una pagina de la memoria aun no cargada en la memoria principal(RAM), lo que produce que el proceso no pueda continuar hasta que tenga acceso a dicha pagina, a esto se le conooce como fallo de pagina, y lo que hay que hacer es reemplazar una pagina que ya está cargada en ram por la que necesitamos que esté cargada, a la forma de seleccionar la pagina a reemplazar la conocemos como 'politica de reemplazo' o 'politica de sustitucion'
    - optimo:
    - FIFO
    - LRU
    - RELOJ 
        -RELOJ 1
        -RELOJ 2
### 3.2 Memoria real
1. **Escribe un programa en C o Python que simule la administración de memoria mediante particiones fijas.** <br>

2. **Diseña un algoritmo para calcular qué procesos pueden ser asignados a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida"**.<br>

### 3.3 Organización de memoria virtual
1. **Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?**<br>
2. **Escribe un programa que simule una tabla de páginas para procesos con acceso aleatorio a memoria virtual.**<br>
### 3.4 Administración de memoria virtual
1. **Escribe un código que implemente el algoritmo de reemplazo de página "Least Recently Used" (LRU).<br>**
2. **Diseña un diagrama que represente el proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual.**<br>
### Integración
1. **Analiza un sistema operativo moderno (por ejemplo, Linux o Windows) e identifica cómo administra la memoria virtual.**<br>
2. **Realiza una simulación en cualquier lenguaje de programación que emule el swapping de procesos en memoria virtual.**<br>
## Administración de Entrada/Salida
### 4.1 Dispositivos y manejadores de dispositivos
1. **Explica la diferencia entre dispositivos de bloque y dispositivos de carácter. Da un ejemplo de cada uno.**<br>
2. **Diseña un programa que implemente un manejador de dispositivos sencillo para un dispositivo virtual de entrada.**<br>
### 4.2 Mecanismos y funciones de los manejadores de dispositivos
1. **Investiga qué es la interrupción por E/S y cómo la administra el sis- tema operativo. Escribe un ejemplo en pseudocódigo para simular este proceso.**<br>
2. **Escribe un programa que utilice el manejo de interrupciones en un sistema básico de simulación.**<br>

### 4.3 Estructuras de datos para manejo de dispositivos
1. **Investiga y explica qué es una cola de E/S. Diseña una simulación de una cola con prioridad.**<br>
#FALTA LA INVESTIGACION
```C
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
```

2. **Escribe un programa que simule las operaciones de un manejador de dispositivos utilizando una tabla de estructuras.**<br>
### 4.4 Operaciones de Entrada/Salida
1. **Diseña un flujo que describa el proceso de lectura de un archivo desde un disco magnético. Acompáñalo con un programa básico que simule el proceso.**<br>
2. **Implementa un programa en Python, C o java que realice operaciones de entrada/salida asíncronas usando archivos.**<br>
### Integración
1. **Escribe un programa que implemente el algoritmo de planificación de discos "Elevator (SCAN)".**<br>
2. **Diseña un sistema que maneje múltiples dispositivos simulados (disco duro, impresora, teclado) y muestra cómo se realiza la comunicación entre ellos.**<br>
### Avanzados
1. **Explica cómo los sistemas operativos modernos optimizan las operaciones de entrada/salida con el uso de memoria caché.**<br>

