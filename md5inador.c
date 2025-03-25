#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h> // Necesario para basename

#define MAX_PATH_LENGTH 4096

void mostrar_ayuda(char *nombre_programa)
{
    printf("Uso: %s [OPCIONES] ARCHIVO\n", nombre_programa);
    printf("Genera un MD5 checksum para el archivo especificado.\n\n");
    printf("Opciones:\n");
    printf("  -h, --help    Muestra esta ayuda y sale\n\n");
    printf("Ejemplo:\n");
    printf("  %s miarchivo.txt\n", nombre_programa);
    exit(0);
}

int main(int argc, char *argv[])
{
    char *nombre_archivo = NULL;
    char path[MAX_PATH_LENGTH];
    char file_path[MAX_PATH_LENGTH];
    char pack_path[MAX_PATH_LENGTH];

    // Verificar argumentos
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
    {
        mostrar_ayuda(argv[0]);
    }
    else if (argc == 2)
    {
        nombre_archivo = argv[1];
    }
    else
    {
        printf("Argumento Invalido\n");
        printf("  -h, --help    Muestra ayuda\n");
        return 1;
    }

    if (nombre_archivo == NULL)
    {
        return 1;
    }

    // Obtener la ruta absoluta del directorio de trabajo
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("Error al obtener el directorio de trabajo");
        return 1;
    }

    // Construir la ruta completa del archivo
    if (snprintf(file_path, sizeof(file_path), "%s/%s", path, nombre_archivo) >= sizeof(file_path))
    {
        fprintf(stderr, "Error: la ruta del archivo es demasiado larga\n");
        return 1;
    }

    // Crear la ruta para el directorio 'pack'
    if (snprintf(pack_path, sizeof(pack_path), "%s/pack", path) >= sizeof(pack_path))
    {
        fprintf(stderr, "Error: la ruta del directorio 'pack' es demasiado larga\n");
        return 1;
    }

    // Verificar si pack_path ya tiene una barra final
    size_t pack_path_len = strlen(pack_path);
    if (pack_path[pack_path_len - 1] != '/')
    {
        strncat(pack_path, "/", sizeof(pack_path) - pack_path_len - 1);
    }

    // Verificar si el archivo existe
    struct stat st;
    if (stat(file_path, &st) != 0) // Usar file_path para stat
    {
        printf("El archivo no existe\n");
        return 1;
    }

    // Validar existencia de carpeta pack
    if (stat(pack_path, &st) == 0)
    {
        // Si el directorio ya existe, eliminarlo y recrearlo
        printf("INFO: El directorio 'pack' ya existe. Intentando eliminarlo: %s\n", pack_path);
        char cmd[MAX_PATH_LENGTH];
        if (snprintf(cmd, sizeof(cmd), "rm -r %s", pack_path) >= sizeof(cmd))
        {
            fprintf(stderr, "Error: el comando 'rm' es demasiado largo\n");
            return 1;
        }
        if (system(cmd) != 0)
        {
            fprintf(stderr, "Error al eliminar el directorio 'pack': %s\n", pack_path);
            return 1;
        }

        printf("INFO: Directorio 'pack' eliminado exitosamente. Intentando recrearlo: %s\n", pack_path);
        if (mkdir(pack_path, 0777) != 0)
        {
            perror("Error al recrear el directorio pack");
            return 1;
        }
        else
        {
            printf("INFO: Directorio 'pack' recreado exitosamente: %s\n", pack_path);
        }
    }
    // Crear directorio 'pack' si no existe
    else
    {
        printf("INFO: creando nuevo directorio 'pack': %s\n", pack_path);
        mkdir(pack_path, 0777);
    }

    // Verificar si el directorio 'pack' se creó correctamente
    if (stat(pack_path, &st) != 0)
    {
        fprintf(stderr, "Error: el directorio pack no se creó correctamente.\n");
        return 1;
    }

    // Crear la ruta para el archivo MD5
    char md5_file_path[MAX_PATH_LENGTH];
    char nombre_sin_extension[MAX_PATH_LENGTH];

    // Obtener solo el nombre del archivo sin la ruta
    char *nombre_archivo_base = basename(nombre_archivo);

    // Copiar el nombre del archivo base
    strcpy(nombre_sin_extension, nombre_archivo_base);

    // Eliminar la extensión del archivo para el nombre del archivo MD5
    char *dot = strrchr(nombre_sin_extension, '.');
    if (dot != NULL)
    {
        *dot = '\0';
    }

    // Corregir la creación de la ruta para el archivo MD5
    printf("INFO: Creando la ruta del archivo MD5: %s\n", md5_file_path);
    if (snprintf(md5_file_path, sizeof(md5_file_path), "%s%s.txt", pack_path, nombre_sin_extension) >= sizeof(md5_file_path))
    {
        fprintf(stderr, "Error: la ruta para el archivo MD5 es demasiado larga\n");
        return 1;
    }
    printf("INFO: Ruta del archivo MD5 creada correctamente: %s\n", md5_file_path);

    // Ejecutar el comando md5sum
    printf("INFO: Calculando el MD5 del archivo: %s\n", file_path);
    char md5_command[MAX_PATH_LENGTH];
    if (snprintf(md5_command, sizeof(md5_command), "md5sum \"%s\" > \"%s\"", nombre_archivo, md5_file_path) >= sizeof(md5_command))
    {
        fprintf(stderr, "Error: el comando 'md5sum' es demasiado largo\n");
        return 1;
    }
    if (system(md5_command) != 0)
    {
        perror("Error al calcular el MD5");
        return 1;
    }
    printf("INFO: MD5 calculado y guardado en: %s\n", md5_file_path);

    // Copiar el archivo al directorio 'pack'
    printf("INFO: Copiando el archivo: %s a %s\n", file_path, pack_path);
    char copy_command[MAX_PATH_LENGTH];
    if (snprintf(copy_command, sizeof(copy_command), "cp \"%s\" \"%s\"", file_path, pack_path) >= sizeof(copy_command))
    {
        fprintf(stderr, "Error: el comando 'cp' es demasiado largo\n");
        return 1;
    }
    if (system(copy_command) != 0)
    {
        perror("Error al copiar el archivo");
        return 1;
    }
    printf("INFO: Archivo copiado correctamente a: %s\n", pack_path);

    printf("INFO: Pack generado correctamente.\n");
    return 0;
}
