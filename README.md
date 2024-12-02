# Trabajo-SO
### Santiago Gonzalez Lara <br>Sistemas Operativos<br>Profesor: Eduardo Alcaraz
### trabajo sistemas operativos <br>2 de diciembre de 2024


## Administración de Memoria<br>
### 3.1 Política y filosofía
1. **¿Cuál es la diferencia entre fragmentación interna y externa? Explica cómo cada una afecta el rendimiento de la memoria.**<br>
la fragmentacion interna es cuando un proceso es mas pequeño que su partición asignada, la memoria sobrante de la particion es inutilizable y a eso se le llama fragmentacion interna, en cambio la externa es cuando hay espacios de memoria sobrantes donde ya no cabe un proceso.<br> afecta porque tanto dentro de las particiones como fuera desperdicia pequeños espacios que acumulados podrían ser utilizados para muchos otros procesos.
2. **Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?**<br>
### 3.2 Memoria real
1. Escribe un programa en C o Python que simule la administración de
memoria mediante particiones fijas.
2. Diseña un algoritmo para calcular qué procesos pueden ser asignados
a un sistema con memoria real limitada utilizando el algoritmo de
"primera cabida".<br>
### 3.3 Organización de memoria virtual
1. Investiga y explica el concepto de "paginación" y "segmentación".
¿Cuáles son las ventajas y desventajas de cada técnica?
2. Escribe un programa que simule una tabla de páginas para procesos
con acceso aleatorio a memoria virtual.
### 3.4 Administración de memoria virtual
1. Escribe un código que implemente el algoritmo de reemplazo de página
"Least Recently Used" (LRU).
2. Diseña un diagrama que represente el proceso de traducción de direc-
ciones virtuales a físicas en un sistema con memoria virtual.
### Integración
1. Analiza un sistema operativo moderno (por ejemplo, Linux o Windows)
e identifica cómo administra la memoria virtual.
2. Realiza una simulación en cualquier lenguaje de programación que
emule el swapping de procesos en memoria virtual.
## Administración de Entrada/Salida
### 4.1 Dispositivos y manejadores de dispositivos
1. Explica la diferencia entre dispositivos de bloque y dispositivos de
carácter. Da un ejemplo de cada uno.
2. Diseña un programa que implemente un manejador de dispositivos sen-
cillo para un dispositivo virtual de entrada.
### 4.2 Mecanismos y funciones de los manejadores de dispositivos
1. Investiga qué es la interrupción por E/S y cómo la administra el sis-
tema operativo. Escribe un ejemplo en pseudocódigo para simular este
proceso.
2. Escribe un programa que utilice el manejo de interrupciones en un
sistema básico de simulación.
### 4.3 Estructuras de datos para manejo de dispositivos
1. Investiga y explica qué es una cola de E/S. Diseña una simulación de
una cola con prioridad.
2. Escribe un programa que simule las operaciones de un manejador de
dispositivos utilizando una tabla de estructuras.
### 4.4 Operaciones de Entrada/Salida
1. Diseña un flujo que describa el proceso de lectura de un archivo desde
un disco magnético. Acompáñalo con un programa básico que simule
el proceso.
2. Implementa un programa en Python, C o java que realice operaciones
de entrada/salida asíncronas usando archivos.
### Integración
1. Escribe un programa que implemente el algoritmo de planificación de
discos "Elevator (SCAN)".
2. Diseña un sistema que maneje múltiples dispositivos simulados (disco
duro, impresora, teclado) y muestra cómo se realiza la comunicación
entre ellos.
### Avanzados
1. Explica cómo los sistemas operativos modernos optimizan las opera-
ciones de entrada/salida con el uso de memoria caché.

