#include "consumos.h"

//////////// FUNCIONES DE VISUALIZACION ///////////////

/**************************************************************************
* \brief Controla la seccion para mostrar consumos, filtrarlos y llamada a modificar
**************************************************************************/
void mostrarConsumos() {
    stConsumo a[MAX_CONSUMOS];
    int v = 0;
    char opcion;
    v = archivoToArregloConsumos(a);
    do{
        printf("(1) Filtrar    |    (2) Todos    |  (3) Modificar  | (ESC) salir\n\n");
        mostrarListaConsumos(a, v);
        fflush(stdin);
        opcion = getch();
        switch (opcion)
        {
        case 49:
            v = controlarFiltroConsumos(a);
            break;
        case 50:
            v = archivoToArregloConsumos(a);
            break;
        case 51:
            controlarModificacionConsumo();
            break;
        }
    }while(opcion != ESC);
}

/**************************************************************************
* \brief Muestra una lista de consumos
* \param stConsumo Arreglo de consumos
* \param int v Validos del arreglo de consumos
**************************************************************************/
void mostrarListaConsumos(stConsumo c[], int v){
    for(int i = 0; i < v ; i++){
        mostrarUnConsumo(c[i]);
    }
}

/**************************************************************************
* \brief Muestra opciones de filtros por pantalla
**************************************************************************/
void mostrarFiltrosConsumos(){
    printf("\n ----------- FILTRAR POR ---------------");
    printf("\n ----------------------------------------");
    printf("\n 1) Nro Cliente .........: ");
    printf("\n 2) Anio ................: ");
    printf("\n 3) Mes .................: ");
    printf("\n 4) Dia .................: ");
    printf("\n 5) Fecha Completa ......: ");
    printf("\n 6) Baja ................: ");
    printf("\n 7) Rango de Datos en MB.: ");
    printf("\n\n\n Cancelar (ESC)     ");

}

/**************************************************************************
* \brief Muestra un consumo por pantalla
* \param stConsumo Consumo a mostrar
**************************************************************************/
void mostrarUnConsumo(stConsumo c){
    //Esta funcion deberia trabajar sobre un arreglo, por que asi es ineficiente, es algo a laburar luego la optimizacion.
    int nroCliente = obtenerNroClientePorID(c.idCliente);
    printf("\n ----------------------------------------");
    //printf("\n ID consumo .............:  %d", c.id);
    //printf("\n ID Cliente .............:  %d", c.idCliente);
    printf("\n Nro Cliente .............: %d", nroCliente);
    printf("\n Fecha (dia - mes - anio) : %d-%d-%d ", c.dia, c.mes, c.anio);
    printf("\n Datos comsumidos ........: %d MB", c.datosConsumidos);
    printf("\n Baja ....................: %s", (c.baja) ? "SI" : "NO" );

}

/**************************************************************************
* \brief Muestra las opciones para modificar un consumo
* \param stConsumo Consumo a modificar
**************************************************************************/
void mostrarModificacionConsumo(stConsumo c){

    int nroCliente = obtenerNroClientePorID(c.idCliente);
    printf("\n ----------------------------------------");
    //printf("\n -) ID consumo .............:  %d", c.id);
    //printf("\n -) ID Cliente .............:  %d", c.idCliente);
    printf("\n 1) Nro Cliente .............: %d", nroCliente);
    printf("\n 2) Anio ....................: %d", c.anio);
    printf("\n 3) Mes .....................: %d", c.mes);
    printf("\n 4) Dia .....................: %d", c.dia);
    printf("\n 5) Datos comsumidos ........: %d MB", c.datosConsumidos);
    printf("\n 6) Baja ....................: %s", (c.baja) ? "SI" : "NO" );
    printf("\n\n\n Cancelar (ESC)   |    Confirmar (c)");

}


///////////////// FUNCIONES DE CARGA AUTOMATICA /////////////////


/**************************************************************************
* \brief Crea un consumo con datos aleatorios
* \return stConsumo Consumo aleatorio
**************************************************************************/
stConsumo consumoRandom(){
    stConsumo c;
    c.idCliente = 1 + rand() % ultimoIdCliente();
    fechaRandom(&c.anio, &c.mes, &c.dia);
    c.datosConsumidos = rand() % MAX_DATOS;
    c.baja = 0;
}

/**************************************************************************
* \brief Carga al archivo de consumos un numero definido de consumos aleatorios
**************************************************************************/
void cargarAleatorios(){
    stConsumo c ;
    for(int i = 0; i < MAX_CARGAS; i++){
        c = consumoRandom();
        sumarONuevo(c);
    }

}


