#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <locale.h>
#include "clientes.h"
#include "fechas.h"

#define MAX_CONSUMOS 9999
#define MAX_DATOS 9999
#define MAX_CARGAS 1000
#define AR_CONSUMOS "consumos.dat"

typedef struct{
    int id;   /// campo unico y autoincremental
    int idCliente;
    int anio;
    int mes;
    int dia;
    int datosConsumidos;
    int baja; /// 0 - 1
} stConsumo;

void mostrarConsumos();
void mostrarListaConsumos(stConsumo c[], int v);
void mostrarFiltrosConsumos();
void mostrarUnConsumo(stConsumo c);
void mostrarModificacionConsumo(stConsumo c);

stConsumo consumoRandom();
void cargarAleatorios();

void cargarConsumosManual();
void sumarONuevo(stConsumo c);
void arregloToArchivoConsumos(stConsumo a[], int  v);
void controlarCargaManual();
stConsumo cargaManualUnConsumo();
void agregarUnConsumo(stConsumo c);
void agregarDatos(int id, int datos);
int archivoToArregloConsumos(stConsumo a[]);

void controlarModificacionConsumo();
void formularioModificacionConsumo(stConsumo c);
void modificarConsumo(stConsumo c);

int idConsumoPorDatos(int cliente, int y, int m, int d);
int ultimoIdConsumos();
int buscaPosConsumos(int id);

int filtrarNroConsumo(stConsumo a[]);
int filtrarAnio(stConsumo a[]);
int filtrarMes(stConsumo a[]);
int filtrarDia(stConsumo a[]);
int filtrarFecha(stConsumo a[]);
int filtrarBajaConsumo(stConsumo a[]);
int filtrarRangoDatos(stConsumo a[]);
int controlarFiltroConsumos(stConsumo a[]);


#endif // CONSUMOS_H_INCLUDED
