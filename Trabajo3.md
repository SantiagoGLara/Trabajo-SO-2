## Sistemas de Archivos

### Ejercicio 1: Concepto y noción de archivo real y virtual

**Descripción:**

- Define los conceptos de archivo real y archivo virtual y explica sus diferencias.
- Identifica ejemplos prácticos de cada tipo en sistemas operativos actuales.

**Tareas:**

- **Define el concepto de archivo real y archivo virtual.** <br>
**archivo real:** es un archivo que contiene programas, datos o cualquier otro elemento. 
Un archivo se muestra de manera real, en la información del espacio que ocupa en un disco duro o sistema de almacenamiento, en otras palabras, su tamaño es en bytes(o su escala).
<br>
**archivo virtual:** es un archivo temporal utilizado por los procesos mientras estos lo necesitan, se crean durante la ejecucion de sistema para almacenar, intercambiar e organizar informacion. Terminan cuando el proceso que los necesita acaba.
- **Proporciona ejemplos de cómo los sistemas operativos manejan archivos reales y virtuales.**<br>
en ambos, un ejemplo de como se manejan los archivos reales es la forma "jerarquica" en la que podemos ver como están almacenados, ya sea en NFTS en windows o exfat4 en linux<br>
en caso de los archivos virtuales, windows tiene el ejemplo de los archivos de paginación, que son archivos temporales que contienen partes de la memoria RAM que no se están utilizando activamente. Permiten que el sistema operativo pueda utilizar más memoria de la que físicamente tiene instalada. Con ubuntu podrían ser las búsquedas virtuales, donde el sistema de archivos virtual (VFS) de Linux permite unificar el acceso a diferentes tipos de dispositivos de almacenamiento, como discos duros, unidades de red y dispositivos USB.
- **Explica un caso práctico donde un archivo virtual sea más útil que un archivo real.**<br>
por ejemplo, cuando necesitamos la informacion en tiempo real de los procesos en ejecucion del sistema y todo lo referente a ellos, basicamente como la que nos da el administrador de tareas del sistema operativo, en ese caso los archvios virtuales nos ayudan a almacenar temporalmente esa informacion. De hacerlo con archivos reales, sería mas tardado y costoso, al implicar demasiadas lecturas y escrituras, ademas implicando un desgaste excesivo sobre el dispositivo de almacenamiento
---

### Ejercicio 2: Componentes de un sistema de archivos

**Descripción:**

- Investiga los componentes principales de un sistema de archivos y compáralos entre dos sistemas operativos, como Linux y Windows.

**Tareas:**

- **Identifica los componentes clave de un sistema de archivos (por ejemplo, metadatos, tablas de asignación, etc.).**<br>
1. superbloque: contiene informacion del sistema de archivos en general, como su tamaño, numero de bloques, ubicacion del sistema de datos, entre otros datos.
2. bloques de datos: guardan los datos reales de los archivos
3. inodos: tambien conocidos como nodos indice, contienen la informacion de los archivos, como su propietario, tamaño, permisos.
4. directorios: Son estructuras que organizan archivos en una jerarquía. Cada directorio puede contener archivos y subdirectorios.
Los directorios son gestionados por tablas o estructuras específicas que almacenan los nombres de los archivos y referencias a sus inodos.
5. tablas de asignacion: son estructuras de datos que se encargan de rastrear cómo se asigna el espacio de almacenamiento físico del disco a los archivos y directorios.
6. registros de journaling: registro de cambios, evita la corrupcion de los archivos
7. metadatos: nformación sobre cada archivo y directorio como el nombre del archivo, fecha de creación, modificación y acceso, Permisos de acceso, propietario, tamaño y grupo.
  

- **Crea un cuadro comparativo de cómo estos componentes funcionan en sistemas como EXT4 y NTFS.**<br>

### Comparación entre ext4 y NTFS

