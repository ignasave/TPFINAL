#include <stdio.h>
#include <stdlib.h>
#include "consumos.h"
#include "clientes.h"

int main()
{
    menuPrincipal();
    return 0;
}


//////////// FUNCIONES DE VISUALIZACION ///////////////

/**************************************************************************
* \brief Imprime en pantalla las opciones del menu principal
**************************************************************************/
void mostrarMenuPrincipal(){
    printf("\n SISTEMA DE CONTROL \n\n");
    printf("\n 1) Clientes ");
    printf("\n 2) Consumos ");
    printf("\n\n\n (ESC) Salir ");
}

/**************************************************************************
* \brief Imprime en pantalla las opciones del menu de clientes
**************************************************************************/
void mostrarMenuClientes(){
    printf("\n CLIENTES \n\n");
    printf("\n 1) Agregar clientes ");
    printf("\n 2) Visualizar clientes ");
    printf("\n 3) Modificar un cliente ");
    printf("\n\n\n (ESC) Volver ");
}

/**************************************************************************
* \brief Imprime en pantalla las opciones del menu de consumos
**************************************************************************/
void mostrarMenuConsumos(){
    printf("\n CONSUMOS \n\n");
    printf("\n 1) Agregar consumos ");
    printf("\n 2) Agregar consumos Aleatorios");
    printf("\n 3) Visualizar consumos ");
    printf("\n 4) Modificar un consumo ");
    printf("\n\n\n (ESC) Volver ");
}


//////////// FUNCIONES DE CONTROL ///////////////

/**************************************************************************
* \brief Maneja el menu principal, redirije a submenus
**************************************************************************/
void menuPrincipal(){
    char opcion;
    do{
        system("cls");
        mostrarMenuPrincipal();
        opcion = getch();
        system("cls");
        switch(opcion){
            case 49:
                menuClientes();
                break;
            case 50:
                menuConsumos();
                break;
        }
    }while(opcion != ESC);
}

/**************************************************************************
* \brief Maneja el menu de consumos, llama las funciones principales de consumos
**************************************************************************/
void menuConsumos(){
    char opcion;
    do{
        system("cls");
        mostrarMenuConsumos();
        opcion = getch();
        system("cls");
        switch(opcion){
            case 49:
                cargarConsumosManual();
                break;
            case 50:
                cargarAleatorios();
                break;
            case 51:
                mostrarConsumos();
                break;
            case 52:
                controlarModificacionConsumo();
                break;
        }
    }while(opcion != ESC);
}

/**************************************************************************
* \brief Maneja el menu de clientes, llama las funciones principales de clientes
**************************************************************************/
void menuClientes(){
    char opcion;
    do{
        system("cls");
        mostrarMenuClientes();
        opcion = getch();
        system("cls");
        switch(opcion){
            case 49:
                cargarClientes();
                break;
            case 50:
                mostrarClientes();
                break;
            case 51:
                controlarModificacionCliente();
                break;
        }
    }while(opcion != ESC);
}
