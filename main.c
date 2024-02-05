#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pila.h"
#include <stdbool.h>

#define max_Nusuario 20
#define max_Nclave 20
#define max_Nproducto 50
#define max_Nlote 10

///ESTRUCTURAS
typedef struct
{
    char nombre_usuario[max_Nusuario];
    char clave[max_Nclave];
    char nombre[30];
    char apellido[30];
    char documento[20];
    char edad[20];
    char mail[30];
    char genero[1]; //m o f
} nuevo_usuario;

typedef struct
{
    char lote[max_Nlote];
    char nombre_producto[max_Nproducto];
    float precio;
    int cantidad;
} nuevo_producto;

///PROTOTIPADOS
//{
int verificar_info_usuario(const char *nombre_usuario, const char *clave);
int verificar_lote_existente(const char *lote);
bool validar_numeros(char numero[]);
int validarNombre(char nombre[]);
int validarGenero(const char *genero);
int validarDato(const char *dato);
void pila_para_cargar();
void pila_para_procesar();
void pila_para_agregar();
void menu_principal();
void registrar_usuario();
int iniciar_sesion(Pila *dada);
void switch_de_opciones();
void menu_de_opciones();
void agregar_producto();
void eliminar_producto();
void mostrar_producto();
void buscar_producto();
void mostrar_usuario();
void modificar_usuario();
//}


int main()
{
    Pila dada;
    system("color e");
    int eleccion;
    int inic_sesion;
    int i=0;
    int j=0;
    char volver_al_menu;

    do {
    printf("\n");
    printf("****************************************\n");
    printf("*            MENU PRINCIPAL            *\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*   1. Crear usuario                   *\n");
    printf("*   2. Ingresar al Sistema             *\n");
    printf("*   3. Salir                           *\n");
    printf("*                                      *\n");
    printf("****************************************\n");
    printf("\n");

        while(!i)
        {
        printf("\nSelecciona una opcion: ");
        if(scanf("%d", &eleccion)==1)
        {
        switch(eleccion)
        {
        case 1:
            system("cls");
            registrar_usuario();
            menu_principal();
            break;
        case 2:
            system("cls");
            inic_sesion=iniciar_sesion(&dada);
            int eleccion2;

            if(inic_sesion==0)
            {
                switch_de_opciones();
            }
            break;
                case 3:
                    system("cls");
                    printf("¡Hasta luego!\n");
                    return 0;
                    break;

                default:
                    system("cls");
                    printf("Opcion invalida. Intentalo de nuevo.\n");
                    menu_principal();
                    break;
            }
        }else
            {
                system("cls");
                printf("\nError: solo se puede ingresar un valor numerico\n");
                fflush(stdin);
                menu_principal();
            }
        }
                printf("\n");
    }while(eleccion >=1 && eleccion <=2);

    return 0;
}

