#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


typedef struct PaginaTabla{
    int indicePagina;
    int marcoAsignado;
    int cargada;
    int ultimoUso;
} PaginaTabla;

typedef struct Pagina{
    int numeroPagina;
    int tamanio;
} Pagina;

typedef struct Proceso{
    int PID;
    int cantidadPaginas;
    int tamanio;
    PaginaTabla *tablaPaginas;
    struct Proceso *siguiente;
} Proceso;

typedef struct Marco{
    int numeroMarco;
    int paginaAsignada;
    int idProceso;
} Marco;


#define TAM_MEMORIA_FISICA 8
#define TAM_PAGINA 4

int totalMarcos = TAM_MEMORIA_FISICA / TAM_PAGINA;
int contadorProceso = 1;
int contadorUso = 0;
Marco memoriaFisica[TAM_MEMORIA_FISICA / TAM_PAGINA];

Proceso *cabeza = NULL;

void aplicarLRU();

void imprimirTablasProcesos() {
    if (cabeza == NULL) {
        printf("No hay procesos registrados.\n");
        return;
    }

    Proceso *procesoActual = cabeza;
    printf("----------------------------------------\n");
    while (procesoActual != NULL) {
        printf("| PID: %d | Tamaño Proceso: %d KB | Páginas: %d |\n\n", procesoActual->PID, procesoActual->tamanio, procesoActual->cantidadPaginas);
        for (int i = 0; i < procesoActual->cantidadPaginas; i++) {
            printf("| Página %d | Marco asignado %d | Cargada %d |\n", procesoActual->tablaPaginas[i].indicePagina, procesoActual->tablaPaginas[i].marcoAsignado, procesoActual->tablaPaginas[i].cargada);
        }
        printf("----------------------------------------\n");
        procesoActual = procesoActual->siguiente;
    }
}

void imprimirMemoriaFisica() {
    printf("-- Memoria Física --\n");
    for (int i = 0; i < totalMarcos; i++) {
        if (memoriaFisica[i].paginaAsignada != -1) {
            int pidProceso = memoriaFisica[i].idProceso;
            Proceso *aux = cabeza;
            while (aux != NULL && aux->PID != pidProceso) {
                aux = aux->siguiente;
            }

            if (aux != NULL) {
                for (int j = 0; j < aux->cantidadPaginas; j++) {
                    if (aux->tablaPaginas[j].marcoAsignado == i) {
                        printf("| Marco: %d | Página: %d | (Proceso ID: %d) | Último Uso: %d \n",
                               i, aux->tablaPaginas[j].indicePagina, aux->PID, aux->tablaPaginas[j].ultimoUso);
                        break;
                    }
                }
            }
        } else {
            printf("Marco %d: Libre\n", i);
        }
    }
}

int calcularPaginas(int *tam) {
    return (int)ceil((float)*tam / TAM_PAGINA);
}

void crearProceso() {
    int tam = 0;
    printf("Ingresa el tamaño del proceso (KB): ");
    scanf("%d", &tam);

    Proceso *nuevoProceso = (Proceso*)malloc(sizeof(Proceso));
    nuevoProceso->PID = contadorProceso;
    nuevoProceso->tamanio = tam;
    nuevoProceso->cantidadPaginas = calcularPaginas(&tam);
    nuevoProceso->tablaPaginas = (PaginaTabla*)malloc(sizeof(PaginaTabla) * nuevoProceso->cantidadPaginas);

    for (int i = 0; i < nuevoProceso->cantidadPaginas; i++) {
        nuevoProceso->tablaPaginas[i].indicePagina = i;
        nuevoProceso->tablaPaginas[i].cargada = 0;
        nuevoProceso->tablaPaginas[i].marcoAsignado = -1;
    }

    nuevoProceso->siguiente = cabeza;
    cabeza = nuevoProceso;
    contadorProceso++;
}

