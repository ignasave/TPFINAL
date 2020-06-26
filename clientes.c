#include "clientes.h"

///////////////// FUNCIONES DE CARGA /////////////////


/**************************************************************************
* \brief Funcion que maneja la carga de clientes manuales
**************************************************************************/
void cargarClientes(){
    char opcion;
    do{
        system("cls");
        agregarUnCliente(cargaManualUnCliente());
        system("cls");
        printf("\n\n\n (ESC) Terminar");
        opcion = getch();
    }while(opcion != ESC);
}

/**************************************************************************
* \brief Funcion que agrega un cliente al archivo de clientes
* \param stCliente cliente a agregar
**************************************************************************/
void agregarUnCliente(stCliente c){
    FILE *pArchClientes = fopen(AR_CLIENTES, "ab");
    if(pArchClientes){
        fwrite(&c,sizeof(stCliente),1,pArchClientes);
        fclose(pArchClientes);
    }
}

/**************************************************************************
* \brief Funcion de formulario para un nuevo cliente validando los datos
* \return stCliente cliente cargado
**************************************************************************/
stCliente cargaManualUnCliente() {
    stCliente c;

    do{
        printf("\n Ingrese el nro de Cliente......: ");
        scanf("%d", &c.nroCliente);
    }while(c.nroCliente < 0 || existeNroCliente(c.nroCliente));
    do{
        printf("\n Ingrese el DNI.................: ");
        scanf("%d", &c.dni);
    }while(existeDNICliente(c.dni));
        printf(" Ingrese el Nombre................: ");
    fflush(stdin);
    gets(c.nombre);
        printf(" Ingrese el Apellido..............: ");
    fflush(stdin);
    gets(c.apellido);
    do{
        printf(" Ingrese el Email.................: ");
        fflush(stdin);
        gets(c.email);
    }while(!validaEmail(c.email));
        printf(" Ingrese el Domicilio.............: ");
    fflush(stdin);
    gets(c.domicilio);
        printf(" Ingrese el Numero de telefono....: ");
    scanf(" %d", &c.movil);

    c.id = ultimoIdCliente() + 1;
    c.baja = 0;

    return c;
}

/**************************************************************************
* \brief Funcion que pasa al archivo de clientes un arreglo de clientes
* \param stCliente arreglo de clientes a agregar
* \param int validos del arreglo
**************************************************************************/
void arregloToArchivo(stCliente a[], int v) {
    FILE *pArchClientes = fopen(AR_CLIENTES, "ab");
    if(pArchClientes) {
        fwrite(a, sizeof(stCliente), v, pArchClientes);
        fclose(pArchClientes);
    }
}

/**************************************************************************
* \brief Funcion que obtiene un valor entero cualquiera manualmente
* \return int valor obtenido
**************************************************************************/
int obtenerInt(){
    int valor;
    printf("\n Ingrese nuevo valor : ");
    scanf("%d", &valor);
    return valor;
}

/**************************************************************************
* \brief Funcion que pasa a un arreglo de clientes los registros del archivo
* \param stCliente arreglo de clientes a agregar
* \return int validos del arreglo
**************************************************************************/
int archivoToArreglo(stCliente a[]){
    int v = 0;
    FILE *pArchClientes  = fopen(AR_CLIENTES, "rb");
    if(pArchClientes){
        while(fread(&a[v],sizeof(stCliente),1,pArchClientes) > 0){
           v++;
        }
        fclose(pArchClientes);
    }
    return v;
}


///////////////// FUNCIONES DE VISUALIZACION /////////////////


/**************************************************************************
* \brief Controla la seccion para mostrar clientes, filtrarlos y llamada a modificar
**************************************************************************/
void mostrarClientes() {
    stCliente a[MAX_CLIENTES];
    int v = 0;
    char opcion;
    v = archivoToArreglo(a);
    do{
        //system("cls");
        printf("(1) Filtrar    |    (2) Todos    |  (ESC) salir\n\n");
        mostrarListaClientes(a, v);
        fflush(stdin);
        opcion = getch();
        switch (opcion)
        {
        case 49:
            v = controlarFiltro(a);
            break;
        case 50:
            v = archivoToArreglo(a);
            break;
        }
    }while(opcion != ESC);
}