| **Componente**               | **ext4 (Linux)**                                                                 | **NTFS (Windows)**                                                                   |
|-------------------------------|----------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **Superbloque**              | Guarda información sobre el sistema de archivos (tamaño, estado, bloques). Tiene copias redundantes para seguridad. | Lo equivalente es la "Master File Table (MFT)", que guarda metadatos de todos los archivos y tiene copias de respaldo. |
| **Bloques de datos**         | Tamaño personalizable (1 KB, 2 KB, 4 KB, etc.) para almacenar los datos reales. Se agrupan en grupos para eficiencia. | Usa clústeres (grupos de sectores). El tamaño se ajusta automáticamente según el disco. |
| **Inodos**                   | Cada archivo tiene un inodo con su información (permisos, dueño, ubicación de datos). | NTFS no usa inodos. En su lugar, toda la información está en la MFT. |
| **Directorios**              | Organizados en una jerarquía con referencias a los inodos correspondientes. | También son jerárquicos, pero las carpetas son entradas en la MFT que apuntan a otros archivos o carpetas. |
| **Metadatos**                | Incluyen el nombre, tamaño, permisos y fechas, almacenados en los inodos. | Centralizados en la MFT, con soporte adicional para datos secundarios (streams). |
| **Gestión de espacio libre** | Usa mapas de bits para rastrear bloques libres y ocupados. | También usa un mapa de bits para identificar clústeres libres. |
| **Controladores de almacenamiento** | Compatible con HDD, SSD y almacenamiento en red. Soporta journaling para evitar corrupción. | Optimizado para discos locales y tiene soporte para compresión y cifrado. |
| **Caché de sistema de archivos** | Usa memoria RAM para acelerar el acceso a datos usados frecuentemente. | Similar, utiliza caché para mejorar el rendimiento en acceso a datos. |
| **Control de acceso y seguridad** | Basado en permisos POSIX y listas de control de acceso (ACL). | Usa listas de control de acceso (ACL) integradas con permisos de Windows. |
| **Registros de journaling**  | Lleva un registro de cambios para evitar corrupción en caso de fallos. | También tiene journaling avanzado con registro detallado de transacciones. |
| **Compatibilidad**           | Es nativo de Linux, pero se puede leer en otros sistemas con herramientas especiales. | Es nativo de Windows, pero puede ser usado en Linux o macOS con programas adicionales. |


- **Describe las ventajas y desventajas de cada sistema basado en sus componentes.**<br>
   ### Comparación entre NTFS y ext4

| **Característica**         | **NTFS**                                                                 | **ext4**                                                      |
|-----------------------------|--------------------------------------------------------------------------|---------------------------------------------------------------|
| **Compatibilidad**          | Nativo en Windows, funcional en Linux/macOS con herramientas adicionales. | Nativo en Linux, funcional en Windows/macOS con herramientas. |
| **Rendimiento**             | Bueno para archivos grandes, pero más lento con fragmentación.           | Excelente para archivos pequeños y muchos directorios.        |
| **Fragmentación**           | Propenso a fragmentarse.                                                | Muy resistente a la fragmentación.                           |
| **Funciones avanzadas**     | Compresión, cifrado, cuotas de disco, flujos de datos alternativos.      | Carece de estas funciones.                                    |
| **Recuperación de datos**   | Buena, gracias al journaling avanzado y la MFT.                         | Limitada, requiere herramientas específicas.                  |


---

### Ejercicio 3: Organización lógica y física de archivos

**Descripción:**

- Crea un esquema que muestre la organización lógica y física de un sistema de archivos. Explica cómo se relacionan las estructuras lógicas con las físicas en el disco.

**Tareas:**

