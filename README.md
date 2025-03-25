# Índice

1. [Características](#caracter%C3%ADsticas)
2. [Instalación](#instalaci%C3%B3n)
3. [Uso](#uso)

---

# md5inador

**md5inador** es una herramienta de línea de comandos diseñada para generar el hash MD5 de un archivo proporcionado, guardar el resultado en un archivo de texto dentro de un directorio llamado *pack*, y, adicionalmente, copiar el archivo original a dicho directorio para mantener una copia del archivo procesado.

## Características

- ✅ Genera el hash MD5 de cualquier archivo.
- 📄 Guarda el hash MD5 en un archivo `.txt` dentro de un directorio `pack`.
- 📦 Copia el archivo original al directorio `pack` para preservar una copia.
- ⚡ Script de instalación automatizado (`install_md5inador.sh`) para facilitar la instalación.

## Instalación

### Requisitos

- **curl** debe estar instalado en tu sistema.

### Script de instalación (install_md5inador.sh)

El script `install_md5inador.sh` automatiza la instalación de **md5inador**. Aquí tienes los pasos para usarlo:

1. **Descargar el script**  
   Puedes descargar el script directamente o clonar el repositorio.

   O usando **curl**:
   Abre una terminal y ejecuta el siguiente comando para descargar el script de instalación:
   ```bash
   curl -sSL https://raw.githubusercontent.com/JunQuin/md5inador/refs/heads/main/install_md5inador.sh -o install_md5inador.sh
   ```

3. **Haz el script ejecutable**  
   Abre una terminal y ejecuta el siguiente comando para darle permisos de ejecución al script:

   ```bash
   chmod +x install_md5inador.sh

4. **Ejecutar el script**
   Luego, corre el script con:
   ```bash
   ./install_md5inador.sh
   ```
   El script realizará lo siguiente:
  - Descargará el binario **md5inador** desde la URL especificada.
  - Creará el directorio `~/bin/` si no existe.
  - Copiará el binario `md5inador` a `~/bin/`.
  - Establecerá el binario como ejecutable.
  - Agregará `~/bin/` a tu PATH en `~/.bashr`c y `~/.zshrc` (si existen).

4. **Aplicar los cambios al PATH**
   Una vez que el script haya terminado, ejecuta uno de los siguientes comandos según el shell que utilices para aplicar los cambios en el PATH:

   `En caso de no conocer cual es, cerrar y volver a abrir la terminal funciona`.

   Para **Bash**:
   ```bash
   source ~/.bashrc
   ```

   Para **Zsh**:
   ```bash
   source ~/.zshrc
   ```

  ## Uso
  Para generar el hash MD5 de un archivo, simplemente ejecuta **md5inador** seguido del nombre del archivo:
  ```
  md5inador miarchivo.txt
  ```

  Este comando generará el hash MD5 del archivo `miarchivo.txt`, lo guardará en un archivo `.txt` dentro del directorio `pack` y copiará el archivo original al mismo directorio.
  
