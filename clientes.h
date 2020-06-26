#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>

#define AR_CLIENTES "clientes.dat"
#define ESC 27
#define MAX_CLIENTES 9999
#define MAX_NOMBRE 30
#define MAX_MAIL 70
#define MAX_DOM 45

typedef struct{
    int id;   /// campo unico y autoincremental
    int nroCliente;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_NOMBRE];
    int dni;
    char email[MAX_MAIL];
    char domicilio[MAX_DOM];
    int movil;
    int baja; /// 0 - 1
} stCliente;

void cargarClientes();
void agregarUnCliente(stCliente c);
stCliente cargaManualUnCliente();
void arregloToArchivo(stCliente a[], int v);
int obtenerInt();
int archivoToArreglo(stCliente a[]);

void mostrarClientes();
void mostrarFiltros();
void mostrarModificacion(stCliente c);
void mostrarListaClientes(stCliente c[], int v);
void mostrarUnCliente(stCliente c);

void controlarModificacionCliente();
void formularioModificacionCliente(stCliente c);
void modificarCliente(stCliente c);

int obtenerNroClientePorID(int id);
int obtenerIdClientePorNro(int nro);
int ultimoIdCliente();
int existeNroClienteExcl(int nro, int id);
int existeDNIClienteExcl(int dni, int id);
int existeDNICliente(int dni);
int existeNroCliente(int nro);
int posPorIdCliente(int id);
int validaEmail(char email[]);

int filtrarNro(stCliente a[]);
int filtrarNombre(stCliente a[]);
int filtrarApellido(stCliente a[]);
int filtrarDNI(stCliente a[]);
int filtrarEmail(stCliente a[]);
int filtrarDomicilio(stCliente a[]);
int filtrarMovil(stCliente a[]);
int filtrarBaja(stCliente a[]);
int controlarFiltro(stCliente a[]);

#endif // CLIENTES_H_INCLUDED
