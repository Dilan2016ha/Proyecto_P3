#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100 //sirve para definir el maximo de productos y poder utilizarlo en todas las funciones
#define MAX_NOMBRE 100 //sirve para definir el maximo de caracteres para un nombre de un producto
#define MAX_LINEA 256 //sirve para que al momento de leer una linea (nombre, cantidad y precio)  no se pase de los 256 caracteres

typedef struct //sirve para definir las variables que van a utilizarse en el programa
{
    char nombre[MAX_NOMBRE];
    int cantidad;
    float precio;
} Producto;

void ingresarProducto()
{
    Producto nuevoProducto; //darle un nombre al grupo de variables de la estructura

    printf("Ingrese el nombre del producto: \n");
    getchar();//solucion del error al momento de ingresar el nombre 
    fgets(nuevoProducto.nombre, MAX_NOMBRE, stdin);
    //fgets se utiliza para leer una línea de texto y stdin es una entrada estandar 
    nuevoProducto.nombre[strcspn(nuevoProducto.nombre, "\n")] = '\0';
    //Se utiliza para terminar la variable nuevoProducto.nombre con un caracter nulo y asi evitar problemas de manejo 
    // y la muestra de datos

    printf("Ingrese la cantidad del producto: \n");
    scanf("%d", &nuevoProducto.cantidad);

    printf("Ingrese el precio del producto: \n");
    scanf("%f", &nuevoProducto.precio);

    // Abrir el archivo en modo escritura "a" para agregar el nuevo producto al final del arcivo 
    // y asi evitar tener problemas con los datos guardados anteriormente
    FILE *archivo = fopen("productos.txt", "a");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Escribir o Guardar el nuevo producto en el archivo
    fprintf(archivo, "%s,%d,%.2f\n", nuevoProducto.nombre, nuevoProducto.cantidad, nuevoProducto.precio);

    // Cerrar el archivo
    fclose(archivo);

    printf("Producto ingresado correctamente.\n");
}

void editarProducto()
{
    int indice;

    printf("Ingrese el numero de producto a editar (0-%d): ", MAX_PRODUCTOS - 1);
    scanf("%d", &indice);

    FILE *archivo = fopen("productos.txt", "r"); // se abre el archivo donde estan guardados los productos
    FILE *archivoTmp = fopen("productos_tmp.txt", "w");
    // se crea un nuevo archivo para otro producto y despues sobre escribirlo en el arcivo anterior

    if (archivo == NULL || archivoTmp == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Producto producto;
    int contador = 0;
    char linea[MAX_LINEA];

    while (fgets(linea, MAX_LINEA, archivo) != NULL)
    // se verifica que se pudo leer una línea de texto desde el archivo
    {
        if (contador == indice)
        {
            sscanf(linea, "%[^,],%d,%f", producto.nombre, &producto.cantidad, &producto.precio); // guarda los datos en el array linea
            //%[^,] sirve para leer una cadena de texto hasta encontrar una coma
            printf("Ingrese el nuevo nombre del producto: ");
            getchar();
            fgets(producto.nombre, MAX_NOMBRE, stdin);
            producto.nombre[strcspn(producto.nombre, "\n")] = '\0';

            printf("Ingrese la nueva cantidad del producto: ");
            scanf("%d", &producto.cantidad);

            printf("Ingrese el nuevo precio del producto: ");
            scanf("%f", &producto.precio);

            fprintf(archivoTmp, "%s,%d,%.2f\n", producto.nombre, producto.cantidad, producto.precio); 
            // se guarda los datos del producto editado en un archivo temporal

            printf("Producto editado correctamente.\n");
        }
        else
        {
            fprintf(archivoTmp, "%s", linea);
        }

        contador++;
    }

    fclose(archivo);
    fclose(archivoTmp);

    // Renombrar el archivo temporal al archivo original
    remove("productos.txt");
    rename("productos_tmp.txt", "productos.txt");
}

void eliminarProducto()
{
    int indice;

    printf("Ingrese el numero de producto a eliminar (0-%d): ", MAX_PRODUCTOS - 1);
    scanf("%d", &indice);

    FILE *archivo = fopen("productos.txt", "r");
    FILE *archivoTmp = fopen("productos_tmp.txt", "w");

    if (archivo == NULL || archivoTmp == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Producto producto;
    int contador = 0;
    char linea[MAX_LINEA];

    while (fgets(linea, MAX_LINEA, archivo) != NULL)
    {
        if (contador != indice)
        {
            fprintf(archivoTmp, "%s", linea);
        }
        else
        {
            sscanf(linea, "%[^,],%d,%f", producto.nombre, &producto.cantidad, &producto.precio);
            printf("Producto eliminado correctamente.\n");
        }

        contador++;
    }

    fclose(archivo);
    fclose(archivoTmp);

    // Renombrar el archivo temporal al archivo original
    remove("productos.txt");
    rename("productos_tmp.txt", "productos.txt");
}

void listarProductos()
{
    FILE *archivo = fopen("productos.txt", "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("----- LISTA DE PRODUCTOS -----\n");
    Producto producto;
    char linea[MAX_LINEA];
    int contador = 0;

    while (fgets(linea, MAX_LINEA, archivo) != NULL)
    {
        sscanf(linea, "%[^,],%d,%f", producto.nombre, &producto.cantidad, &producto.precio);
        printf("Producto %d:\n", contador);
        printf("Nombre: %s\n", producto.nombre);
        printf("Cantidad: %d\n", producto.cantidad);
        printf("Precio: %.2f\n", producto.precio);
        printf("-----------------------------\n");
        contador++;
    }

    fclose(archivo);
}