///VERIFICAR LA INFORMACION DEL USUARIO
int verificar_info_usuario(const char *nombre_usuario, const char *clave)
{
    FILE *archi=fopen("usuarios.bin", "rb");
    if(archi==NULL)
    {
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    nuevo_usuario usuario;
    while(fread(&usuario, sizeof(nuevo_usuario), 1, archi))
    {
        if(strcmp(usuario.nombre_usuario, nombre_usuario) == 0 && strcmp(usuario.clave, clave) == 0)
        {
            fclose(archi);
            return 1;
        }
    }
    fclose(archi);
    return 0;
}

///VERIFICAR LA INFORMACION DEL LOTE
int verificar_lote_existente(const char *lote)
{
    FILE *archi = fopen("productos.bin", "rb");

    nuevo_producto producto;

    while (fread(&producto, sizeof(nuevo_producto), 1, archi)) {
        if (strcmp(producto.lote, lote) == 0) {
            fclose(archi);
            return 1;
        }
    }

    fclose(archi);
    return 0;
}

///BOOL PARA NUMEROS
bool validar_numeros(char numero[])
{
    int i;
    for(i=0; i<strlen(numero); i++)
    {
        if(!(numero[i]>=48 && numero[i]<=57))
        {
            printf("SOLO INGRESA NUMEROS\n");
            return false;
        }
    }
    return true;
}

///BOOL PARA CARACTERES
int validarNombre(char nombre[])
{
    int i;
    for(i=0 ; i<strlen(nombre); i++)
    {
        if(!(nombre[i]>=65 && nombre[i]<=90 || nombre[i]>=97 && nombre[i]<=122))
        {
            printf("SOLO INGRESA LETRAS");
            return 0;
        }
    }
    return 1;
}

///VALIDAR GENERO
int validarGenero(const char *genero)
{
    if (strlen(genero) > 1) {
        const char* caracteres_adicionales = genero + 1;
        while (*caracteres_adicionales != '\0') {
            if (*caracteres_adicionales != ' ') {
                printf("SOLO 'M' o 'F'\n");
                return 0;
            }
            caracteres_adicionales++;
        }
    }

    char primer_caracter = genero[0];
    if (primer_caracter == 'm' || primer_caracter == 'M' || primer_caracter == 'f' || primer_caracter == 'F') {
        return 1;
    } else {
        printf("SOLO 'M' o 'F'\n");
        return 0;
    }
}

///VALIDAR DATOS(QUE SEAN CARACTERES)
int validarDato(const char *dato)
{
    int i = 0;

    while (dato[i]) {
        if (!isalpha(dato[i]) && !isspace(dato[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

///PILA PARA CARGAR
void pila_para_cargar()
{

    Pila dada;
    inicpila(&dada);
    apilar(&dada, '.');
    apilar(&dada, '.');
    apilar(&dada, '.');
    apilar(&dada, 'o');
    apilar(&dada, 'd');
    apilar(&dada, 'n');
    apilar(&dada, 'a');
    apilar(&dada, 'g');
    apilar(&dada, 'r');
    apilar(&dada, 'a');
    apilar(&dada, 'C');

while(!pilavacia(&dada))
{
    char elemento = tope(&dada);
    printf("%c", elemento);
    desapilar(&dada);
    usleep(100000);
}
printf("\n");
usleep(300000);
}

///PILA PARA PROCESAR
void pila_para_procesar()
{
    Pila procesar;
    inicpila(&procesar);
    apilar(&procesar, '.');
    apilar(&procesar, '.');
    apilar(&procesar, '.');
    apilar(&procesar, 'o');
    apilar(&procesar, 'd');
    apilar(&procesar, 'n');
    apilar(&procesar, 'a');
    apilar(&procesar, 's');
    apilar(&procesar, 'e');
    apilar(&procesar, 'c');
    apilar(&procesar, 'o');
    apilar(&procesar, 'r');
    apilar(&procesar, 'P');

while(!pilavacia(&procesar))
{
    char elemento = tope(&procesar);
    printf("%c", elemento);
    desapilar(&procesar);
    usleep(100000);
}
printf("\n");
usleep(300000);
}

///PILA PARA AGREGAR PRODUCTO
void pila_para_agregar()
{
    Pila agregar;
    inicpila(&agregar);

    apilar(&agregar, '.');
    apilar(&agregar, '.');
    apilar(&agregar, '.');
    apilar(&agregar, 'o');
    apilar(&agregar, 'd');
    apilar(&agregar, 'n');
    apilar(&agregar, 'a');
    apilar(&agregar, 'g');
    apilar(&agregar, 'e');
    apilar(&agregar, 'r');
    apilar(&agregar, 'g');
    apilar(&agregar, 'A');

while(!pilavacia(&agregar))
{
    char elemento = tope(&agregar);
    printf("%c", elemento);
    desapilar(&agregar);
    usleep(100000);
}
printf("\n");
usleep(300000);
}

///MENU PRINCIPAL
void menu_principal()
{
    printf("\n");
    printf("****************************************\n");
    printf("*            MENU PRINCIPAL            *\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*   1. Crear usuario                   *\n");
    printf("*   2. Ingresar al Sistema             *\n");
    printf("*   3. Salir                           *\n");
    printf("*                                      *\n");
    printf("****************************************\n");
    printf("\n");

}

///REGISTRAR UN USUARIO
void registrar_usuario()
{
    nuevo_usuario usuario;
    int validacion;
    int valido;
    int validacion_genero;

    printf("\n------------------------------\n");
    printf("   Registro de Usuario\n");
    printf("------------------------------\n");

    printf("\nNombre de Usuario: ");
    fflush(stdin);
    scanf(" %[^\n]", usuario.nombre_usuario);

    printf("\nClave: ");
    fflush(stdin);
    scanf(" %[^\n]", usuario.clave);

    do{
    printf("\nNombre: ");
    fflush(stdin);
    scanf(" %[^\n]", usuario.nombre);
    validacion=validarNombre(usuario.nombre);
    }while(validacion==0);

    do
    {
        printf("\nApellido: ");
        fflush(stdin);
        scanf(" %[^\n]", usuario.apellido);
        validacion=validarNombre(usuario.apellido);

    }while(validacion==0);

    do
    {
        printf("\nDocumento: ");
        fflush(stdin);
        scanf("%s", usuario.documento);
        valido=validar_numeros(usuario.documento);

    }while(valido==false);

    do
    {
        printf("\nEdad: ");
        fflush(stdin);
        scanf("%s", usuario.edad);
        valido=validar_numeros(usuario.edad);

    }while(valido==false);

    printf("\nCorreo Electronico: ");
    fflush(stdin);
    gets(usuario.mail);

    do {
        printf("\nGenero (m/f): ");
        fflush(stdin);
        scanf(" %[^\n]", usuario.genero);
        validacion_genero = validarGenero(usuario.genero);
    } while (validacion_genero == 0);

    FILE *archi = fopen("usuarios.bin", "ab");
    if (archi == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(&usuario, sizeof(nuevo_usuario), 1, archi);

    fclose(archi);
    system("cls");
    pila_para_procesar();
    system("cls");

    printf("\n--------------------------------------\n");
    printf("   Usuario registrado exitosamente.\n");
    printf("--------------------------------------\n");
}

///INICIAR SESION
int iniciar_sesion(Pila *dada)
{
    char nombre_usuario[max_Nusuario];
    char clave[max_Nclave];
    int flag=0;

    printf("\n------------------------------\n");
    printf("       Inicio de Sesion\n");
    printf("------------------------------\n");

    printf("\nNombre de usuario: ");
    fflush(stdin);
    scanf(" %[^\n]", nombre_usuario);
    printf("\nClave: ");
    fflush(stdin);
    scanf(" %[^\n]", clave);

    if(verificar_info_usuario(nombre_usuario, clave))
    {
        system("cls");
        pila_para_cargar();
        system("cls");
        printf("\n------------------------------\n");
        printf("Bienvenido, %s!\n", nombre_usuario);
        printf("------------------------------\n");
        flag=0;
    }else
        {
            system("cls");
            printf("\n------------------------------\n");
            printf("   Credenciales invalidas.\n");
            printf("   Intentalo de nuevo.\n");
            printf("------------------------------\n");
            menu_principal();
            flag=1;
        }
    return flag;
}

///SEGUNDO SWITCH
void switch_de_opciones()
{
    int eleccion2;
    int j = 0;
    char volver_al_menu;

    do {
        menu_de_opciones();
        while (!j) {
            do {
                printf("\nSelecciona una opcion: ");

                if (scanf("%d", &eleccion2) == 1) {
                    j = 1;
                    switch (eleccion2) {
                        case 1:
                            system("cls");
                            agregar_producto();
                            printf("\nPresione cualquier tecla para volver al menu de opciones: ");
                            fflush(stdin);
                            scanf("%c", &volver_al_menu);
                            system("cls");
                            menu_de_opciones();
                            break;
                        case 2:
                            system("cls");
                            eliminar_producto();
                            printf("\nPresione cualquier tecla para volver al menu de opciones: ");
                            fflush(stdin);
                            scanf("%c", &volver_al_menu);
                            system("cls");
                            menu_de_opciones();
                            break;
                        case 3:
                            system("cls");
                            mostrar_producto();
                            printf("\nPresione cualquier tecla para volver al menu de opciones: ");
                            fflush(stdin);
                            scanf("%c", &volver_al_menu);
                            system("cls");
                            menu_de_opciones();
                            break;
                        case 4:
                            system("cls");
                            buscar_producto();
                            printf("\nPresione cualquier tecla para volver al menu de opciones: ");
                            fflush(stdin);
                            scanf("%c", &volver_al_menu);
                            system("cls");
                            menu_de_opciones();
                            break;
                        case 5:
                            system("cls");
                            mostrar_usuario();
                            printf("\nPresione cualquier tecla para volver al menu de opciones: ");
                            fflush(stdin);
                            scanf("%c", &volver_al_menu);
                            system("cls");
                            menu_de_opciones();
                            break;
                        case 6:
                            system("cls");
                            modificar_usuario();
                            printf("\nPresione cualquier tecla para volver al menu de opciones: ");
                            fflush(stdin);
                            scanf("%c", &volver_al_menu);
                            system("cls");
                            menu_de_opciones();
                            break;
                        case 7:
                            system("cls");
                            printf("¡Hasta luego!\n");
                            menu_principal();
                            return;
                        default:
                            system("cls");
                            printf("Opcion invalida. Intentalo de nuevo.\n");
                            menu_de_opciones();
                            break;
                    }
                } else {
                    system("cls");
                    printf("\nError: solo se puede ingresar un valor numerico\n");
                    fflush(stdin);
                    menu_de_opciones();
                }
            } while (eleccion2 < 1 || eleccion2 > 7);
            j=0;
        }
        printf("\n");
    } while (1);
}

///MENU DE OPCIONES
void menu_de_opciones()
{
printf("\n******************************************\n");
printf("*            Ferreteria S.P.I            *\n");
printf("*            MENU DEL SISTEMA            *\n");
printf("******************************************\n");
printf("*                                        *\n");
printf("*   1. Agregar Producto/s                *\n");
printf("*   2. Eliminar Producto/s               *\n");
printf("*   3. Mostrar Catalogo                  *\n");
printf("*   4. Busqueda de Productos             *\n");
printf("*   5. Informacion del Usuario           *\n");
printf("*   6. Modificar Usuario                 *\n");
printf("*   7. Volver al Menu Principal          *\n");
printf("*                                        *\n");
printf("******************************************\n");
printf("\n");
}

///OPCION 1
void agregar_producto()
{
    char lote[max_Nlote];
    char nombre_producto[max_Nproducto];
    float precio=0;
    int cantidad=0;

    printf("\n------------------------\n");
    printf("    Agregar Producto\n");
    printf("------------------------\n");

    printf("\nNombre: ");
    fflush(stdin);
    scanf(" %[^\n]", nombre_producto);

    printf("\nLote: ");
    fflush(stdin);
    scanf(" %[^\n]", lote);

     if (verificar_lote_existente(lote)) {
        printf("\nEl lote ya esta creado. No se puede agregar el producto.\n");
        return;
    }

    printf("\nPrecio por Unidad: $");
    fflush(stdin);
    if(scanf("%f", &precio)==1)
    {
    printf("\nCantidad: ");
    fflush(stdin);
    if(scanf("%d", &cantidad)==1)
    {
    if (!validarDato(nombre_producto)) {
        printf("\n");
        pila_para_agregar();
        system("cls");
        printf("\n¡ERROR! El nombre del producto debe contener solo letras.\n");
        usleep(300000);
        return;
    }

    nuevo_producto producto;
    strncpy(producto.nombre_producto, nombre_producto, max_Nproducto);
    strncpy(producto.lote, lote, max_Nlote);
    producto.cantidad = cantidad;
    producto.precio = precio;

    FILE *archi = fopen("productos.bin", "ab");
    fwrite(&producto, sizeof(nuevo_producto), 1, archi);

    fclose(archi);
    printf("\n");
    system("cls");
    pila_para_procesar();
    system("cls");
    printf("------------------------------------------\n");
    printf("Producto agregado exitosamente.\n");
    printf("------------------------------------------\n");
    }else
    {
            system("cls");
            printf("\nError: solo se puede ingresar un valor numerico\n");
            fflush(stdin);
            return;
    }
    }else
    {
            system("cls");
            printf("\nError: solo se puede ingresar un valor numerico\n");
            fflush(stdin);
            return;
    }
}

///OPCION 2
void eliminar_producto()
{
    char lote[max_Nlote];
    int cantidad_eliminar;
    printf("\n------------------------\n");
    printf("    Eliminar Producto\n");
    printf("------------------------\n");
    printf("\nLote del producto a eliminar: ");
    fflush(stdin);
    scanf("%s", lote);

    printf("\nIngresa la cantidad a eliminar: ");
    fflush(stdin);
    if(scanf("%d", &cantidad_eliminar)==1)
    {
    FILE *archi = fopen("productos.bin", "r+b");
    if (archi == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    nuevo_producto producto;

    FILE *tempArchivo = fopen("temp.bin", "wb");
    if (tempArchivo == NULL)
    {
        printf("Error al abrir el archivo temporal.\n");
        fclose(archi);
        return;
    }

    int encontrado = 0;
                system("cls");
            pila_para_procesar();
            system("cls");
    while (fread(&producto, sizeof(nuevo_producto), 1, archi))
    {
        if (strcmp(producto.lote, lote) == 0)
        {
            encontrado = 1;
            if(producto.cantidad > cantidad_eliminar)
            {
                producto.cantidad -= cantidad_eliminar;
                fwrite(&producto, sizeof(nuevo_producto), 1, tempArchivo);
            }else
                {
                    printf("\nSe eliminaron todas las cantidades del producto, ya que ingresaste un numero igual/mayor a la cantidad del mismo.\n");
                    sleep(2);
                    system("cls");
                }
                    } else {
            fwrite(&producto, sizeof(nuevo_producto), 1, tempArchivo);
        }

    }
        fclose(archi);
        fclose(tempArchivo);

        if(encontrado)
        {
            remove("productos.bin");
            rename("temp.bin", "productos.bin");
            printf("------------------------------------------\n");
            printf("Producto eliminado exitosamente.\n");
            printf("------------------------------------------\n");
        }

    else
    {
        remove("temp.bin");
        system("cls");
        printf("No se encontro ningun producto con el numero de lote especificado.\n");
    }
    }else
        {
            system("cls");
            printf("\nError: solo se puede ingresar un valor numerico\n\n");
            fflush(stdin);
            return;
        }


}

///OPCION 3
void mostrar_producto()
{
    FILE *archi = fopen("productos.bin", "rb");

    if (archi == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    nuevo_producto producto;
    nuevo_producto productos[100];
    int num_productos = 0;

    while (fread(&producto, sizeof(nuevo_producto), 1, archi)) {
        productos[num_productos++] = producto;
    }

    for (int i = 0; i < num_productos - 1; i++) {
        int minimo = i;
        for (int j = i + 1; j < num_productos; j++) {
            if (strcmp(productos[j].nombre_producto, productos[minimo].nombre_producto) < 0) {
                minimo = j;
            }
        }
        nuevo_producto temp = productos[minimo];
        productos[minimo] = productos[i];
        productos[i] = temp;
    }

    printf("** Lista de Productos **\n");
    for (int i = 0; i < num_productos; i++) {
        printf("------------------------------------------\n");
        printf("Nombre: %s\n", productos[i].nombre_producto);
        printf("Lote: %s\n", productos[i].lote);
        printf("Precio: %.2f\n", productos[i].precio);
        printf("Cantidad: %d\n", productos[i].cantidad);
        printf("------------------------------------------\n");
    }

    fclose(archi);
}

///OPCION 4
void buscar_producto()
{
    char lote[max_Nlote];
    system("cls");

    printf("\n------------------------\n");
    printf("    Buscar Producto\n");
    printf("------------------------\n");

    printf("\nIngresa el numero de lote del producto que deseas buscar: ");
    fflush(stdin);
    scanf("%s", lote);

    FILE *archi = fopen("productos.bin", "rb");
    if (archi == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    nuevo_producto producto;
    int encontrado = 0;

    while (fread(&producto, sizeof(nuevo_producto), 1, archi))
    {
        if (strcmp(producto.lote, lote) == 0)
        {
            encontrado = 1;
            system("cls");
            pila_para_cargar();
            system("cls");
            printf("\n** Producto encontrado **\n");

            printf("------------------------------------------\n");
            printf("Nombre: %s\n", producto.nombre_producto);
            printf("Lote: %s\n", producto.lote);
            printf("Precio por Unidad: $%.2f\n", producto.precio);
            printf("Cantidad: %d\n", producto.cantidad);
            printf("------------------------------------------\n");
            break;
        }
    }

    fclose(archi);

    if (!encontrado)
    {
        printf("No se encontro ningun producto con el numero de lote especificado.\n");
    }
}

///OPCION 5
void mostrar_usuario()
{
    char nombre_usuario[max_Nusuario];
    char clave[max_Nclave];
    int flag=0;

    printf("\n-----------------------------------\n");
    printf("       Informacion del usuario\n");
    printf("-----------------------------------\n");
    printf("\nNombre de usuario: ");
    fflush(stdin);
    scanf(" %[^\n]", nombre_usuario);
    printf("\nClave: ");
    fflush(stdin);
    scanf(" %[^\n]", clave);

    system("cls");
    pila_para_procesar();
    system("cls");

    if(verificar_info_usuario(nombre_usuario, clave))
    {

        printf("** Informacion del usuario **\n");

        FILE *archi=fopen("usuarios.bin", "rb");
        if(archi==NULL)
        {
            printf("Error al abrir el archivo.\n");
            return;
        }

        nuevo_usuario usuario;
        while(fread(&usuario, sizeof(nuevo_usuario), 1, archi))
        {
            if(strcmp(usuario.nombre_usuario, nombre_usuario) == 0 && strcmp(usuario.clave, clave) == 0)
            {
                printf("-----------------------------------\n");
                printf("Usuario: %s\n", usuario.nombre_usuario);
                printf("Nombre y Apellido: %s ", usuario.nombre);
                printf("%s\n", usuario.apellido);
                printf("Documento: %s\n", usuario.documento);
                printf("Edad: %s\n", usuario.edad);
                printf("Correo Electronico: %s\n", usuario.mail);
                printf("Genero: %s\n", usuario.genero);
                printf("-----------------------------------\n");
                flag=1;
                break;
            }
        }

        fclose(archi);

        if (flag == 0)
        {
            system("cls");
            printf("No se encontró ningún usuario con las credenciales especificadas.\n");
        }
    }
    else
    {
        system("cls");
        printf("Credenciales Invalidas. Intentalo de nuevo.\n");
    }
}

///OPCION 6:
void modificar_usuario()
{
    char nombre_usuario[max_Nusuario];
    char clave[max_Nclave];
    int flag = 0;
    int validacion;
    int valido;
    int validacion_genero;

    printf("\n-----------------------------------\n");
    printf("       Informacion del usuario\n");
    printf("-----------------------------------\n");
    printf("\nNombre de usuario: ");
    fflush(stdin);
    scanf(" %[^\n]", nombre_usuario);
    printf("\nClave: ");
    fflush(stdin);
    scanf(" %[^\n]", clave);

    system("cls");
    pila_para_procesar();
    system("cls");

    if (verificar_info_usuario(nombre_usuario, clave))
    {
        system("cls");
        printf("** Informacion actual **\n");
        FILE *archi = fopen("usuarios.bin", "r+b");
        if (archi == NULL)
        {
            printf("Error al abrir el archivo.\n");
            return;
        }

        nuevo_usuario usuario;
        while (fread(&usuario, sizeof(nuevo_usuario), 1, archi))
        {
            if (strcmp(usuario.nombre_usuario, nombre_usuario) == 0 && strcmp(usuario.clave, clave) == 0)
            {
                printf("-----------------------------------\n");
                printf("Usuario: %s\n", usuario.nombre_usuario);
                printf("Nombre y Apellido: %s ", usuario.nombre);
                printf("%s\n", usuario.apellido);
                printf("Documento: %s\n", usuario.documento);
                printf("Edad: %s\n", usuario.edad);
                printf("Correo Electronico: %s\n", usuario.mail);
                printf("Genero: %s\n", usuario.genero);
                printf("-----------------------------------\n");

                printf("\n** Introduce la nueva informacion: **\n");
                do{
                printf("\nNombre: ");
                fflush(stdin);
                gets(usuario.nombre);
                validacion=validarNombre(usuario.nombre);
                }while(validacion==0);

                do{
                printf("\nApellido: ");
                fflush(stdin);
                gets(usuario.apellido);
                validacion=validarNombre(usuario.apellido);
                }while(validacion==0);

                do{
                printf("\nDocumento: ");
                fflush(stdin);
                scanf("%s", usuario.documento);
                valido=validar_numeros(usuario.documento);
                }while(valido==false);

                do{
                printf("\nEdad: ");
                fflush(stdin);
                scanf("%s", usuario.edad);
                valido=validar_numeros(usuario.edad);
                }while(valido==false);

                printf("\nCorreo Electronico: ");
                fflush(stdin);
                gets(usuario.mail);

                do {
                printf("\nGenero (m/f): ");
                fflush(stdin);
                scanf(" %[^\n]", usuario.genero);
                validacion_genero = validarGenero(usuario.genero);
                } while (validacion_genero == 0);

                fseek(archi, -sizeof(nuevo_usuario), SEEK_CUR);
                fwrite(&usuario, sizeof(nuevo_usuario), 1, archi);

                system("cls");
                printf("----------------------------------------------------\n");
                printf("Informacion del usuario modificada exitosamente.\n");
                printf("----------------------------------------------------\n");
                flag = 1;
                break;
            }
        }

        fclose(archi);

        if (flag == 0)
        {
            printf("\nNo se encontro ningun usuario con las credenciales especificadas.\n");
        }
    }
    else
    {
        system("cls");
        printf("\nCredenciales Invalidas. Intentalo de nuevo.\n");
    }
}
