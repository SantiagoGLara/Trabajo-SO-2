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


```
```