/**************************************************************************
* \brief Funcion que muestra las opciones de los filtros de clientes
**************************************************************************/
void mostrarFiltros() {

    printf("\n ----------- FILTRAR POR ---------------");
    printf("\n ----------------------------------------");
    printf("\n 1) Nro Cliente ......: ");
    printf("\n 2) Nombre ...........: ");
    printf("\n 3) Apellido .........: ");
    printf("\n 4) DNI ..............: ");
    printf("\n 5) Email ............: ");
    printf("\n 6) Domicilio ........: ");
    printf("\n 7) Movil ............: ");
    printf("\n 8) Baja .............: ");
    printf("\n\n\n Cancelar (ESC)     ");

}

/**************************************************************************
* \brief Funcion que muestra las opciones para modificar un cliente
* \param stCliente cliente a modificar
**************************************************************************/
void mostrarModificacion(stCliente c) {

    printf("\n ----------------------------------------");
    printf("\n 1) Nro Cliente ......: %d", c.nroCliente);
    printf("\n 2) Nombre ...........: %s", c.nombre);
    printf("\n 3) Apellido .........: %s", c.apellido);
    printf("\n 4) DNI ..............: %d", c.dni);
    printf("\n 5) Email ............: %s", c.email);
    printf("\n 6) Domicilio ........: %d", c.domicilio);
    printf("\n 7) Movil ............: %d", c.movil);
    printf("\n 8) Baja .............: %s", (c.baja) ? "SI" : "NO" );
    printf("\n\n\n Cancelar (ESC)   |    Confirmar (c)");
}

/**************************************************************************
* \brief Funcion que muestra una lista de clietnes
* \param stCliente arreglo de clientes a mostrar
* \param int validos del arreglo
**************************************************************************/
void mostrarListaClientes(stCliente c[], int v) {
    for(int i = 0; i < v; i++){
        mostrarUnCliente(c[i]);
    }
}


/**************************************************************************
* \brief Funcion que muestra un clietne
* \param stCliente cliente a modificar
**************************************************************************/
void mostrarUnCliente(stCliente c) {

    printf("\n ----------------------------------------");
    printf("\n ID EMPLEADO ......: %d", c.id);
    printf("\n Nro Cliente ......: %d", c.nroCliente);
    printf("\n Nombre ...........: %s", c.nombre);
    printf("\n Apellido .........: %s", c.apellido);
    printf("\n DNI ..............: %d", c.dni);
    printf("\n Email ............: %s", c.email);
    printf("\n Domicilio ........: %d", c.domicilio);
    printf("\n Movil ............: %d", c.domicilio);
    printf("\n Baja .............: %s", (c.baja) ? "SI" : "NO" );

}


///////////////// FUNCIONES DE MODIFICACION /////////////////


/**************************************************************************
* \brief Funcion que controla la modificacion de un cliente
**************************************************************************/
void controlarModificacionCliente(){
    stCliente b[MAX_CLIENTES];
    stCliente c;
    int v, encontrado = 0;
    v = archivoToArreglo(b);
    int nroCliente = -1;
    printf("Ingrese el Nro Cliente a modificar : ");
    scanf("%d", &nroCliente);
    for(int i = 0; i < v; i++){
        if(b[i].nroCliente == nroCliente){
            c = b[i];
            encontrado = 1;
        }
    }
    if(encontrado){
        formularioModificacionCliente(c);
    } else {
        printf("El Nro Cliente ingresado no existe en el registro");
        system("pause");
    }
}