void asignarPaginas() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    printf("Selecciona el proceso para asignar páginas:\n");
    Proceso *temp = cabeza;
    while (temp != NULL) {
        printf("| ID: %d | Tamaño: %d KB | Páginas: %d |\n", temp->PID, temp->tamanio, temp->cantidadPaginas);
        temp = temp->siguiente;
    }

    printf("Ingresa el ID del proceso: ");
    int idProceso;
    scanf("%d", &idProceso);

    Proceso *temp2 = cabeza;
    while (temp2 != NULL) {
        if (temp2->PID == idProceso) {
            int todasAsignadas = 1;
            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                if (temp2->tablaPaginas[i].marcoAsignado == -1) {
                    todasAsignadas = 0;
                    break;
                }
            }

            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                printf("| Página %d | Marco asignado: %d | Cargada: %d |\n", temp2->tablaPaginas[i].indicePagina, temp2->tablaPaginas[i].marcoAsignado, temp2->tablaPaginas[i].cargada);
            }

            int opc = 0;
            do {
                int pagSeleccionada;
                printf("Selecciona el número de página a cargar en memoria: ");
                scanf("%d", &pagSeleccionada);

                if (pagSeleccionada < 0 || pagSeleccionada >= temp2->cantidadPaginas) {
                    printf("Página inválida.\n");
                    return;
                }

                if (temp2->tablaPaginas[pagSeleccionada].marcoAsignado != -1) {
                    printf("Página ya asignada. Actualizando último uso.\n");
                    temp2->tablaPaginas[pagSeleccionada].ultimoUso = contadorUso;
                    contadorUso++;
                    return;
                }

                int marcosLibres[totalMarcos];
                int numLibres = 0;
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        marcosLibres[numLibres++] = i;
                    }
                }

                if (numLibres == 0) {
                    aplicarLRU();
                }

                numLibres = 0;
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        marcosLibres[numLibres++] = i;
                    }
                }

                int marcoAleatorio = marcosLibres[rand() % numLibres];
                memoriaFisica[marcoAleatorio].paginaAsignada = temp2->tablaPaginas[pagSeleccionada].indicePagina;
                memoriaFisica[marcoAleatorio].idProceso = temp2->PID;
                temp2->tablaPaginas[pagSeleccionada].marcoAsignado = marcoAleatorio;
                temp2->tablaPaginas[pagSeleccionada].cargada = 1;
                temp2->tablaPaginas[pagSeleccionada].ultimoUso = contadorUso;
                contadorUso++;

                printf("Página %d asignada al marco %d.\n", pagSeleccionada, marcoAleatorio);
                todasAsignadas = 1;
                for (int i = 0; i < temp2->cantidadPaginas; i++) {
                    if (temp2->tablaPaginas[i].marcoAsignado == -1) {
                        todasAsignadas = 0;
                        break;
                    }
                }

                if (todasAsignadas) {
                    return;
                }

                printf("1.- Asignar otra página\n");
                printf("0.- Salir\n");
                scanf("%d", &opc);
            } while (opc != 0);

            return;
        }
        temp2 = temp2->siguiente;
    }

    printf("Proceso no encontrado.\n");
}

void aplicarLRU() {
    if (cabeza == NULL) {
        printf("No hay procesos registrados.\n");
        return;
    }

    Proceso *temp2 = cabeza;
    int paginaEliminar = -1;
    int menorUso = contadorUso;
    Proceso *auxProceso = NULL;

    while (temp2 != NULL) {
        for (int i = 0; i < temp2->cantidadPaginas; i++) {
            if (temp2->tablaPaginas[i].cargada && temp2->tablaPaginas[i].ultimoUso < menorUso) {
                menorUso = temp2->tablaPaginas[i].ultimoUso;
                paginaEliminar = i;
                auxProceso = temp2;
            }
        }
        temp2 = temp2->siguiente;
    }

    if (paginaEliminar == -1) {
        printf("No se encontró página cargada para eliminar.\n");
        return;
    }

    if (auxProceso != NULL) {
        int marcoLiberado = auxProceso->tablaPaginas[paginaEliminar].marcoAsignado;
        memoriaFisica[marcoLiberado].paginaAsignada = -1;
        auxProceso->tablaPaginas[paginaEliminar].marcoAsignado = -1;
        auxProceso->tablaPaginas[paginaEliminar].cargada = 0;
        printf("Página %d eliminada del marco %d del proceso[%d].\n", paginaEliminar, marcoLiberado, memoriaFisica[marcoLiberado].idProceso);
        printf("\n");
        memoriaFisica[marcoLiberado].idProceso = -1;
    }
}

int main() {
    srand(time(NULL));

    // Inicializar Memoria Física
    for (int i = 0; i < totalMarcos; i++) {
        memoriaFisica[i].numeroMarco = i;
        memoriaFisica[i].paginaAsignada = -1;
    }

    int opcion = 0;
    do {
        printf("------------- Menú -------------\n");
        printf("1.- Crear Proceso\n");
        printf("2.- Asignar Páginas\n");
        printf("3.- Mostrar Procesos\n");
        printf("4.- Mostrar Memoria Física\n");
        printf("5.- Salir\n");
        printf("--------------------------------\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearProceso();
                break;
            case 2:
                asignarPaginas();
                break;
            case 3:
                imprimirTablasProcesos();
                break;
            case 4:
                imprimirMemoriaFisica();
                break;
            case 5:
                return 0;
            default:
                printf("Opción inválida\n");
                break;
        }
    } while (true);

    return 0;
}