- Diseña un árbol jerárquico que represente la organización lógica de directorios y subdirectorios.
![diagramaJerarquica](Diagrama1.png)
- **Explica cómo se traduce la dirección lógica a la dirección física en el disco.**<br>
Cuando un proceso entra en el estado de ejecución, un registro especial del procesador, a menudo llamado **registro base**, se carga con la dirección inicial del programa en la memoria principal. Además, existe un registro llamado **registro límite** o "valla", que marca la posición final de la memoria asignada al programa. Estos valores se configuran cuando el programa se carga en la memoria o cuando la imagen del proceso se transfiere a ella.
<br>Durante la ejecución del proceso, se utilizan **direcciones relativas**. Estas incluyen las direcciones almacenadas en el registro de instrucciones, las direcciones de saltos o llamadas (instrucciones `call`), y las direcciones de datos especificadas en instrucciones de carga y almacenamiento. El procesador procesa estas direcciones relativas en dos pasos:
1. **Cálculo de la dirección absoluta**: Se suma el valor del registro base a la dirección relativa para obtener una dirección absoluta.
2. **Verificación de límites**: La dirección absoluta se compara con el valor del registro límite. Si la dirección está dentro del rango permitido, la instrucción puede ejecutarse. Si no, se genera una interrupción, que el sistema operativo debe gestionar adecuadamente.
<br>
Este mecanismo asegura que el proceso no acceda a regiones de memoria fuera de las asignadas, protegiendo así la estabilidad del sistema.
podemos verlo en la siguiente imagen:
![traduccionDireccionesLibro](image-2.png)

- Proporciona un ejemplo práctico de cómo un archivo se almacena físicamente.
Creación del archivo: Supongamos que creas documento.txt, un archivo de 5 KB.

División en bloques: El archivo se divide en partes según el tamaño de los clusters. Si cada cluster es de 4 KB: Los primeros 4 KB ocupan un cluster. El último 1 KB ocupa otro cluster (aunque deja 3 KB vacíos por el tamaño fijo).

Asignación de clusters: El sistema de archivos encuentra clusters libres en el disco. Por ejemplo: el archivo se almacena en los clusters 1000 y 2000.

Registro en la tabla del sistema de archivos:
 Se guarda en una tabla (como la MFT en NTFS) la información del archivo: nombre, tamaño, y los clusters asignados (1000 y 2000).

---

### Ejercicio 4: Mecanismos de acceso a los archivos

**Descripción:**

- Simula diferentes mecanismos de acceso a archivos (secuencial, directo e indexado) en un entorno práctico.

**Tareas:**

1. Define los diferentes mecanismos de acceso.
2. Escribe un pseudocódigo que muestre cómo acceder a:
   - Un archivo secuencialmente.
   - Un archivo directamente mediante su posición.
   - Un archivo utilizando un índice.
3. Compara las ventajas de cada mecanismo dependiendo del caso de uso.

---

### Ejercicio 5: Modelo jerárquico y mecanismos de recuperación en caso de falla

**Descripción:**

- Diseña una estructura jerárquica para un sistema de archivos y simula un escenario de falla en el sistema. Describe cómo recuperar los datos utilizando mecanismos de recuperación.

**Tareas:**

- Diseña un modelo jerárquico para un sistema de archivos con al menos tres niveles de directorios.
- Simula una falla en un directorio específico y describe los pasos necesarios para recuperarlo.
- Explica el concepto de protección basada en el lenguaje.
- Proporciona un ejemplo de cómo un lenguaje como Java o Rust asegura la memoria y evita accesos no autorizados.
- Compara este enfoque con otros mecanismos de protección en sistemas operativos.

---

### Ejercicio 6: Validación y amenazas al sistema

**Descripción:**

- Analiza las principales amenazas a un sistema operativo y los mecanismos de validación utilizados para prevenirlas.

**Tareas:**

- Investiga y describe al menos tres tipos de amenazas comunes (por ejemplo, malware, ataques de fuerza bruta, inyección de código).
- Explica los mecanismos de validación como autenticación multifactor y control de integridad.
- Diseña un esquema de validación para un sistema operativo con múltiples usuarios.

---

### Ejercicio 7: Cifrado

**Descripción:**

- Explora cómo los mecanismos de cifrado protegen la información en un sistema operativo.

**Tareas:**

- Define los conceptos de cifrado simétrico y asimétrico.
- Proporciona un ejemplo práctico de cada tipo de cifrado aplicado en sistemas operativos.
- Simula el proceso de cifrado y descifrado de un archivo con una clave dada.

