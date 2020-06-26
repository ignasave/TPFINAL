#include "fechas.h"

int diasEnMes(int y, int m)
{
   const int dias[12] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
   int resultado;

   resultado = dias[m-1];

   if ( m == Febrero && esAnioBisciesto( y ) )
      resultado++;

   return resultado;
}


int esFechaValida( int y, int m, int d ){
   if ( d < 0 || d >= diasEnMes( y, m ) )
      return 0;

   return 1;
}

int fechaRandom( int *y, int *m, int *d ){
   y = ANIO_HOY;
   m = Enero + rand() % (Diciembre);
   d = 1 + rand() % (diasEnMes(y,m));
}
