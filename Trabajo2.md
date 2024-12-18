# Comandos de Entrada y Salida, Discos y Archivos

## Ejercicio 1: Montar y Desmontar Discos
buscamos el disco (memoria) con el comando "lsblk"

```bash
sdb           8:16   1  28,9G  0 disk 
└─sdb1        8:17   1  28,9G  0 part /home santiago-fichi/usb
```
montamos el disco
```bash
sudo mount /dev/sdb1 /home/santiago-fichi/usb
```
nos damos cuenta que está mondado porque(en ubuntu) ahora nos aparece el siguiente icono en la barra de tareas<br>
![iconoMontaje](Montaje.png)<br>

o tambien, de una forma mas exacta podemos identificar su montaje exitoso con "df -h", en mi caso identificando la memoria /dev/sd1 de 29,1gb, que es mi memoria

```bash
df -h
S.ficheros     Tamaño Usados  Disp Uso% Montado en
tmpfs            1,4G   2,5M  1,4G   1% /run
/dev/sda5        491G    94G  372G  21% /
tmpfs            6,8G    94M  6,7G   2% /dev/shm
tmpfs            5,0M    12K  5,0M   1% /run/lock
efivarfs         148K   133K   11K  93% /sys/firmware/efi/efivars
/dev/sda4        1,1G    43M  1,1G   4% /boot/efi
tmpfs            1,4G   2,6M  1,4G   1% /run/user/1000
/dev/sdb1         29G    66M   29G   1% /home/santiago-fichi/usb

```

copiamos un archivo, meramente a manera de prueba

```bash
cp trabajosdesistemasoperativos.txt /home/santiago-fichi/usb
```
![copiaArchivo](CopiaArchivo.png)<br>
desmontamos para finalizar
```
sudo umount /dev/sdb1 /home/santiago-fichi/usb
umount: /home/santiago-fichi/usb: no montado.
```
y en efecto, ya no aparece montado
![fotodesMontado](desmontaje.png)
## ejercicio 2: Redirección de Entrada y Salida
ahora, vamos a guardar los archivos del directorio donde nos encontramos en un .txt con el siguiente comando

```bash
ls -l > listado.txt
```
y con el comando `cat listado.txt` mostramos el contenido del .txt, la salida es la siguiente
```bash
santiago-fichi@santiago-inspiron-15-3515:~$ ls -l > listado.txt
santiago-fichi@santiago-inspiron-15-3515:~$ cat listado.txt
total 164
drwxrwxr-x  7 santiago-fichi santiago-fichi  4096 nov 28 22:00 curso-HTML
-rw-rw-r--  1 santiago-fichi santiago-fichi 36868 dic 17 02:01 d1.png
drwxr-xr-x  8 santiago-fichi santiago-fichi  4096 dic 17 01:40 Descargas
-rw-rw-r--  1 santiago-fichi santiago-fichi 30112 dic 17 02:01 Diagrama1.dia
drwxr-xr-x  8 santiago-fichi santiago-fichi  4096 nov 26 14:04 Documentos
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Escritorio
drwxr-xr-x  5 santiago-fichi santiago-fichi  4096 dic 15 19:58 Imágenes
-rwxrwxr-x  1 santiago-fichi santiago-fichi 16752 dic 16 23:37 implementacionLRU
drwxrwxr-x  6 santiago-fichi santiago-fichi  4096 dic 10 14:26 kk
-rw-rw-r--  1 santiago-fichi santiago-fichi     0 dic 17 17:44 listado.txt
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Música
-rw-rw-r--  1 santiago-fichi santiago-fichi   314 sep  1 17:48 NOTAS ALBION ropa para.txt
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Plantillas
-rw-rw-r--  1 santiago-fichi santiago-fichi     0 nov  6 14:10 potsum ivrst
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Público
drwxrwxr-x  3 santiago-fichi santiago-fichi  4096 dic 17 17:38 SantiagoGLara
drwx------ 14 santiago-fichi santiago-fichi  4096 dic 10 14:26 snap
drwxrwxr-x  6 santiago-fichi santiago-fichi  4096 dic  1 09:25 SO PRACT
drwxrwxr-x  3 santiago-fichi santiago-fichi  4096 ago 28 17:40 The Escapists
-rw-rw-r--  1 santiago-fichi santiago-fichi   455 dic 15 19:58 trabajosdesistemasoperativos.txt
drwxrwxr-x  5 santiago-fichi santiago-fichi  4096 dic 17 17:33 Trabajo-SO-2
drwxrwxr-x  2 santiago-fichi santiago-fichi  4096 dic 15 19:39 usb
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Vídeos

```
ahora, con el siguiente comando le agregamos la fecha en la que hacemos las modificaciones hasta el final del .txt

