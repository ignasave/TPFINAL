#ifndef FECHAS_H_INCLUDED
#define FECHAS_H_INCLUDED

#include <stdio.h>
#include <dos.h>
#include <conio.h>

#define esAnioBisciesto(y)  ((((y)%400)==0)||((((y)%4)==0)&&(((y)%100)!=0)))
#define DIA_HOY 26
#define MES_HOY 6
#define ANIO_HOY 2020

enum bool
{
    false = 0,
    true = 1
};

enum Mes
{
   Enero = 1,
   Febrero = 2,
   Marzo = 3,
   Abril = 4,
   Mayo = 5,
   Junio = 6,
   Julio = 7,
   Agosto = 8,
   Septiembre = 9,
   Octubre = 10,
   Noviembre = 11,
   Diciembre = 12
};

int diasEnMes(int y, int m);
int esFechaValida( int y, int m, int d );
int fechaRandom( int *y, int *m, int *d );

#endif // FECHAS_H_INCLUDED
