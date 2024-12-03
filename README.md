# Trabajo-SO
### Santiago Gonzalez Lara <br>Sistemas Operativos<br>Profesor: Eduardo Alcaraz
### trabajo sistemas operativos <br>2 de diciembre de 2024


## Administración de Memoria<br>
### 3.1 Política y filosofía
1. **¿Cuál es la diferencia entre fragmentación interna y externa? Explica cómo cada una afecta el rendimiento de la memoria.**<br>
la fragmentacion interna es cuando un proceso es mas pequeño que su partición asignada, la memoria sobrante de la particion es inutilizable y a eso se le llama fragmentacion interna, en cambio la externa es cuando hay espacios de memoria sobrantes donde ya no cabe un proceso.<br> afecta porque tanto dentro de las particiones como fuera desperdicia pequeños espacios que acumulados podrían ser utilizados para muchos otros procesos.
2. **Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?**<br>
las politicas de reemplazo de pagina se utilizan cuando un programa intenta acceder a una pagina de la memoria aun no cargada en la memoria principal(RAM), lo que produce que el proceso no pueda continuar hasta que tenga acceso a dicha pagina, a esto se le conooce como fallo de pagina, y lo que hay que hacer es reemplazar una pagina que ya está cargada en ram por la que necesitamos que esté cargada, a la forma de seleccionar la pagina a reemplazar la conocemos como 'politica de reemplazo' o 'politica de sustitucion'
    - **optimo:** selecciona a reemplazar la pagina que tardará mas en volver a ser utilizada. para ciertas cantidades fijas de marcos es la que menos produce fallos, y esto precisamente es lo que lo hace dificil de implementar, pues predecir que paginas se referenciarán en un futuro no es posible.
    - **FIFO:** saca de la memoria a la pagina que primero haya llegado, la más antigua en la memoria. Super simple de implementar, simplemente se utiliza un puntero para la pagina mas antigua y otro para la añadida mas recientemente, cuando hay un fallo simplemente se elimina la mas vieja y se añade la nueva pagina al final de la lista. Si bien es simple. puede presentiar fenomenos que mientras mas marcos utilicemos, mas fallos de pagina se presenten.
    - **LRU(Less Recently Used):** se basa en el principio de la cercania de referencia, tambien conocido como principio de localidad, que establece que las referencias a codigo y datos tienden a agruparse y no cambiar en periodos cortos de tiempo. Bajo este principio es organizar 'jerarquicamente' la prioridad con la que se hacen referencia a ciertos espacios de memoria, o por lo menos una estimación. El algoritmo LRU se basa en ello, para deducir que la pagina que tiene mas tiempo sin ser referenciada es la que tiene menor probabilidad de ser referenciada, esto hace que se aproxime mucho al algoritmo optimo. Funciona como una pila, lo que hace que no presente la anomalia de Belady (a más marcos, mas fallas). Tiene mejores resultados que el algoritmo fifo, pero sufre de varios defectos de los que sufre el algoritmo optimo, ademas que implementar una pila es dificil, por lo que se sugiere usar una pila doblemente enlazada, lo que lo hace mas eficaz pero su utilizacion ocuparia demasiados recursos, pues puede modificar hasta 6 punteros por un reemplazo de pagina.
    - **RELOJ:** se basa en en los buenos resultados que salen de utilizar pilas, y los bajos costos del algoritmo FIFO, utiliza hardware para facilitar su implementación y ser mas eficiente. Consiste en añadirle a cada marco un bit de referencia, que se modificará en base a la pagina.<br>
    Cuando la pagina se carga a memoria, el bit de referencia se cambia a 1, asi como cuando se referencie a la pagina, nuevamente se le marcará con 1(o se mantendrá). Se mantiene haciendo un recorrido circular cuando hay paginas sin haber sido referenciadas o cuando se necesita hacer un reempĺazo, hace un recorrido 'circular' por toda la lista, durante su ciclo, recorre los los marcos en busca de una pagina que no haya sido referenciada, y desactiva los bits de referencia a su paso. En caso de que en un ciclo todos los bits de referencia estén activos, dará un ciclo completo para desactivarlos todos y así, ya devuelta en el inicio de la lista circular, haga el reemplazo sobre el primer elemento integrado a la lista, tal como FIFO.<BR>
    Aumentar el tamaño del bit de referencia de cada marco, aumenta su complejidad y en ciertos casos puede dar mejores resultados, pues nos da mas informacion acerca de las paginas<br>
        - **RELOJ MEJORADO:** consiste en utilizar 2 bits de referencia en lugar de 1, el bit menos significativo representa el bit de modificacion, mientras que el mas significativo representa el bit de referencia. esto nos lleva a que una pagina puede tener 4 estados:<br>

            |Bit modificación|Bit referencia|significado|
            |----------------|--------------|-----------|
            |0               |0             |sin modificacion ni referencia|
            |0               |1             |no ha sido referenciado, pero si modificado|
            |1               |0             |ha sido referenciado recientemente pero no modificado
            |1               |1             |se ha referenciado y modificado recientemente|
            
            el algoritmo lo que hace es en base a esta informacion extra, definir los que menos prioridad tengan para permanecer en memoria.
             1. primero, busca las paginas de tipo (0,0), de encontrar una la sustituye
             2. recorre la lista buscando la primer pagina de tipo (0,1), durante esta busqueda desactiva el bit de referencia que lo tengan en uno
             3. regresa al paso 1, pues en este paso ya todos los bits tanto de referencia como de modificación habran regresado al estado (0,0)

### 3.2 Memoria real
1. **Escribe un programa en C o Python que simule la administración de memoria mediante particiones fijas.** <br>
```C
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

```
nota: al ejecutarse, aunque el proceso no supera el tamaño de la particion, pero si el limite de particiones a la vez, con lo que no se asigna

2. **Diseña un algoritmo para calcular qué procesos pueden ser asignados a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida"**.<br>


### 3.3 Organización de memoria virtual
1. **Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?**<br>
Paginación: consiste en dividir la memoria fisica en  del mismo tamaño llamados marcos, y la memoria logica la dividimos en bloques del mismo del marco, cuando se necesita cargar un programa en memoria, se cargan las paginas en los marcos, sin que sea necesario que estén contiguos. Esto elimina la fragmentación externa, aunque deja algo de fragmentacion interna en la ultima pagina del codigo<br>
segmentacion:  tampoco exigue que esté de forma contigua, el programa se carga en espacios de memoria de tamaño irregular, segun el tamaño de los espacios disponibles y el tamaño del programa. para gestionar este tipo de administracion de memoria, se necesita una tabla de segmentos, para guardar las direcciones, ademas se necesita llevar el control de las zonas libres y ocupadas.
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