///////////////// FUNCIONES DE CARGA /////////////////


/**************************************************************************
* \brief Controla la carga de consumos por carga manual
**************************************************************************/
void cargarConsumosManual(){
    char opcion;
    do{
        system("cls");
        controlarCargaManual();
        system("cls");
        printf("\n\n\n (ESC) Terminar");
        opcion = getch();
    }while(opcion != ESC);
}

/**************************************************************************
* \brief Funcion que determina si el consumo es nuevo o debe sumarse a uno existente
* \param stConsumo
**************************************************************************/
void sumarONuevo(stConsumo c){
    int cpd = idConsumoPorDatos(c.idCliente, c.anio, c.mes, c.dia);
    if(cpd != -1){
        agregarDatos(cpd, c.datosConsumidos);
    } else {
        c.id = ultimoIdConsumos() + 1;
        agregarUnConsumo(c);
    }
}

/**************************************************************************
* \brief Funcion que carga un arreglo de consumos al archivo de consumos
* \param stConsumo Arreglo de consumos
* \param int Validos del arreglo de consumos
**************************************************************************/
void arregloToArchivoConsumos(stConsumo a[], int  v) {
    FILE *pArchConsumo = fopen(AR_CONSUMOS, "ab");
    if(pArchConsumo) {
        fwrite(a, sizeof(stConsumo), v, pArchConsumo);
        fclose(pArchConsumo);
    }
}

/**************************************************************************
* \brief Funcion que carga un consumo completo al archivo
**************************************************************************/
void controlarCargaManual(){
    stConsumo c = cargaManualUnConsumo();
    sumarONuevo(c);
}

/**************************************************************************
* \brief Funcion que ingresa un consumo de forma manual y lo retorna
* \return stConsumo El consumo ingresado
**************************************************************************/
stConsumo cargaManualUnConsumo() {
    stConsumo c;
    int nroCliente = -1;
    do{
        printf("\n Ingrese el nro de Cliente......: ");
        scanf("%d", &nroCliente);
    }while(nroCliente < 0 || !existeNroCliente(nroCliente));
    do{
        printf("\n Ingrese el Anio................: ");
        scanf("%d", &c.anio);
    }while(c.anio < 0 || c.anio > 2999);
    do{
        printf("\n Ingrese el Mes.................: ");
        scanf("%d", &c.mes);
    }while(c.mes < Enero || c.mes > Diciembre);
    do{
        printf("\n Ingrese el Dia.................: ");
        scanf("%d", &c.dia);
    }while(!esFechaValida(c.anio, c.mes, c.dia));


    printf("\n Ingrese los Datos Consumidos...: ");
    scanf("%d", &c.datosConsumidos);

    c.idCliente = obtenerIdClientePorNro(nroCliente);
    c.baja = 0;
    return c;
}

/**************************************************************************
* \brief Agrega un consumo al archivo
* \param stConsumo Consumo a agregar
**************************************************************************/
void agregarUnConsumo(stConsumo c){
    FILE *pArchConsumos = fopen(AR_CONSUMOS, "ab");
    if(pArchConsumos){
        fwrite(&c,sizeof(stConsumo),1,pArchConsumos);
        fclose(pArchConsumos);
    }
}

/**************************************************************************
* \brief Agrega datos consumidos a un consumo existente
* \param int Id del consumo al que agregar
* \param int datos cantidad de datos consumidos a agregar
**************************************************************************/
void agregarDatos(int id, int datos){
    stConsumo c;
    int pos = 0;
    pos = buscaPosConsumos(id);
    FILE *pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        fseek(pArchConsumos, sizeof(stConsumo)*pos, SEEK_SET);
        fread(&c, sizeof(stConsumo), 1, pArchConsumos);
        c.datosConsumidos += datos;
        modificarConsumo(c);
        fclose(pArchConsumos);
    }
}

/**************************************************************************
* \brief Funcion que pasa todos los consumos del archivo a un arreglo
* \param stConsumo Arreglo de consumos
* \return int Validos del arreglo
**************************************************************************/
int archivoToArregloConsumos(stConsumo a[]){
    int v = 0;
    FILE *pArchConsumos  = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while(fread(&a[v],sizeof(stConsumo),1,pArchConsumos) > 0){
           v++;
        }
        fclose(pArchConsumos);
    }
    return v;
}


