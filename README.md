# md5inador

`md5inador` es una herramienta de línea de comandos que genera el hash MD5 de un archivo proporcionado y guarda el resultado en un archivo de texto dentro de un directorio llamado `pack`. Además, copia el archivo original al directorio `pack` para mantener una copia del archivo procesado.

## Características

* Genera el hash MD5 de un archivo.
* Guarda el hash MD5 en un archivo `.txt` dentro de un directorio `pack`.
* Copia el archivo original al directorio `pack`.
* Script de instalación (`install_md5inador.sh`) para facilitar la instalación.

## Uso

Para generar el hash MD5 de un archivo, simplemente ejecuta `md5inador` seguido del nombre del archivo:

```bash
md5inador miarchivo.txt
