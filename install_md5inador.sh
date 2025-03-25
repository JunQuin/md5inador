#!/bin/bash

# URL del binario md5inador
BINARY_URL="https://github.com/JunQuin/md5inador/releases/download/main/md5inador"
BINARY_NAME="md5inador"
INSTALL_DIR="$HOME/bin"

# Verificar si 'curl' está instalado
if ! command -v curl &> /dev/null; then
  echo "Error: curl no está instalado. Por favor, instálalo antes de ejecutar este script."
  exit 1
fi

# Crear el directorio ~/bin/ si no existe
mkdir -p "$INSTALL_DIR"

# Descargar el binario y guardarlo en ~/bin/
curl -sSL "$BINARY_URL" -o "$INSTALL_DIR/$BINARY_NAME"

# Verificar si la descarga fue exitosa
if [ $? -ne 0 ]; then
  echo "Error: la descarga del binario falló."
  exit 1
fi

# Hacer el binario ejecutable
chmod +x "$INSTALL_DIR/$BINARY_NAME"

# Agregar ~/bin/ al PATH en ~/.bashrc
if [ -f "$HOME/.bashrc" ]; then
  echo 'export PATH="$HOME/bin:$PATH"' >> "$HOME/.bashrc"
  echo "Se ha agregado ~/bin/ al PATH en ~/.bashrc."
fi

# Agregar ~/bin/ al PATH en ~/.zshrc si existe
if [ -f "$HOME/.zshrc" ]; then
  echo 'export PATH="$HOME/bin:$PATH"' >> "$HOME/.zshrc"
  echo "Se ha agregado ~/bin/ al PATH en ~/.zshrc."
fi

# Informar al usuario que ejecute source para aplicar los cambios
echo "Instalación completada. Por favor, ejecuta 'source ~/.bashrc' y/o 'source ~/.zshrc' para aplicar los cambios al PATH."

exit 0