///////////////// FUNCIONES DE MODIFICACION /////////////////


/**************************************************************************
* \brief Funcion que controla la modificacion de un consumo
* \param stConsumo consumo a modificar
**************************************************************************/
void controlarModificacionConsumo(){
    stConsumo a[MAX_CONSUMOS];
    stConsumo c;
    int v, encontrado = 0;
    v = archivoToArregloConsumos(a);
    int nroCliente = -1, dia, mes, anio;
    printf("\n Ingrese el Nro Cliente a modificar : ");
    scanf("%d", &nroCliente);
    printf("\n Ingrese anio: --/--/----");
    scanf("%d", &anio);
    printf("\n Ingrese mes : --/--/%d", anio);
    scanf("%d", &mes);
    printf("\n Ingrese dia : --/%d/%d", mes, anio);
    scanf("%d", &dia);
    int id = obtenerIdClientePorNro(nroCliente);
    for(int i = 0; i < v; i++){
        if(a[i].idCliente == id
        && a[i].anio == anio
        && a[i].mes == mes
        && a[i].dia == dia){
            c = a[i];
            encontrado = 1;
        }
    }
    if(encontrado){
        formularioModificacionConsumo(c);
    } else {
        printf("\n El consumo ingresado no existe en el registro");
        system("pause");
    }

}

