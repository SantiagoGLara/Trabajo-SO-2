#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_PAGINA 1024
#define NUM_PAGINAS 16
#define MEMORIA_VIRTUAL 16384

typedef struct {
    int numero_pagina;
    int numero_marco;
    int valido;
} EntradaTablaPaginas;

int memoria_fisica[NUM_PAGINAS][TAM_PAGINA];

void inicializar_tabla_paginas(EntradaTablaPaginas *tabla_paginas) {
    for (int i = 0; i < NUM_PAGINAS; i++) {
        tabla_paginas[i].numero_pagina = i;
        tabla_paginas[i].numero_marco = -1;
        tabla_paginas[i].valido = 0;
    }
}

void cargar_pagina(EntradaTablaPaginas *tabla_paginas, int numero_pagina) {
    if (tabla_paginas[numero_pagina].valido == 0) {
        tabla_paginas[numero_pagina].numero_marco = numero_pagina;
        tabla_paginas[numero_pagina].valido = 1;
        printf("Página %d cargada en el marco %d.\n", numero_pagina, tabla_paginas[numero_pagina].numero_marco);
    }
}

void acceder_memoria(EntradaTablaPaginas *tabla_paginas, int direccion_virtual) {
    int numero_pagina = direccion_virtual / TAM_PAGINA;
    int desplazamiento = direccion_virtual % TAM_PAGINA;

    if (numero_pagina >= NUM_PAGINAS) {
        printf("Error: Dirección virtual fuera de rango.\n");
        return;
    }

    if (tabla_paginas[numero_pagina].valido == 0) {
        printf("Fallo de página en la página %d. Cargando la página...\n", numero_pagina);
        cargar_pagina(tabla_paginas, numero_pagina);
    }

    int numero_marco = tabla_paginas[numero_pagina].numero_marco;
    int direccion_fisica = (numero_marco * TAM_PAGINA) + desplazamiento;

    printf("Dirección virtual %d -> Dirección física %d (Página %d, Marco %d, Desplazamiento %d)\n",
           direccion_virtual, direccion_fisica, numero_pagina, numero_marco, desplazamiento);
}

int main() {
    EntradaTablaPaginas tabla_paginas[NUM_PAGINAS];
    int direccion_virtual;

    inicializar_tabla_paginas(tabla_paginas);
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        direccion_virtual = rand() % MEMORIA_VIRTUAL;
        printf("\nAcceso a la dirección virtual: %d\n", direccion_virtual);
        acceder_memoria(tabla_paginas, direccion_virtual);
    }
    return 0;
}