```bash
date >> listado.txt
```
y volvemos a mostrar el contenido del archivo para comprobar el ultimo cambio
```bash
total 164
drwxrwxr-x  7 santiago-fichi santiago-fichi  4096 nov 28 22:00 curso-HTML
-rw-rw-r--  1 santiago-fichi santiago-fichi 36868 dic 17 02:01 d1.png
drwxr-xr-x  8 santiago-fichi santiago-fichi  4096 dic 17 01:40 Descargas
-rw-rw-r--  1 santiago-fichi santiago-fichi 30112 dic 17 02:01 Diagrama1.dia
drwxr-xr-x  8 santiago-fichi santiago-fichi  4096 nov 26 14:04 Documentos
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Escritorio
drwxr-xr-x  5 santiago-fichi santiago-fichi  4096 dic 15 19:58 Imágenes
-rwxrwxr-x  1 santiago-fichi santiago-fichi 16752 dic 16 23:37 implementacionLRU
drwxrwxr-x  6 santiago-fichi santiago-fichi  4096 dic 10 14:26 kk
-rw-rw-r--  1 santiago-fichi santiago-fichi     0 dic 17 17:44 listado.txt
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Música
-rw-rw-r--  1 santiago-fichi santiago-fichi   314 sep  1 17:48 NOTAS ALBION ropa para.txt
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Plantillas
-rw-rw-r--  1 santiago-fichi santiago-fichi     0 nov  6 14:10 potsum ivrst
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Público
drwxrwxr-x  3 santiago-fichi santiago-fichi  4096 dic 17 17:38 SantiagoGLara
drwx------ 14 santiago-fichi santiago-fichi  4096 dic 10 14:26 snap
drwxrwxr-x  6 santiago-fichi santiago-fichi  4096 dic  1 09:25 SO PRACT
drwxrwxr-x  3 santiago-fichi santiago-fichi  4096 ago 28 17:40 The Escapists
-rw-rw-r--  1 santiago-fichi santiago-fichi   455 dic 15 19:58 trabajosdesistemasoperativos.txt
drwxrwxr-x  5 santiago-fichi santiago-fichi  4096 dic 17 17:33 Trabajo-SO-2
drwxrwxr-x  2 santiago-fichi santiago-fichi  4096 dic 15 19:39 usb
drwxr-xr-x  2 santiago-fichi santiago-fichi  4096 ago 24 18:10 Vídeos
mar 17 dic 2024 17:49:18 CST
```
## ejercicio 3: Copiar y Mover Archivos
Crea un archivo de texto llamado `archivo1.txt`: 

```bash
echo "Este es un archivo de prueba" > archivo1.txt
```
copiamos este archivo en cualquier otro directorio, usamos /tmp como ejemplo
```bash
cp archivo1.txt /tmp/
```
ahora renombramos al archivo que está dentro de /tmp
```bash
mv /tmp/archivo1.txt /tmp/aguantePESCADORABIOSO_PAAAAa.txt
```
y ahora lo regresamos al directorio actual
```bash
mv /tmp/aguantePESCADORABIOSO_PAAAAa.txt
```
y en efecto, podemos ver que ambos archivos coexisten en el mismo directorio
![ambosArchivos](coexistencia.png)

## Ejercicio 4: Comprimir y Descomprimir Archivos
primero creamos un directorio con algunas copias de archivos, que es lo que le vamos a hacer backup
![directorioBackup](copiaDir.png)
ahora con el comando `tar -czvf backup.tar.gz backup/` lo comprimimos en un archivo del tipo tar.gz
```bash
ar -czvf backup.tar.gz backup/
backup/
backup/NOTAS ALBION ropa para.txt
backup/aguantePESCADORABIOSO_PAAAAa.txt
backup/archivo1.txt
backup/Diagrama1.dia
```
y en efecto se comprimió
![comprimido](comprimido.png)

ahora borramos el directorio original y extraemos a la vez el contenido del comprimido
```bash
tar -xzvf backup.tar.gz
backup/
backup/NOTAS ALBION ropa para.txt
backup/aguantePESCADORABIOSO_PAAAAa.txt
backup/archivo1.txt
backup/Diagrama1.dia
```
## Ejercicio 5: Permisos y Propiedades de Archivos
Creamos un archivo llamado `privado.txt`

```bash
touch privado.txt
```
ahora le cambiamos los permisos
```bash
```

```bash
```

```bash
```
```bash
```
```bash
```
```bash
```
```bash
```
```bash
```
```bash
```