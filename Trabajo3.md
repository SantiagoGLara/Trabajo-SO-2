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

- Identifica los componentes clave de un sistema de archivos (por ejemplo, metadatos, tablas de asignación, etc.).
- Crea un cuadro comparativo de cómo estos componentes funcionan en sistemas como EXT4 y NTFS.
- Describe las ventajas y desventajas de cada sistema basado en sus componentes.

---

### Ejercicio 3: Organización lógica y física de archivos

**Descripción:**

- Crea un esquema que muestre la organización lógica y física de un sistema de archivos. Explica cómo se relacionan las estructuras lógicas con las físicas en el disco.

**Tareas:**

- Diseña un árbol jerárquico que represente la organización lógica de directorios y subdirectorios.
- Explica cómo se traduce la dirección lógica a la dirección física en el disco.
- Proporciona un ejemplo práctico de cómo un archivo se almacena físicamente.

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

