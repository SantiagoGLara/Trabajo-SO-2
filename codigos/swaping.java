import java.util.LinkedList;
import java.util.Queue;

class Proceso {
    int idProceso;
    int tamanioProceso;

    public Proceso(int id, int tamanio) {
        this.idProceso = id;
        this.tamanioProceso = tamanio;
    }

    @Override
    public String toString() {
        return "Proceso{" +
                "idProceso=" + idProceso +
                ", tamanioProceso=" + tamanioProceso +
                '}';
    }
}

class GestorMemoria {
    int capacidadMemoria;
    Queue<Proceso> procesosEnMemoria;

    public GestorMemoria(int capacidad) {
        this.capacidadMemoria = capacidad;
        this.procesosEnMemoria = new LinkedList<>();
    }

    public boolean asignarProceso(Proceso proceso) {
        int espacioNecesario = proceso.tamanioProceso;
        int espacioOcupado = obtenerEspacioOcupado();

        if (espacioOcupado + espacioNecesario <= capacidadMemoria) {
            procesosEnMemoria.add(proceso);
            System.out.println("Proceso " + proceso.idProceso + " asignado a memoria.");
            return true;
        } else {
            return false;
        }
    }

    private int obtenerEspacioOcupado() {
        int espacioOcupado = 0;
        for (Proceso p : procesosEnMemoria) {
            espacioOcupado += p.tamanioProceso;
        }
        return espacioOcupado;
    }

    public void realizarSwapping(Proceso proceso) {
        if (!asignarProceso(proceso)) {
            System.out.println("Memoria llena, realizando swapping...");

            Proceso procesoExpulsado = procesosEnMemoria.poll();
            if (procesoExpulsado != null) {
                System.out.println("Proceso " + procesoExpulsado.idProceso + " intercambiado a disco (swapped out).");
                asignarProceso(proceso);
            } else {
                System.out.println("No hay procesos para intercambiar.");
            }
        }
    }

    public void mostrarEstadoMemoria() {
        System.out.println("Estado actual de la memoria:");
        if (procesosEnMemoria.isEmpty()) {
            System.out.println("La memoria está vacía.");
        } else {
            for (Proceso p : procesosEnMemoria) {
                System.out.println(p);
            }
        }
        System.out.println("Espacio ocupado: " + obtenerEspacioOcupado() + "/" + capacidadMemoria);
    }
}

public class swaping {

    public static void main(String[] args) {

        GestorMemoria gestorMemoria = new GestorMemoria(500);

        Proceso[] procesos = {
                new Proceso(1, 100),
                new Proceso(2, 150),
                new Proceso(3, 200),
                new Proceso(4, 100),
                new Proceso(5, 50)
        };

        for (Proceso proceso : procesos) {
            gestorMemoria.realizarSwapping(proceso);
            gestorMemoria.mostrarEstadoMemoria();
            System.out.println("--------------------");
        }
    }
}