/**************************************************************************
* \brief Funcion formulario para la modificacion de un cliente con validacion de datos
* \param stCliente cliente a modificar
**************************************************************************/
void formularioModificacionCliente(stCliente c){
    stCliente cm = c;
    char opcion;
    do{
        mostrarModificacion(cm);
        fflush(stdin);
        opcion = getch();
        switch (opcion){
            case 49:{
                int valor;
                valor = obtenerInt();
                if(!existeNroClienteExcl(valor, cm.id)){
                    cm.nroCliente = valor;
                } else {
                    printf("\n\n Ya existe un cliente con ese Nro Cliente! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            case 50:{
                printf("\n Ingrese nuevo valor : ");
                scanf("%s", &cm.nombre );
                break;
            }
            case 51:{
                printf("\n Ingrese nuevo valor : ");
                scanf("%s", &cm.apellido);
                break;
            }
            case 52:{
                int valor;
                valor = obtenerInt();
                if(!existeDNIClienteExcl(valor, cm.id)){
                    cm.dni = valor;
                } else {
                    printf("\n\n Ya existe un cliente con ese Nro Cliente! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            case 53:{
                char valor[MAX_MAIL];
                printf("\n Ingrese nuevo valor : ");
                scanf("%s", &valor);
                if(validaEmail(valor)){
                    strcpy(&cm.email, valor);
                } else {
                    printf("\n\n Correo invalido! ..........(OK) \n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                }
                break;
            }
            case 54:{
                printf("\n Ingrese nuevo valor : ");
                scanf("%s", &cm.domicilio);
                break;
            }
            case 55:{
                int valor;
                valor = obtenerInt();
                cm.movil = valor;
                break;
            }
            case 56:{
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
    }while (opcion != ESC && opcion != 'c');
    if(opcion == 'c'){
        modificarCliente(cm);
    }
}

/**************************************************************************
* \brief Sobreescribe un cliente en un archivo de clientes
* \param stCliente c el cliente modificado
**************************************************************************/
void modificarCliente(stCliente c) {
    int pos = 0;
    pos = posPorIdCliente(c.id);
    FILE *pArchClientes = fopen(AR_CLIENTES, "r+b");
    if(pArchClientes){
        fseek(pArchClientes, sizeof(stCliente)*pos, SEEK_SET);
        fwrite(&c, sizeof(stCliente), 1, pArchClientes);
        fclose(pArchClientes);
    }
}


///////////////// FUNCIONES DE BUSQUEDA /////////////////

/**************************************************************************
* \brief Funcion que obtiene el nro de cliente segun su idcliente
* \param int id cliente
* \return int Nro cliente
**************************************************************************/
int obtenerNroClientePorID(int id) {
    int nroCliente = -1;
    stCliente c;
    FILE *pArchClientes = fopen(AR_CLIENTES, "rb");
    if(pArchClientes){
        while(nroCliente == -1 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.id == id){
                nroCliente = c.nroCliente;
            }
        }
    }
    return nroCliente;
}

/**************************************************************************
* \brief Funcion que obtiene el id de cliente segun su nrocliente
* \param int nro cliente
* \return int id cliente
**************************************************************************/
int obtenerIdClientePorNro(int nro) {
    int id = -1;
    stCliente c;
    FILE *pArchClientes = fopen(AR_CLIENTES, "rb");
    if(pArchClientes){
        while(id == -1 &&  fread(&c, sizeof(stCliente),1,pArchClientes) > 0){
            if(c.nroCliente == nro){
                id = c.id;
            }
        }
        fclose(pArchClientes);
    }
    return id;
}

/**************************************************************************
*
* \brief Retorna el ultimo id cargado
* \return int -1 si no hay registros o el id del ultimo registro
*
**************************************************************************/
int ultimoIdCliente() {
    stCliente c;
    int id = -1;
    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        fseek(pArchCliente, sizeof(stCliente)*(-1),SEEK_END);
        if(fread(&c,sizeof(stCliente),1,pArchCliente) > 0){
            id = c.id;
        }
        fclose(pArchCliente);
    }
    return id;
}

/*************************************************************************
*
* \brief Busca en un archivo de tipo stCliente un nroCliente
* \param int nroCliente
* \return int 0 si no existe / 1 si existe
*
**************************************************************************/
int existeNroClienteExcl(int nro, int id){
    int flag = 0;
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.nroCliente == nro && c.id != id){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }

    return flag;
}

/*************************************************************************
*
* \brief Busca en un archivo de tipo stCliente un dni
* \param int dni
* \return int 0 si no existe / 1 si existe
*
**************************************************************************/
int existeDNIClienteExcl(int dni, int id) {
    int flag = 0;
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.dni == dni && c.id != id){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }

    return flag;
}

/*************************************************************************
*
* \brief Busca en un archivo de tipo stCliente un dni
* \param int dni
* \return int 0 si no existe / 1 si existe
*
**************************************************************************/
int existeDNICliente(int dni){
    int flag = 0;
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.dni == dni){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }

    return flag;
}

/*************************************************************************
*
* \brief Busca en un archivo de tipo stCliente un nroCliente
* \param int nroCliente
* \return int 0 si no existe / 1 si existe
*
**************************************************************************/
int existeNroCliente(int nro){
    int flag = 0;
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.nroCliente == nro){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }

    return flag;
}

/*************************************************************************
*
* \brief Busca la posicion en el archivo de un determinado cliente por su id
* \param int id
* \return int posicion
*
**************************************************************************/
int posPorIdCliente(int id){
    int pos = -1;
    stCliente c;
    FILE *pArchClientes = fopen(AR_CLIENTES, "rb");
    if(pArchClientes){
        while(pos == -1 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.id == id){
                pos = ftell(pArchClientes)/sizeof(stCliente) -1;
            }
        }
        fclose(pArchClientes);
    }

    return pos;
}

/*********************************************************************//**
*
* \brief Valida si existe una @ en un string
* \param char email[]
* \return int 0 si no existe - 1 si existe
*
**************************************************************************/
int validaEmail(char email[]){
    int v=strlen(email);
    int i=0;
    int flag=0;
    while(i<v && flag == 0){
        if(email[i]==64){ /// =='@'
            flag=1;
        }
        i++;
    }
    return flag;
}

///////////////// FUNCIONES DE FILTROS /////////////////

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por Nro Cliente
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarNro(stCliente a[]){
    stCliente c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE * pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while (fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.nroCliente == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por nombre
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarNombre(stCliente a[]){
    stCliente c;
    int v = 0;
    char valor[MAX_NOMBRE];
    printf("Buscar: ");
    fflush(stdin);
    gets(valor);

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while(fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(!strcmp(c.nombre,valor)){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por apellido
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarApellido(stCliente a[]){
    stCliente c;
    int v = 0;
    char valor[MAX_NOMBRE];
    printf("Buscar: ");
    fflush(stdin);
    gets(valor);

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while (fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(!strcmp(c.apellido,valor)){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por dni
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarDNI(stCliente a[]){
    stCliente c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while (fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.dni == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por email
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarEmail(stCliente a[]){
    stCliente c;
    int v = 0;
    char valor[MAX_MAIL];
    printf("Buscar: ");
    fflush(stdin);
    gets(valor);

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while (fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(!strcmp(c.email,valor)){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por domicilio
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarDomicilio(stCliente a[]){
    stCliente c;
    int v = 0;
    char valor[MAX_DOM];
    printf("Buscar: ");
    fflush(stdin);
    gets(valor);

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while (fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(!strcmp(c.domicilio, valor)){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por movil
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarMovil(stCliente a[]){
    stCliente c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while (fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.movil == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que obtiene un arreglo de clientes filtrados por estado
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int filtrarBaja(stCliente a[]){
    stCliente c;
    int v = 0;
    int valor;
    printf("Buscar: ");
    scanf("%d", &valor);

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");
    if(pArchCliente){
        while (fread(&c, sizeof(stCliente),1,pArchCliente) > 0){
            if(c.baja == valor){
                a[v] = c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}

/**************************************************************************
* \brief Funcion que controla los filtros de clientes
* \param stCliente arreglo de clientes
* \return int validos del arreglo
**************************************************************************/
int controlarFiltro(stCliente a[]){
    int v;
    char opcion;

    mostrarFiltros();
    fflush(stdin);
    opcion = getch();
    switch (opcion)
    {
    case 49:
        v = filtrarNro(a);
        break;
    case 50:
        v = filtrarNombre(a);
        break;
    case 51:
        v = filtrarApellido(a);
        break;
    case 52:
        v = filtrarDNI(a);
        break;
    case 53:
        v = filtrarEmail(a);
        break;
    case 54:
        v = filtrarDomicilio(a);
        break;
    case 55:
        v = filtrarMovil(a);
        break;
    case 56:
        v = filtrarBaja(a);
        break;
    }

    return v;
}