/**************************************************************************
* \brief Obtiene y valida los datos para la modificacion de un consumo
* \param stConsumo consumo a modificar
**************************************************************************/
void formularioModificacionConsumo(stConsumo c){
    stConsumo cm = c;
    char opcion;
    do{
        mostrarModificacionConsumo(cm);
        fflush(stdin);
        opcion = getch();
        switch(opcion){
            case 49:{
                int valor;
                valor = obtenerInt();
                if(existeNroCliente(valor)){
                    int idCliente = obtenerIdClientePorNro(valor);
                    cm.idCliente = idCliente;
                } else {
                    printf("\n\n NO existe un cliente con ese Nro Cliente! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            case 50:{
                int valor;
                valor = obtenerInt();
                if(valor > 0 && valor < 2999){
                    cm.anio = valor;
                } else {
                    printf("\n\n A�o incorrecto! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            case 51:{
                int valor;
                valor = obtenerInt();
                if(valor > 0 && valor < 13){
                    cm.mes = valor;
                } else {
                    printf("\n\n Mes incorrecto! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            case 52:{
                int valor;
                valor = obtenerInt();
                if(esFechaValida(c.anio, c.mes, valor)){
                    cm.dia = valor;
                } else {
                    printf("\n\n Dia incorrecto! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            case 53:{
                int valor;
                valor = obtenerInt();
                cm.datosConsumidos = valor;
                break;
            }
            case 54:{
                int valor;
                valor = obtenerInt();
                if(valor == 0 || valor == 1) {
                    cm.baja = valor;
                } else {
                    printf("\n\n Valor incorrecto, solo: ( 0 / 1 )! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            }
        }while(opcion != ESC && opcion != 'c');
        if(opcion == 'c'){
            //volver a checkear fecha por si modifico mes/a�o despues del dia
            if(esFechaValida(cm.anio, cm.mes, cm.dia)){
                //verifico si no existe o si es el propio.
                int idConsumo = idConsumoPorDatos(cm.idCliente, cm.anio, cm.mes, cm.dia);
                if( idConsumo == -1 || idConsumo == cm.id) {
                    modificarConsumo(cm);
                } else {
                    printf("\n\n Error, ese consumo ya existe! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
            } else {
                printf("\n\n Error, fecha erronea! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                system("pause");
            }
        }
    }

/**************************************************************************
* \brief Modifica un consumo en el archivo
* \param stConsumo consumo a modificar
**************************************************************************/
void modificarConsumo(stConsumo c) {
    int pos = 0;
    pos = buscaPosConsumos(c.id);
    FILE *pArchConsumos = fopen(AR_CONSUMOS, "r+b");
    if(pArchConsumos){
        fseek(pArchConsumos, sizeof(stConsumo)*pos, SEEK_SET);
        fwrite(&c, sizeof(stConsumo), 1, pArchConsumos);
        fclose(pArchConsumos);
    }
}


///////////////// FUNCIONES DE BUSQUEDA /////////////////

/*********************************************************************//**
*
* \brief Busca la posicion en el archivo de un determinado consumo por su id
* \param int id
* \return int posicion
*
**************************************************************************/
int buscaPosConsumos(int id){
    int pos = -1;
    stConsumo c;
    FILE *pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while(pos==-1 && fread(&c, sizeof(stConsumo), 1, pArchConsumos) > 0){
            if(c.id == id){
                pos = ftell(pArchConsumos)/sizeof(stConsumo)-1;
            }
        }
        fclose(pArchConsumos);
    }

    return pos;
}

/**************************************************************************
*
* \brief Retorna el ultimo id cargado
* \return int -1 si no hay registros o el id del ultimo registro
*
**************************************************************************/
int ultimoIdConsumos() {
    stConsumo c;
    int id = -1;
    FILE *pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        fseek(pArchConsumos, sizeof(stConsumo)*(-1),SEEK_END);
        if(fread(&c,sizeof(stConsumo),1,pArchConsumos) > 0){
            id = c.id;
        }
        fclose(pArchConsumos);
    }
    return id;
}

/**************************************************************************
* \brief Funcion que obtiene el id de un consumo por idCliente y fecha
* \param int idCliente
* \param int anio
* \param int mes
* \param int dia
* \return int Id del consumo buscado
**************************************************************************/
int idConsumoPorDatos(int cliente, int y, int m, int d){
    stConsumo c;
    int id = -1;
    FILE *pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while(id == -1 && fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.idCliente == cliente
            && c.anio == y
            && c.mes == m
            && c.dia == d){
                id = c.id;
            }
        }
        fclose(pArchConsumos);
    }
    return id;
}


///////////////// FUNCIONES DE FILTROS /////////////////


/**************************************************************************
* \brief Funcion que obtiene un arreglo de consumos filtrados por Nro Cliente
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int filtrarNroConsumo(stConsumo a[]){
    stConsumo c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);
    int id = obtenerIdClientePorNro(valor);
    FILE * pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while (fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.idCliente == id){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchConsumos);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de consumos filtrados por anio
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int filtrarAnio(stConsumo a[]){
    stConsumo c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE * pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while (fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.anio == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchConsumos);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de consumos filtrados por mes
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int filtrarMes(stConsumo a[]){
    stConsumo c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE * pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while (fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.mes == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchConsumos);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de consumos filtrados por dia
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int filtrarDia(stConsumo a[]){
    stConsumo c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE * pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while (fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.dia == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchConsumos);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de consumos filtrados por fecha completa
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int filtrarFecha(stConsumo a[]){
    stConsumo c;
    int v = 0;
    int dia, mes, anio;

    printf("\n Ingrese a�o : --/--/----");
    scanf("%d", anio);
    printf("\n Ingrese mes : --/--/%d", anio);
    scanf("%d", mes);
    printf("\n Ingrese dia : --/%d/%d", dia);
    scanf("%d", dia);

    FILE * pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while (fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.anio == anio
            && c.mes == mes
            && c.dia == dia){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchConsumos);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de consumos filtrados por estado de consumo
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int filtrarBajaConsumo(stConsumo a[]){
    stConsumo c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE * pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while (fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.baja == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchConsumos);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de consumos filtrados por rango de datos consumidos
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int filtrarRangoDatos(stConsumo a[]){
    stConsumo c;
    int v = 0;
    int min, max;
    printf("Valor minimo: ");
    scanf("%d", &min);
    printf("Valor maximo: ");
    scanf("%d", &max);

    FILE * pArchConsumos = fopen(AR_CONSUMOS, "rb");
    if(pArchConsumos){
        while (fread(&c, sizeof(stConsumo),1,pArchConsumos) > 0){
            if(c.datosConsumidos >= min && c.datosConsumidos <= max ){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchConsumos);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que controla el filtro que se quiere aplicar
* \param stConsumo arreglo de consumos
* \return int validos del arreglo
**************************************************************************/
int controlarFiltroConsumos(stConsumo a[]){
    int v;
    char opcion;
    system("cls");
    mostrarFiltrosConsumos();
    opcion = getch();
    switch (opcion)
    {
    case 49:
        v = filtrarNroConsumo(a);
        break;
    case 50:
        v = filtrarAnio(a);
        break;
    case 51:
        v = filtrarMes(a);
        break;
    case 52:
        v = filtrarDia(a);
        break;
    case 53:
        v = filtrarFecha(a);
        break;
    case 54:
        v = filtrarBajaConsumo(a);
        break;
    case 55:
        v = filtrarRangoDatos(a);
        break;
    }
    return v;
}
