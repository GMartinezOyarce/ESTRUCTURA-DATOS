#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
/*--------------------Defines para Tamaños de Strings---------------------*/

#define TEXTO 1001
#define RUC 15
#define FECHA 11
#define RUT 11
#define MAXVICTIMAS 1000
/*------------------------------------------------------------------------*/

/*-----------------------Defines para Print Errores-----------------------*/

#define FORMATO 0
#define DENUNCIA 1
#define CARPETA 2
#define DILIGENCIA 3
#define IMPUTADO 4
#define RESOLUCION 5
#define PRUEBA 6
#define DECLARACION 7
#define CAUSA 8
#define DENUNCIAINEXISTENTE 9
#define CARPETAENCONTRADA 10
#define CARPETAINEXISTENTE 11

/*-------------------------ESTRUCTURA DEL SISTEMA-------------------------*/
struct Prueba {
  /*Si Tipo Prueba == 0 es un informe Pericial
   * Si Tipo Prueba == 1 es una grabacion
   * Si Tipo Prueba == 2 es un documento
   * Si Tipo Prueba == 3 es una prueba fisica
   */
  int tipoDePrueba;
  char descripcionPrueba[TEXTO];
  char fecha[FECHA];
};

/*Lista Simplemente Enlazada*/
struct NodoPruebas {
  struct Prueba *prueba;
  struct NodoPruebas *sig;
};


struct Resolucion {
  char rutJuez[TEXTO];
  /*Si Tipo Resolucion == 0 es Sentencia o Fallo
   * si Tipo Resolucion == 1 es Autorizacion para diligencias
   * si Tipo Resolucion == 2 es una medida Cautelar
   * si tipo Resolucion == 3 es un sobreseimiento
   */
  int tipoResolucion;

  /*Si origen == 0 la resolucion fue emitida por el Juez de Garantia
   * Si origen == 1 la resolucion fue emitida por el tribunal de Juicio Oral
   */
  int origenResolucion;
  char descripcion[TEXTO];
  char fecha[FECHA];

};

/*Lista simple*/
struct NodoResoluciones {
  struct Resolucion *resolucion;
  struct NodoResoluciones *sig;
};

struct Diligencia {
  /*La persona que pidio la diligencia
   *Si Origen Diligencia == 0 lo pidio El fiscal
   *Si origen == 1 lo pidio la victima,
   *Si origen == 2 lo pidio el imputado
   *Si Origen == 3 Lo pidio un Juez
   */
  int OrigenDiligencia;

  /*Ejemplos: allanamientos, intercepciones Telefonicas, citaciones,
   * toma de declaraciones a victimas, testigos o imputados, peritajes,
   * inspecciones, medidas de proteccion a victimas o testigos
   *
   * Ya que son demaciados tipos no podemos usar int
   */
  char tipoDiligencia[TEXTO];

  char descripcionDiligencia[TEXTO];

  char fechaDiligencia[FECHA];

  /*Si quien pide la diligencia no es el fiscal,
   * la diligencia queda como rechazada pero igualmente se guarda
   * dentro de la carpeta investigativa
   * si aprobacion == 1, aprobada
   * si aprobacion == 0, rechazada
   * si aprobacion == -1, en proceso
   */
  int aprobacion;
  /*Si urgencia == 1, es urgencia baja
   * Si urgencia == 2, es urgencia media
   * Si urgencia == 3, es urgencia Alta
   */
  int urgencia;
  /*
   * Si impacto == 1, es de bajo impacto para la investigacion
   * Si impacto == 2 es de medio impacto para la investigacion
   * Si impacto == 3 es de alto impacto para la investigacion
   */
  int impacto;
};

/*Lista Simplemente enlazada*/
struct NodoDiligencias {
  struct Diligencia *diligencia;
  struct NodoDiligencias *sig;
};

struct Declaracion {
  char rut[RUT];
  /*Si declaracion == 0 es una declaracion de la victima
   *Si declaracion == 1 es una declaracion de un testigo
   *Si declaracion == 2 es una declaracion de un imputado
   */
  int origenDeclaracion;
  char declaracion[TEXTO];
  char fecha[FECHA];
};

/*Lista Simplemente enlazada*/
struct NodoDeclaraciones{
  struct Declaracion *declaracion;
  struct NodoDeclaraciones *sig;
};

struct Causa {
  /*Tipo de causa por la que de esta demandando
   * si causa == 0 es un crimen (Infraccion grave)
   * si causa == 1 es un delito simple (Ejemplo:Hurto, estafa)
   * si causa == 2 es una falta (Ejemplo: Infracciones de transito)
   */
  int tipoCausa;
  char descripcionCausa[TEXTO];
};

struct NodoCausas {
  struct Causa *causa;
  struct NodoCausas *sig;
};

struct Imputado {
  /*Rut del imputado*/
  char rut[RUT];

  /*Medidas que se tomo para controlar al imputado,
   * como prision preventiva o arraigo
   */
  /*Si sentencia == 0 es Condenatoria
  *Si sentencia == 1 es Absolutoria*/
  int tipoSentencia;

  /*Si se hace un sobresimiento, un acuerdo reparatorio,
   *escribir aca la desripcion de la decision,
   * si se hace una sentencia hacer una descripcion, etc.
   */
  char descripcionSentencia[TEXTO];

  char medidasCautelares[TEXTO];

  /*Lista Simple con todas las Causas que se le acusan al imputado*/
  struct NodoCausas *causas;

};

struct NodoImputados {
  struct Imputado *imputado;
  struct NodoImputados *sig;
};

struct CarpetaInvestigativa {
  char ruc[RUC];
  /*Posibles Estados de Carpeta:
   *Si estado == 0 En investigacion
   *Si estado == 1 Juicio Oral
   *Si estado == 2 Archivada
   *Si estado == 3 Cerrada
   */
  int estadoCarpeta;

  /*si tipoDeJuicio == 0, es un juicio publico
   * si tipodeJuicio == 1, es un juicio privado
   */
  int tipoDeJuicio;

  struct Denuncia *denuncia;
  struct NodoImputados *imputado;
  /*Lista Simplemente enlazada*/
  struct NodoDeclaraciones *declaraciones;
  /*Lista Simplemente enlazada*/
  struct NodoPruebas *pruebas;
  /*Lista Simplemente enlazada*/
  struct NodoDiligencias *diligencias;
  /*Lista Simplemente enlazada*/
  struct NodoResoluciones *resoluciones;
};

/*Arbol binario de carpetas investigativas*/
struct arbolCarpetas {
  struct CarpetaInvestigativa*carpetaInvestigativa;
  struct arbolCarpetas *izq, *der;
};

struct RutVictima {
  char rut[RUT];
};

struct Denuncia{
  /* RUC Para identificar la denuncia*/
  char ruc[RUC];
  /* Rut del denunciante*/
  char rutDenunciante[RUT];
  /*Si origen Denunciante == 0 denuncio una victima
   * Si origen Denunciante == 1 denuncio un testigo
   * Si origen Denunciante == 2 denuncio un tercero
   * Si origen Denunciante == 3 denuncio Carabineros
   * Si origen Denunciante == 4 denuncio PDI
   */
  int origenDenunciante;
  /*Fecha en la que se hizo la denuncia*/
  char fecha[FECHA];

  /*Lista con las Causas por las cuales que se esta haciendo la denuncia*/
  struct NodoCausas *causas;
  /*Posibles Estados de Denuncia:
   *Si estado == -1 Todavia no se inicia la investigacion
  *Si estado == 0 En investigacion
  *Si estado == 1 Juicio Oral
  *Si estado == 2 Archivada
  *Si estado == 3 Cerrada
  */
  int estadoDenuncia;

  struct RutVictima **rutVictimas;
  int pLibreRutVictimas;

 };

/*Lista Circular Doblemente Enlazada*/
struct NodoDenuncias {
  struct Denuncia *denuncia;
  struct NodoDenuncias *sig,*ant;
};

struct Fiscal {
  char rut[RUT];
  char contrasenia[TEXTO];
  /*lista simplemente enlazada, Posiblemente se cambie a circular doblemente enlazada,
   * porque en este caso solo se agregan denuncias, no se eliminan
   */
  struct NodoDenuncias *denuncias;
  /*arbol binario con carpetas de investigacion*/
  struct arbolCarpetas *carpetas;

};

/*Struct principal con un arreglo fiscales de tamaño TamFiscal*/
struct MinisterioPublico {
  struct Fiscal **fiscales;
  int tamFiscal;
};

/*------------------------------------------------------------------------*/

/*------------------------FUNCIONES DE MENUS------------------------------*/

/*Funcion que genera Espacios Vacios para Limpiar La pantalla*/
void limpiarPantalla() {
  int i;
  for(i=0;i<20;i++) printf("\n");
}


/* Limpiar el buffer de entrada después de un scanf()*/
void limpiarBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}
/*------------------------------------------------------------------------*/

/*-----------------------FUNCIONES DE BUSQUEDA----------------------------*/

/*Funcion que Busca Una Carpeta dentro del Arbol Carpetas por su ruc y la retorna*/
struct CarpetaInvestigativa* BUSCARCARPETA(struct arbolCarpetas *raiz, char *ruc) {
  int cmp;
  if (raiz == NULL) return NULL;

  cmp = strcmp(ruc, raiz->carpetaInvestigativa->ruc);
  if (cmp == 0) return raiz->carpetaInvestigativa;
  if (cmp < 0) return BUSCARCARPETA(raiz->izq, ruc);
  return BUSCARCARPETA(raiz->der, ruc);
}


/*Función para buscar una denuncia por RUC en la lista de denuncias del fiscal*/
struct Denuncia* BUSCARDENUNCIA(struct Fiscal *fiscal, char *ruc) {
  struct NodoDenuncias *head = fiscal->denuncias,*actual;
  actual = head;
  if (fiscal -> denuncias == NULL) return NULL;
  do{
    if (strcmp(actual->denuncia->ruc, ruc) == 0) {
      return actual->denuncia;
    }
    actual = actual->sig;
  }while (actual != head);
  return NULL;
}

/*------------------------------------------------------------------------*/

/*------------------------FUNCIONES DE PRINTS-----------------------------*/
/*Funcion Para Printear Errores*/
void printError(int tipo) {
  switch(tipo){
    case FORMATO: printf("\nFormato Equivocado\n");break;
    case DENUNCIA: printf("\nDenuncia No encontrada\n");break;
    case CARPETA: printf("\nCarpeta Investigativa No Encontrada\n");break;
    case DILIGENCIA: printf("\nDiligencia No Encontrada\n");break;
    case IMPUTADO: printf("\nImputado No Encontrada\n");break;
    case RESOLUCION: printf("\nResolucion No Encontrada\n");break;
    case PRUEBA: printf("\nPrueba No Encontrada\n");break;
    case DECLARACION: printf("\nDeclaracion No Encontrada\n");break;
    case CAUSA: printf("\nCausa No Encontrada\n");break;
    case DENUNCIAINEXISTENTE: printf("\nDenuncia No inexistente\n");break;
    case CARPETAENCONTRADA: printf("\nCarpeta Investigativa ya existente\n");break;
    case CARPETAINEXISTENTE: printf("\nCarpeta Investigativa no existe\n"); break;
    default: printf("\nError desconocido\n"); break;
  }
  printf("1: Intentar nuevamente  Vuelva a ingresar el dato despues de escribir 1.\n");
  printf("Cualquier otro Numero: Volver al menu anterior\n");
}

/*Funcion para Cuando ocurre un error en el procedimiento*/
void ingresarOpcion(int *opcionDestino) {
  int resultadoScan;
  do {
    printf("Seleccione una opcion: ");
    resultadoScan = scanf("%d", opcionDestino);

    if (resultadoScan == 1) {
      limpiarBuffer();
      break;
    }else {
      printf("Error: Debe ingresar un numero entero valido.\n");
      limpiarBuffer();
    }
  } while (1);
}

/* Esperar a que el usuario presione Enter*/
void esperarEnter() {
  printf("\nPresione Enter para continuar...\n");
  limpiarBuffer(); /* Consume el '\n' previo si existe*/
  (void)getchar(); /* Espera a que el usuario presione Enter*/
}


/*------------------------------------------------------------------------*/

/*-------------------FUNCIONES PARA INGRESAR DATOS------------------------*/
/*Esta Funcion analiza un string y devielve 0 si esta no contiene espacios*/
int revisarEspacios( char *str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ') {
      return 1; /* contiene espacio*/
    }
  }
  return 0; /*no contiene espacios*/
}

char *ingresarRuc() {
  char ruc[RUC];
  char *vacio = NULL;
  char *ret;
  int opcion;

  do {
    fgets(ruc, RUC, stdin);
    ruc[strcspn(ruc, "\n")] = 0;
    if (ruc[9] != '-' || revisarEspacios(ruc) == 1) {
      printError(FORMATO);
      ingresarOpcion(&opcion);
      if (opcion!= 1) {
        return vacio;
      }
    }else {
      break;
    }

  }while (1);
  ret = malloc(RUC);
  if (ret != NULL) {
    strcpy(ret, ruc);
  }
  return ret;
}


char *ingresarFecha() {
  char fecha[FECHA];
  char *vacio = NULL;
  char *ret;
  int opcion;
  do {

    fgets(fecha, FECHA, stdin);
    limpiarBuffer();
    limpiarPantalla();
    if (revisarEspacios(fecha) == 1 || fecha[2]!= '/'|| fecha[5] != '/') {
      printError(FORMATO);
      ingresarOpcion(&opcion);
      limpiarBuffer();
      if (opcion != 1) {
        return vacio;
      }
    }else {
      break;
    }
  }while (1);
  ret = malloc(FECHA);
  if (ret != NULL) {
    strcpy(ret, fecha);
  }
  return ret;
}
/*------------------------------------------------------------------------*/

struct NodoCausas *crearNodoCausas() {
  struct NodoCausas *nuevoNodo;
  nuevoNodo = (struct NodoCausas *)malloc(sizeof(struct NodoCausas));
  nuevoNodo->causa = (struct Causa *)malloc(sizeof(struct Causa));
  nuevoNodo->sig = NULL;
  return nuevoNodo;
}

int anidarCausa(struct Denuncia *denuncia, struct NodoCausas *nuevoNodo) {
  struct NodoCausas *head = denuncia->causas;
  if (denuncia == NULL || nuevoNodo == NULL) {
    return FALSE;
  }
  if (denuncia->causas == NULL) {

    denuncia->causas = nuevoNodo;

  } else {

    head = denuncia->causas;
    while (head->sig != NULL) {
      head = head->sig;
    }
    head->sig = nuevoNodo;
  }
  return TRUE;
}

/*Funcion para Agregar una sola Causa*/
void AGREGARCAUSA(struct Denuncia *denuncia) {
  struct NodoCausas *nuevoNodo = crearNodoCausas();
  do {
    limpiarPantalla();
    printf("Ingrese La Causa:\n");
    printf("0 Si es un Crimen (Infraccion grave como Homicidio)\n");
    printf("1 Si es un Delito Simple (Ejemplo: Hurto o Estafa)\n");
    printf("2 Si es una Falta (Ejemplo: Infracciones de Transito)\n");
    scanf("%d", &nuevoNodo->causa->tipoCausa);
    limpiarBuffer();
    if (nuevoNodo-> causa->tipoCausa == 0 || nuevoNodo->causa->tipoCausa == 1 || nuevoNodo-> causa->tipoCausa == 2) {
      printf("Ingrese la descripcion de su Causa\n");
      fgets(nuevoNodo->causa->descripcionCausa, TEXTO, stdin);
      nuevoNodo->causa->descripcionCausa[strcspn(nuevoNodo->causa->descripcionCausa, "\n")] = 0;
      break;
    }
  }while (1);
  if (!anidarCausa(denuncia,nuevoNodo)) {
    printf("Error al anidar Causa\n");
  }
}




/*-----------------------FUNCIONES DE DENUNCIAS----------------------------*/
void printDenuncia (struct Denuncia *denuncia) {
  struct NodoCausas *rec = denuncia->causas;
  int i;
  printf("\n\n");
  printf("RUC: %s\n\n",denuncia->ruc);
  /*Print de quien hizo la denuncia*/
  if (denuncia->origenDenunciante == 0) {
    printf("Denunciante: Victima\n\n");
  }
  if (denuncia->origenDenunciante== 1) {
    printf("Denunciante: Testigo\n\n");
  }
  if (denuncia->origenDenunciante== 2) {
    printf("Denunciante: Un Tercero\n\n");
  }
  if (denuncia->origenDenunciante== 3) {
    printf("Denunciante: Carabineros\n\n");
  }
  if (denuncia->origenDenunciante== 4) {
    printf("Denunciante: PDI\n\n");
  }

  printf("Rut Denunciante: %s\n\n",denuncia->rutDenunciante);
  /*No es necesario revisar si esta vacio, pues, siempre tiene que haber al menos 1 en el nodo Causas*/
  if (rec == NULL) {
    printf("NO HAY CAUSAS\n\n");
  }else {
    printf("----------Causas----------\n");
    while (rec != NULL){
      /*Print de las causas*/
      if (rec->causa->tipoCausa == 0) {
        printf("Causa: Crimen\n");
        printf("Descripcion: %s\n\n",rec->causa->descripcionCausa);
      }
      if (rec->causa->tipoCausa == 1) {
        printf("Causa: Delito\n");
        printf("Descripcion: %s\n\n",rec->causa->descripcionCausa);
      }
      if (rec->causa->tipoCausa == 2) {
        printf("Causa: Infraccion\n");
        printf("Descripcion: %s\n\n",rec->causa->descripcionCausa);
      }
      rec = rec->sig;
    }
  }
  printf("Fecha en la cual se hizo la denuncia: %s\n\n",denuncia->fecha);

  /*Print de estados de la denuncia*/
  if (denuncia->estadoDenuncia == -1) {
    printf("Estado: Todavia no se ha iniciado Ninguna investigacion a la Denuncia\n\n");
  }
  if (denuncia->estadoDenuncia == 0) {
    printf("Estado: Denuncia en investigacion\n\n");
  }
  if (denuncia->estadoDenuncia == 1) {
    printf("Estado: Denuncia se encuentra en Juicio Oral\n\n");
  }
  if (denuncia->estadoDenuncia == 2) {
    printf("Estado: Denuncia se encuentra archivada\n\n");
  }
  if (denuncia->estadoDenuncia == 3) {
    printf("Estado: Denuncia ha sido cerrada de forma permanente\n\n");
  }

  printf("Rut de Victimas: ");
  for (i = 0; i <= denuncia->pLibreRutVictimas;i++) {
    if (i == denuncia->pLibreRutVictimas) {
      printf("%s.\n\n",denuncia->rutVictimas[i]);
    }else {
      printf("%s , ",denuncia->rutVictimas[i]);
    }
  }
  esperarEnter();
}
void buscarDenunciaRUC(struct Fiscal *fiscal) {
  struct Denuncia *denuncia;
  char ruc[RUC];
  char *temporal;
  if (fiscal->denuncias == NULL) {
    printf("No Hay Denuncias En el Sistema\n");
  }
  printf("Ingrese el Ruc de la denuncia: (Formato: 123456789-2024)\n");
  do {
    temporal = ingresarRuc();
    if (temporal == NULL) {
      return;
    }
    strcpy(ruc, temporal);
    break;

  }while (1);

  denuncia = BUSCARDENUNCIA(fiscal,ruc);
  if (denuncia == NULL) {
    printf("No se ha encontrado su Denuncia\n");
  }else {
    printDenuncia(denuncia);
  }
  return;
}

void buscarDenunciaEstado(struct Fiscal *fiscal) {
  int opcion,encontrado = 0;
  struct NodoDenuncias *head = fiscal->denuncias, *actual;
  limpiarPantalla();
  if (head == NULL) {
    printf("No se ha ingresado ninguna Denuncia al sistema\n");
  }else {
    do {
      printf("Ingrese el numero de estado de Denuncia:\n");
      printf("-1 = Sin investigacion\n");
      printf("0 = en investigacion\n");
      printf("1 = en Juicio Oral\n");
      printf("2 = Archivada\n");
      printf("3 = Cerrada\n");
      ingresarOpcion(&opcion);
      if (opcion == -1 || opcion == 0 || opcion == 1|| opcion == 2 || opcion == 3) {
        break;
      }else {
        printf("");
      }
      limpiarPantalla();
    }while (1);
    actual = head;
    do {
      if (actual->denuncia->estadoDenuncia == opcion) {
        printDenuncia(actual->denuncia);
        encontrado = 1;
      }
      actual = actual->sig;
    }while (actual != head);
    if (encontrado == 0) {
      printf("No se ha encontrado ninguna Denuncia\n");
    }
  }

}

int anidarDenuncia(struct Fiscal *fiscal, struct Denuncia *denuncia) {
  struct NodoDenuncias *nodo;
  nodo = (struct NodoDenuncias *)malloc(sizeof(struct NodoDenuncias));
  if (nodo == NULL) {
    /*Si el Malloc Falla Retorna False*/
    return FALSE;
  }
  nodo ->denuncia = denuncia;
  /*Si el nodo esta vacio*/
  if (fiscal->denuncias == NULL) {
    fiscal->denuncias = nodo;

    nodo ->ant = nodo;
    nodo ->sig = nodo;
  }else {
    /*Si Solo existe un nodo*/
    if (fiscal->denuncias->sig == fiscal->denuncias) {
      fiscal->denuncias->sig = nodo;
      fiscal->denuncias -> ant = nodo;
      nodo->sig = fiscal->denuncias;
      nodo->ant = fiscal->denuncias;
    }else {
      /*Si existen 2 nodos o más*/
      nodo ->ant = fiscal->denuncias->ant;
      nodo ->sig = fiscal->denuncias;
      fiscal->denuncias->ant->sig = nodo;
      fiscal->denuncias->ant = nodo;
    }
  }
  return TRUE;
}

void agregarDenuncia(struct Fiscal *fiscal) {
  struct NodoDenuncias *nodo;
  struct Denuncia *denuncia;
  int i;
  int opcion;
  char ruc[RUC];
  char *temporal;
  printf("---------------CREAR DEMANDA-------------------\n");
  printf("Ingrese RUC de la carpeta / denuncia:\n");
  temporal = ingresarRuc();
  if (temporal == NULL) {
    return;
  }

  strcpy(ruc, temporal);

  do {
    if(BUSCARDENUNCIA(fiscal,ruc) != NULL) {
      limpiarPantalla();
      printf("Este RUC ya existe dentro del sistema\n");
      printf("1. Intentar nuevamente\n");
      printf("2. Volver al menu anterior\n");
      ingresarOpcion(&opcion);
      limpiarBuffer();
      if (opcion == 2) {
        return;  /*Salir de la función si el usuario elige volver*/
      }
      temporal = ingresarRuc();
      strcpy(ruc, temporal);
    }else {
      break;
    }
  }while(1);

  denuncia = (struct Denuncia *)malloc(sizeof(struct Denuncia));
  strcpy(denuncia->ruc,ruc);
  do {
    limpiarPantalla();
    printf("Quien esta haciendo la Denuncia?\n");
    printf("0 = Victima , 1 = Testigo, 2 = Tercero , 3 = Carabineros , 4 = PDI\n");
    scanf("%d", &denuncia->origenDenunciante);
    limpiarBuffer();
    if (denuncia -> origenDenunciante >=0 && denuncia -> origenDenunciante <= 4) {
      break;
    }
  }while (1);


  limpiarPantalla();

  do {
    printf("Ingrese Su Rut: (Formato:12345678-9)\n");
    fgets(denuncia ->rutDenunciante, 14, stdin);
    denuncia-> rutDenunciante[strcspn(denuncia -> rutDenunciante, "\n")] = 0;
    if (denuncia->rutDenunciante[0]  == '\0') {
      printf("No Se Ingreso Nada\n");
    }else {
      break;
    }
  }while(1);

  /*Se ingresa la fecha*/
  printf("Ingrese Fecha: (Formato: 01/01/2000)\n");
  temporal = ingresarFecha();
  if (temporal == NULL) {
    return;
  }
  strcpy(denuncia->fecha, temporal);

  denuncia->causas = NULL;
  do {
    AGREGARCAUSA(denuncia);

    printf("Desea Agregar Otra Causa a su denuncia?\n");
    printf("1 = SI , Cualquier otro Numero = NO\n");

    ingresarOpcion(&opcion);
    if (opcion != 1) {
      break;
    }
  }while (1);

  denuncia->rutVictimas = (struct RutVictima**)malloc(40*sizeof(struct RutVictima*));
  for (i = 0; i < 40; i++) {
    denuncia -> rutVictimas[i] = NULL;
  }
  denuncia->pLibreRutVictimas = 0;
  limpiarPantalla();
  do {
    limpiarBuffer();
    denuncia->rutVictimas[denuncia->pLibreRutVictimas] = (struct RutVictima*)malloc(sizeof(struct RutVictima));
    printf("Ingrese Rut de la victima: (Formato:12345678-9) \n");
    fgets(denuncia->rutVictimas[denuncia->pLibreRutVictimas]->rut, RUT, stdin);
    denuncia->rutVictimas[denuncia->pLibreRutVictimas]->rut[strcspn(denuncia->rutVictimas[denuncia->pLibreRutVictimas]->rut, "\n")] = 0;
    limpiarBuffer();
    if (denuncia->rutVictimas[denuncia->pLibreRutVictimas]->rut[0] == '\0'){
      printf("No Se Ingreso Nada\n");
    }else {
      printf("Desea Agregar otra Victima? \n");
      printf("1 = Si , Cualquier otro numero: NO\n");
      scanf("%d", &opcion);
      if (opcion != 1) {
        break;
      }
      denuncia->pLibreRutVictimas +=1;
    }
  }while (1);


  denuncia->estadoDenuncia = -1;


  if (!anidarDenuncia(fiscal,denuncia)) {
    printf("Error al Anidar Denuncia.\n");
  }else {
    printf("Se ha Agregado Su denuncia\n");
  }

}



void listarDenuncias(struct Fiscal *fiscal) {
  struct NodoDenuncias *head = fiscal->denuncias, *actual;
  limpiarPantalla();
  if (head == NULL) {

    printf("No se ha ingresado ninguna Denuncia al sistema\n");

  }else {
    actual = head;
    do {
      printDenuncia(actual->denuncia);
      actual = actual->sig;
    }while (actual!=head);
  }
}



void modificarEstadoDenuncia(struct Fiscal *fiscal) {

  struct Denuncia *denuncia;
  char ruc[RUC];
  char *temporal;
  int opcion;
  if (fiscal->denuncias == NULL) {
    printf("No Hay Denuncias En el Sistema\n");
    return;
  }
  printf("Ingrese El Ruc de la denuncia: ()\n");
  temporal = ingresarRuc();
  if (temporal == NULL) {return;}
  strcpy(ruc, temporal);

  denuncia = BUSCARDENUNCIA(fiscal,ruc);
  if (denuncia == NULL) {
    printf("No se encontro la Denuncia\n");
    return;
  }
  do {
    printf("Ingrese el nuevo estado de la denuncia:\n");
    printf("-1 = Sin investigacion\n");
    printf("0 = en investigacion\n");
    printf("1 = en Juicio Oral\n");
    printf("2 = Archivada\n");
    printf("3 = Cerrada\n");
    ingresarOpcion(&opcion);
    if (opcion >= -1 && opcion <= 3) {
      break;
    }
    printf("\n");
  }while (1);

  denuncia->estadoDenuncia = opcion;


}
/*---------------------FUNCIONES SOBRE CARPETAS----------------*/

/*---------------------FUNCION CREAR CARPETA


/* Función para crear una nueva carpeta investigativa*/
int CrearCarpeta(struct Fiscal *fiscal, char *rucIngresado) {
  struct Denuncia *denunciaEncontrada = NULL;
  struct CarpetaInvestigativa *nuevaCarpeta = NULL;
  struct arbolCarpetas *actual = NULL;
  struct arbolCarpetas *nuevoNodo = NULL;

  if (fiscal->denuncias == NULL) {
    return DENUNCIAINEXISTENTE;
  }

  denunciaEncontrada = BUSCARDENUNCIA(fiscal, rucIngresado);
  if (denunciaEncontrada == NULL){
    return DENUNCIA;
  }
  if (BUSCARCARPETA(fiscal->carpetas, denunciaEncontrada->ruc) != NULL) {
    return CARPETAENCONTRADA;
  }

  nuevaCarpeta = (struct CarpetaInvestigativa*)malloc(sizeof(struct CarpetaInvestigativa));


  strcpy(nuevaCarpeta->ruc, denunciaEncontrada->ruc);
  nuevaCarpeta->denuncia = denunciaEncontrada;
  nuevaCarpeta->declaraciones = NULL;
  nuevaCarpeta->pruebas = NULL;
  nuevaCarpeta->diligencias = NULL;
  nuevaCarpeta->resoluciones = NULL;
  nuevaCarpeta->imputado = NULL;
  nuevaCarpeta->estadoCarpeta = 0;

  nuevoNodo = (struct arbolCarpetas*)malloc(sizeof(struct arbolCarpetas));


  nuevoNodo->carpetaInvestigativa = nuevaCarpeta;
  nuevoNodo->izq = NULL;
  nuevoNodo->der = NULL;

  if (fiscal->carpetas == NULL) {
    fiscal->carpetas = nuevoNodo;
  } else {
    actual = fiscal->carpetas;
    while (1) {
      if (strcmp(nuevaCarpeta->ruc, actual->carpetaInvestigativa->ruc) < 0) {
        if (actual->izq == NULL) {
          actual->izq = nuevoNodo;
          break;
        } else {
          actual = actual->izq;
        }
      } else {
        if (actual->der == NULL) {
          actual->der = nuevoNodo;
          break;
        } else {
          actual = actual->der;
        }
      }
    }
  }
  return 0;
}

/*-----------------------FUNCION BUSCAR CARPETA Y MOSTRARLA POR RUC-------------*/
int buscarCarpetaRuc(struct Fiscal *fiscal, char *rucIngresado) {
  struct CarpetaInvestigativa *carpeta;
  struct NodoImputados *recImputado;
  struct NodoCausas *recCausas;
  struct NodoDeclaraciones *recDeclaraciones;
  struct NodoPruebas *recPruebas;
  struct NodoDiligencias *recDiligencias;
  struct NodoResoluciones *recResoluciones;
  limpiarPantalla();


  if (fiscal -> carpetas == NULL) {
    return CARPETAINEXISTENTE;
  }



  carpeta = BUSCARCARPETA(fiscal->carpetas, rucIngresado);
  if (carpeta == NULL) {
    return CARPETA;
  }
  printf("--------------------------------------------------\n");
  printf("RUC: %s\n", carpeta->ruc);
  printf("Estado: ");
  switch (carpeta->estadoCarpeta) {
    case 0: printf("En investigacion\n"); break;
    case 1: printf("Juicio Oral\n"); break;
    case 2: printf("Archivada\n"); break;
    case 3: printf("Cerrada\n"); break;
    default: printf("Desconocido\n"); break;
  }

  /*Se muestra la denuncia de la carpeta*/
  printf("\n-----------Denuncia que contiene la Carpeta----------\n");
  printf("RUT DENUNCIANTE = %s\n", carpeta->denuncia->rutDenunciante);
  printf("Origen de la denuncia :");
  switch (carpeta->denuncia-> origenDenunciante) {
    case 0: printf("Victima\n"); break;
    case 1: printf("Testigo\n"); break;
    case 2: printf("Tercero\n"); break;
    case 3: printf("Carabineros de Chile\n"); break;
    case 4: printf("PDI\n"); break;
    default: printf("Desconocido\n"); break;
  }
  printf("Fecha: %s\n", carpeta->denuncia->fecha);

  /*Se recorren las Causas de la denuncia para poder mostrarlas*/
  recCausas = carpeta->denuncia->causas;
  if (recCausas == NULL)
    printf("No hay Causas en la denuncia\n");
  while (recCausas != NULL) {
    printf("El tipo de Causa por la que esta demandado :");
    switch (recCausas->causa->tipoCausa) {
      case 0: printf("CRIMEN \n"); break;
      case 1: printf("DELITO SIMPLE \n");break;
      case 2: printf("FALTA\n");break;
      default: printf("Desconocido\n"); break;
    }
    printf("Descripcion de la Causa %s\n", recCausas-> causa-> descripcionCausa);
    recCausas= recCausas->sig;
  }

  /*se recorre la lista de imputados para mostrar cada imputado de la carpeta*/
  printf("\n-----------Imputados que contiene la Carpeta----------\n");
  recImputado = carpeta -> imputado;
  if (recImputado != NULL) {
    while (recImputado != NULL) {
      printf("RUT Imputado: %s\n", recImputado->imputado->rut);
      printf("Tipo de la sentencia :");
      switch (recImputado->imputado->tipoSentencia) {
        case 0: printf("Condenatoria");break;
        case 1: printf("Absolutoria");break;
        default: printf("Desconocido\n"); break;
      }

      /*Verificacion de que si exiten las descripciones y medidas cautelares para ver si las imprimo o no*/
      if (strcmp(recImputado->imputado->descripcionSentencia,"")==0)
        printf("No hay descripcion de la sentencia\n");
      else
        printf("Descripcion de la sentencia : %s\n", recImputado-> imputado-> descripcionSentencia);
      if (strcmp(recImputado->imputado->medidasCautelares,"")==0)
        printf("No hay medidas cautelares\n");
      else
        printf("Las medidas Cautelares son: %s\n", recImputado-> imputado->medidasCautelares);


      /*reciclo codigo anterior para mostrar Causas*/
      recCausas = recImputado->imputado->causas;
      if (recCausas == NULL)
        printf("No hay Causas en el Imputado\n");

      while (recCausas != NULL) {
        printf("El tipo de Causa por la que esta demandado :");
        switch (recCausas->causa->tipoCausa) {
          case 0: printf("Crimen(INFRACCION GRAVE)\n"); break;
          case 1: printf("Delito simple(Ejemplo: Hurto, estafa)\n");break;
          case 2: printf("falta(Ejemplo: infracciones de transito\n)");break;
          default: printf("Desconocido\n"); break;
        }
        printf("Descripcion de la Causa %s\n",recCausas-> causa-> descripcionCausa);
        recCausas= recCausas->sig;
      }
      printf("------------------------------\n");
      recImputado = recImputado -> sig;
    }
  }
  else
    printf("Sin imputado asignado\n");

  /*Se recorre la lista de declaraciones para poder mostrarla por pantalla*/
  printf("\n-----------Declaraciones que contiene la Carpeta----------\n");
  recDeclaraciones = carpeta -> declaraciones;
  if (recDeclaraciones != NULL) {
    while (recDeclaraciones != NULL) {
      printf("Rut del Declarante: %s\n", recDeclaraciones->declaracion->rut);

      printf("Quien emitio la declaracion: ");
      switch (recDeclaraciones->declaracion->origenDeclaracion) {
        case 0: printf("Victima\n"); break;
        case 1: printf("Testigo\n"); break;
        case 2: printf("Imputado\n"); break;
        default: printf("Desconocido\n"); break;
      }
      printf("Descripcion de la Declaracion %s\n", recDeclaraciones->declaracion->declaracion);
      printf("Fecha de la declaracion : %s\n", recDeclaraciones->declaracion->fecha);
      recDeclaraciones = recDeclaraciones-> sig;
    }
  }
  else {
    printf("No hay Declaraciones\n");
  }
  /*Se recorre la lista de pruebas para  mostrarlas en pantalla*/
  printf("\n-----------Pruebas que contiene la Carpeta----------\n");
  recPruebas = carpeta -> pruebas;
  if (recPruebas != NULL) {\
    while (recPruebas!=NULL) {
      printf("Tipo de Prueba :");
      switch (recPruebas->prueba->tipoDePrueba) {
        case 0: printf("Informe Pericial\n"); break;
        case 1: printf("Grabacion\n");break;
        case 2: printf("Documento\n"); break;
        case 3: printf("Prueba fisica\n");break;
        default: printf("Desconocido\n"); break;
      }
      printf("Descripcion de la prueba:  %s\n", recPruebas->prueba->descripcionPrueba);
      printf("Fecha en la que se ingreso la prueba: %s\n", recPruebas->prueba->fecha);
      printf("----------------------------------------\n");

      recPruebas = recPruebas-> sig;
    }
  }
  else
    printf("No hay Pruebas\n");

  /*Se recorre la lista de diligencias para  mostrarlas en pantalla*/
  printf("\n-----------diligencias que contiene la Carpeta----------\n");
  recDiligencias = carpeta->diligencias;
  if (recDiligencias != NULL) {
    while (recDiligencias != NULL) {
      printf("Origen de la diligencia :");
      switch (recDiligencias->diligencia->OrigenDiligencia) {
        case 0: printf("Pedido de Fiscal\n"); break;
        case 1: printf("Victima\n"); break;
        case 2: printf("imputado\n"); break;
        default: printf("Desconocido\n"); break;
      }
      printf("tipo de la diligencia: %s\n", recDiligencias-> diligencia-> tipoDiligencia);
      printf("Descripcion de las diligencias: %s\n",recDiligencias->diligencia->descripcionDiligencia);
      printf("Fecha de ingreso de la diligencia: %s\n", recDiligencias ->diligencia->fechaDiligencia);

      printf("Estado de la diligencia: ");
      switch (recDiligencias->diligencia->aprobacion) {
        case 0: printf("Rechazada\n"); break;
        case 1: printf("Aprovada\n"); break;
        default: printf("Desconocido\n"); break;
      }


      printf("Urgencia de la diligencia: ");
      switch (recDiligencias-> diligencia-> urgencia) {
        case 1: printf("Urgencia Baja\n"); break;
        case 2: printf("Urgencia Media\n"); break;
        case 3: printf("Urgencia Alta\n"); break;
        default: printf("Desconocido\n"); break;
      }

      printf("Impacto de la Urgencia");
      switch (recDiligencias->diligencia-> impacto) {
        case 1: printf("Bajo impacto para la investigacion\n"); break;
        case 2: printf("Medio impacto para la investigacion\n"); break;
        case 3: printf("Alto impacto para la investgacion\n"); break;
        default:printf("Desconocido\n"); break;
      }
      printf("----------------------------------------\n");
      recDiligencias = recDiligencias-> sig;
    }
  }
  else
    printf("No hay Diligencias\n");

  /*Se recorren las resoluciones para mostrar por pantalla*/
  printf("\n-----------Resoluciones que contiene la Carpeta----------\n");
  recResoluciones = carpeta->resoluciones;
  if (recResoluciones !=NULL) {
    while (recResoluciones !=NULL) {
      printf("Rut del juez: %s\n", recResoluciones->resolucion->rutJuez);

      printf("El tipo de resolucion es: ");
      switch (recResoluciones-> resolucion -> tipoResolucion) {
        case 0: printf("Sentencia o Fallo\n"); break;
        case 1: printf("Autorizacion para diligencias\n"); break;
        case 2: printf("Medidas Cautelares\n"); break;
        case 3: printf("sobresimiento"); break;
        default: printf("Desconocido\n");break;
      }

      printf("Origen de la Resolucion: ");
      switch (recResoluciones-> resolucion-> origenResolucion) {
        case 0: printf("Juez de Garantia\n"); break;
        case 1: printf("Tribunal de Juicio Oral\n"); break;
        default: printf("Desconocido\n"); break;
      }

      printf("Descripcion de la Resolucion: %s\n", recResoluciones-> resolucion-> descripcion);
      printf("Fecha en la que se emitio la Resolucion: %s\n", recResoluciones-> resolucion-> fecha);

      printf("----------------------------------------\n");
      recResoluciones = recResoluciones-> sig;
    }
  }
  else
    printf("No hay Resoluciones\n");
  printf("\nCARPETA MOSTRADA CORRECTAMENTE\n");
  esperarEnter();
  return 0;
}

/*-----------------------------FUNCION MODIFICAR ESTADO CARPETA-------------------------*/
int modificarEstadoCarpeta(struct Fiscal *fiscal, char *rucIngresado, int estadoCarpeta) {
  struct CarpetaInvestigativa *carpeta;
  if (fiscal->carpetas == NULL) {
    return CARPETAINEXISTENTE;
  }

  carpeta = BUSCARCARPETA(fiscal->carpetas, rucIngresado);
  if (carpeta == NULL) {
    return CARPETA;
  }

  carpeta->estadoCarpeta = estadoCarpeta;
  return 0;
}

/*-----------------------------FUNCION AGREGAR DECLARACION------------------*/

int agregarDeclaracion(struct Fiscal *fiscal, char *rucCarpeta, struct Declaracion *datosDeclaracion) {
  struct CarpetaInvestigativa *carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  struct NodoDeclaraciones *nuevoNodo;
  struct NodoDeclaraciones *rec;

  if (carpeta == NULL) {
    return CARPETA;
  }

  nuevoNodo = (struct NodoDeclaraciones*)malloc(sizeof(struct NodoDeclaraciones));


  nuevoNodo->declaracion = datosDeclaracion;
  nuevoNodo->sig = NULL;

  if (carpeta->declaraciones == NULL) {
    carpeta->declaraciones = nuevoNodo;
  } else {
    rec = carpeta->declaraciones;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nuevoNodo;
  }
  return 0;
}

/*-------------------------FUNCION AGREGAR  DILIGENCIAS-----------------*/
int agregarDiligencia(struct Fiscal *fiscal, char *rucCarpeta, struct Diligencia *datosDiligencia) {
  struct CarpetaInvestigativa *carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  struct NodoDiligencias *nuevoNodo;
  struct NodoDiligencias *rec;

  if (carpeta == NULL) {
    return CARPETA;
  }

  nuevoNodo = (struct NodoDiligencias*)malloc(sizeof(struct NodoDiligencias));

  nuevoNodo->diligencia = datosDiligencia;
  nuevoNodo->sig = NULL;

  if (carpeta->diligencias == NULL) {
    carpeta->diligencias = nuevoNodo;
  } else {
    rec = carpeta->diligencias;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nuevoNodo;
  }
  return 0;
}

/*---------funcion para asignar prioridad a las diligencias--------*/

struct Imputado *buscarImputado(struct CarpetaInvestigativa *carpeta, char rut[RUT]) {
  struct NodoImputados *rec;
  if (carpeta->imputado == NULL) {
    return NULL;
  }
  rec = carpeta->imputado;
  while (rec != NULL) {
    if (strcmp(rut,rec->imputado->rut) == 0) {
      return rec->imputado;
    }
    rec = rec->sig;
  }
  return NULL;

}

void agregarSentencia(struct CarpetaInvestigativa *carpeta,int *correctamente) {
  char rut[RUT];
  struct Imputado *imputado;
  int opcion;
  do {
    printf("Ingrese El Rut del Imputado:\n");
    fgets(rut, RUT, stdin);
    rut[strcspn(rut, "\n")] = 0;
    imputado = buscarImputado(carpeta, rut);
    if (imputado == NULL) {
      printError(IMPUTADO);
      ingresarOpcion(&opcion);
      if (opcion == 0) {
        (*correctamente) = 0;
        return;
      }
    }else {
      break;
    }
  }while (1);

  printf("Indique el tipo De Sentencia: (0 = Condenatoria, 1 = Absolutoria)\n");
  do {
    ingresarOpcion(&opcion);
    if (opcion != 0  && opcion != 1) {
      printf("Ingrese una opcion valida\n");
    }
  }while (opcion != 0 && opcion != 1);
  imputado->tipoSentencia = opcion;
  printf("\n\nDescriba la Sentencia\n");
  fgets(imputado->descripcionSentencia, TEXTO, stdin);
  (*correctamente) = 1;

}

int anidarDiligencia(struct CarpetaInvestigativa *carpeta,struct Diligencia *diligencia) {
  struct NodoDiligencias *nodo,*rec;
  nodo = (struct NodoDiligencias*)malloc(sizeof(struct NodoDiligencias));
  if (nodo == NULL) {
    return 0;
  }
  nodo->diligencia = diligencia;
  nodo->sig = NULL;
  if (carpeta->diligencias == NULL) {
    carpeta->diligencias = nodo;
    return 1;
  }else {
    rec = carpeta->diligencias;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nodo;

    return 1;
  }
}

void agregarDiligenciaJuez(struct CarpetaInvestigativa *carpeta,int *correctamente) {
  struct Diligencia *diligencia;
  char *fecha;
  diligencia = (struct Diligencia*)malloc(sizeof(struct Diligencia));
  diligencia->OrigenDiligencia = 3;

  printf("Ingrese el tipo de Diligencia: (Ingrese texto:)\n");
  fgets(diligencia->tipoDiligencia, TEXTO, stdin);

  printf("Ingrese Descripcion de Diligencia:\n");
  fgets(diligencia-> descripcionDiligencia, TEXTO, stdin);

  printf("Ingrese Fecha de Diligencia: (Formato:20/04/2024)\n");
  fecha = ingresarFecha();
  if (fecha == NULL) {
    (*correctamente) = 0;
    return;
  }
  strcpy(diligencia->fechaDiligencia, fecha);

  do {
    printf("\nIngrese Urgencia: (1 = Baja, 2 = Media, 3 = Alta)\n");
    scanf("%d", &diligencia->urgencia);
  }while (diligencia->urgencia>3 && diligencia->urgencia<1);

  do {
    printf("\nIngrese Impacto para la Investigacion: (1 = Baja, 2 = Media, 3 = Alta)\n");
    scanf("%d", &diligencia->impacto);
  }while (diligencia->impacto>3 && diligencia->impacto<1);

  if (!anidarDiligencia(carpeta,diligencia)) {
    printf("Error al Anidar Diligencia");
    (*correctamente) = 0;
  }else {
    (*correctamente) = 1;
  }
}

void agregarMedidaCautelar(struct CarpetaInvestigativa *carpeta,int *correctamente) {

  struct Imputado *imputado;
  char rut[RUT];
  int opcion;

  do {
    printf("Ingrese El Rut del Imputado:\n");
    fgets(rut, RUT, stdin);
    rut[strcspn(rut, "\n")] = 0;
    imputado = buscarImputado(carpeta, rut);
    if (imputado == NULL) {
      printError(IMPUTADO);
      ingresarOpcion(&opcion);
      if (opcion == 0) {
        (*correctamente) = 0;
        return;
      }
    }
  }while (imputado == NULL);

  printf("Ingrese Las medidas Cautelares:\n");
  limpiarBuffer();
  fgets(imputado->medidasCautelares, TEXTO, stdin);
  if (strchr(imputado->medidasCautelares, '\n') == NULL) {
    printf("Advertencia:El texto es muy largo, este pudo haber sido cortado.\n");
    limpiarBuffer();
  }
  (*correctamente) = 1;
}

int eliminarImputado(struct CarpetaInvestigativa *carpeta, struct Imputado *imputado) {
  struct NodoImputados *rec;
  /*Ya se verifica que el carpeta->imputado existe en la funcion Buscar Imputado*/
  rec = carpeta->imputado;
  /*Si el Nodo a Eliminar es el Head o el primer Nodo*/
  if (carpeta -> imputado-> imputado == imputado) {
    carpeta -> imputado = carpeta -> imputado -> sig;
    return 1;
  }
  else {
    /*Recorremos hasta encontrar al imputado*/
    while (rec-> sig -> imputado != imputado || rec->sig == NULL) {
      rec = rec-> sig;
    }
    if (rec->sig == NULL) {
      return 0;
    }
    rec -> sig = rec-> sig-> sig;
    return 1;
  }
}

void sobreseimiento(struct CarpetaInvestigativa *carpeta, int *correctamente) {
  char rut[RUT];
  int opcion;
  struct Imputado *imputado;

  do {
    printf("Ingrese El Rut del Imputado:\n");
    fgets(rut, RUT, stdin);
    rut[strcspn(rut, "\n")] = 0;
    imputado = buscarImputado(carpeta, rut);
    if (imputado == NULL) {
      printError(IMPUTADO);
      ingresarOpcion(&opcion);
      if (opcion != 1) {
        (*correctamente) = 0;
      }
    }else {
      break;
    }
  }while (1);
  if (!eliminarImputado(carpeta, imputado)) {
    printf("Error al eliminar Imputado\n\n");
    (*correctamente) = 0;
  }else {
    printf("Se Ha desenlazado Correctamente al Imputado\n\n");
    (*correctamente) = 1;
  }

}

int accionResolucion(struct CarpetaInvestigativa *carpeta,int tipoCausa) {
  int correctamente;
  switch (tipoCausa) {
    case 0: agregarSentencia(carpeta,&correctamente); break;
    case 1: agregarDiligenciaJuez(carpeta,&correctamente); break;
    case 2: agregarMedidaCautelar(carpeta,&correctamente); break;
    case 3: sobreseimiento(carpeta,&correctamente); break;
    default: return 0;
  }
  return correctamente;

}

/*---------FUNCION AGREGAR RESOLUCION----------------*/
void anidarResolusion(struct CarpetaInvestigativa *carpeta,struct Resolucion *nueva) {
  struct NodoResoluciones *rec;
  struct NodoResoluciones *nodo;
  nodo = (struct NodoResoluciones*)malloc(sizeof(struct NodoResoluciones));

  nodo->resolucion = nueva;
  nodo->sig = NULL;

  if (carpeta->resoluciones == NULL) {
    carpeta->resoluciones = nodo;
  } else {
    rec = carpeta->resoluciones;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nodo;
  }
}

void agregarResolucion(struct Fiscal *fiscal) {
  struct Resolucion *nuevaResolucion;
  struct CarpetaInvestigativa *carpeta;
  char *fecha;
  char *rucTemporal;
  char rucCarpeta[RUC];
  int correcto;
  limpiarPantalla();

  if (fiscal -> carpetas == NULL) {
    printf("NO EXISTE NINGUNA CARPETA");
    return;
  }

  do {
    printf("Ingrese un RUC: ");
    rucTemporal = ingresarRuc();
    if (rucTemporal == NULL)
      return;
    strcpy(rucCarpeta, rucTemporal);
    carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
    if (carpeta == NULL) {
      printf("No existe una carpeta con ese RUC INTENTE DE NUEVO\n\n");
    }
    else
      break;
  }while(1);

  nuevaResolucion = (struct Resolucion*)malloc(sizeof(struct Resolucion));
  limpiarPantalla();

  do {
    printf("\nIngrese el tipo de resolución:\n");/*Tengo que agregar codigo para cada una de las opciones para agregarlo por sepradao a la carpeta*/
    printf("0. Sentencia\n");
    printf("1. Autorizacion para Diligancias\n");
    printf("2. Medida Cautelar\n");
    printf("3. Sobreseimiento\n");
    scanf("%d", &nuevaResolucion->tipoResolucion);
    limpiarPantalla();
    limpiarBuffer();
  }while (nuevaResolucion->tipoResolucion <= 0 && nuevaResolucion->tipoResolucion >= 3);


  correcto = accionResolucion(carpeta,nuevaResolucion->tipoResolucion);
  if (correcto == 0) {
    return;
  }
  /*Si origen == 0 la resolucion fue emitida por el Juez de Garantia
   * Si origen == 1 la resolucion fue emitida por el tribunal de Juicio Oral
   */
  printf("Ingrese el Origen de la Resolucion\n");
  printf("0. Resolucion emitida por Juez de Garantía\n");
  printf("1. Resolucion emitida por Tribunal De jucio Oral\n");
  scanf("%d", &nuevaResolucion-> origenResolucion);
  limpiarBuffer();

  printf("Ingrese la Descripcion de su Resolucion:\n");
  fgets(nuevaResolucion->descripcion, TEXTO, stdin);
  nuevaResolucion->descripcion[strcspn(nuevaResolucion->descripcion, "\n")] = 0;

  printf("Ingrese una fecha: Formato:(12/04/2025)\n");
  fecha = ingresarFecha();
  if (fecha == NULL) return;
  strcpy(nuevaResolucion->fecha, fecha);
  anidarResolusion(carpeta,nuevaResolucion);

  printf("Resolucion agregada Correctamente\n");
  esperarEnter();
}
/*-------------------------FUNCION AGREGAR IMPUTADO-----------------------------------------*/
void agregarImputado(struct Fiscal *fiscal) {
  struct NodoImputados *nuevoNodo;
  struct Imputado *nuevoImputado;
  struct NodoImputados *recImputado;
  struct NodoCausas *recCausas;
  struct NodoCausas *nodoCausas;
  struct Causa *nuevaCausa;
  struct CarpetaInvestigativa *carpeta;
  int opcion;
  int causas;
  char descripcion[TEXTO];
  char *rucTemporal;
  char rucCarpeta[RUC];
  limpiarPantalla();

  if (fiscal->carpetas == NULL) {
    printf("No existen Carpetas");
    return;
  }

  do {
    printf("Ingrese RUC de la carpeta(123456789-2024)\n");
    rucTemporal = ingresarRuc();
    if (rucTemporal == NULL)
      return;
    strcpy(rucCarpeta, rucTemporal);
    carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
    if (carpeta == NULL) {
      printf("No existe una carpeta con ese RUC INTENTE DENUEVO\n\n");
    }
    else
      break;
  }while(1);

  /*Asignacion de memoria para las variables a las que se les ingresaran datos*/
  nuevoImputado = (struct Imputado*)malloc(sizeof(struct Imputado));
  nuevoNodo = (struct NodoImputados*)malloc(sizeof(struct NodoImputados));


  limpiarBuffer();
  printf("Ingrese el RUT del imputado(123456789-8)\n");
  fgets(nuevoImputado-> rut, RUT, stdin);
  nuevoImputado->rut[strcspn(nuevoImputado->rut, "\n")] = 0;

  limpiarBuffer();
  printf("Ingrese las Medidas Cautelares (MAX 1000 caracteres)\n");
  fgets(descripcion, TEXTO, stdin);
  descripcion[strcspn(descripcion, "\n")] = 0;
  strcpy(nuevoImputado->medidasCautelares, descripcion);

  do {

    nuevaCausa = (struct Causa*)malloc(sizeof(struct Causa));
    nodoCausas = (struct NodoCausas*)malloc(sizeof(struct NodoCausas));
    recCausas = nuevoImputado-> causas;
    printf("Ingrese la Causa (Solamente un numero) \n");
    printf("0. Crimen (Infraccion grave) \n");
    printf("1. Delito Simple (Ejemplo: Hurto, estafan) \n");
    printf("2. Falta (Ejemplo: Infracciones de transito)\n");
    scanf("%d", &causas);
    limpiarBuffer();

    printf("Ingrese la descripcion de su causa \n");
    fgets(descripcion, TEXTO, stdin);
    descripcion[strcspn(descripcion, "\n")] = 0;
    strcpy(nuevaCausa->descripcionCausa, descripcion);


    nuevaCausa -> tipoCausa = causas;


    nodoCausas -> causa= nuevaCausa;
    nodoCausas -> sig= NULL;

    if (nuevoImputado-> causas == NULL) {
      nuevoImputado -> causas = nodoCausas;
    }
    else {
      while (recCausas -> sig != NULL) {
        recCausas = recCausas -> sig;
      }
      recCausas -> sig = nodoCausas;
    }

    printf("Ingrese algun numero DISTINTO de 0 si desea agregar alguna otra causa \n");
    scanf("%d", &opcion);
    limpiarBuffer();

    limpiarPantalla();
  }while (opcion != 0);

  nuevoNodo -> imputado = nuevoImputado;
  nuevoNodo -> sig = NULL;

  recImputado = carpeta -> imputado;

  if (carpeta -> imputado == NULL) {
    carpeta -> imputado = nuevoNodo;
  }
  else {
    while (recImputado -> sig != NULL) {
      recImputado = recImputado->sig;
    }
    recImputado -> sig = nuevoNodo;
  }

  printf("El imputado se agrego correctamente.\n");
  esperarEnter();
}

/*--------------------FUNCION AGREGAR PRUEBA----------------------*/
int agregarPrueba(struct Fiscal *fiscal, char *rucCarpeta, struct Prueba *datosPrueba) {
  struct CarpetaInvestigativa *carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  struct NodoPruebas *nuevoNodo;
  struct NodoPruebas *rec;

  if (carpeta == NULL) {
    return CARPETA;
  }

  nuevoNodo = (struct NodoPruebas*)malloc(sizeof(struct NodoPruebas));


  nuevoNodo->prueba = datosPrueba;
  nuevoNodo->sig = NULL;

  if (carpeta->pruebas == NULL) {
    carpeta->pruebas = nuevoNodo;
  } else {
    rec = carpeta->pruebas;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nuevoNodo;
  }
  return 0;
}
void listarCarpetasRecursivo(struct arbolCarpetas *raiz) {
  struct CarpetaInvestigativa *carpeta;
  struct NodoImputados *recImputado = NULL;
  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarCarpetasRecursivo(raiz-> izq);
  carpeta = raiz -> carpetaInvestigativa;
  printf("--------------------------------------------------\n");
  printf("RUC: %s\n", carpeta->ruc);
  printf("Estado: ");
  switch (carpeta->estadoCarpeta) {
    case 0: printf("En investigación\n"); break;
    case 1: printf("Juicio Oral\n"); break;
    case 2: printf("Archivada\n"); break;
    case 3: printf("Cerrada\n"); break;
    default: printf("Desconocido\n"); break;
  }

  /*se recorre la lista de imputados para mostrar cada imputado de la carpeta*/
  recImputado = carpeta -> imputado;
  if (recImputado != NULL) {
    while (recImputado != NULL) {
      printf("RUT Imputado: %s\n", recImputado->imputado->rut);
      recImputado = recImputado -> sig;
    }
  }
  else
    printf("Sin imputado asignado\n");

  /* 3. Recorre subarbol derecho*/
  listarCarpetasRecursivo(raiz->der);
}


void listarCarpetas(struct Fiscal *fiscal) {
  limpiarPantalla();
  printf("=============== LISTADO DE CARPETAS =============");
  if (fiscal-> carpetas == NULL) {
    printf("NO HAY CARPETAS REGISTRADAS");
    return;
  }
  /*el listar Carpetas solo se puede hacer recursivo*/
  listarCarpetasRecursivo(fiscal-> carpetas);

  esperarEnter();
}
/*-------------------------*/

/*----------Funciones MenuCarpeta---------*/



/*--------Función recorrerRut--------*/

struct Imputado *buscarImputadoPorRUT(struct arbolCarpetas *nodo, char *rut) {
  struct NodoImputados *actual;
  struct Imputado *encontrado;

  if (nodo == NULL)
    return NULL;

  actual = nodo->carpetaInvestigativa->imputado;
  while (actual != NULL) {
    if (strcmp(actual->imputado->rut, rut) == 0) {
      return actual->imputado;
    }
    actual = actual->sig;
  }

  encontrado = buscarImputadoPorRUT(nodo->izq, rut);
  if (encontrado != NULL)
    return encontrado;

  return buscarImputadoPorRUT(nodo->der, rut);
}



void buscarImputadoPorRut(struct Fiscal *fiscal) {
  char rut[RUT];
  struct Imputado *imputado;

  if (fiscal->carpetas == NULL) {
    printf("No hay carpetas registradas.\n");
    return;
  }

  limpiarPantalla();
  printf("=== BUSCAR IMPUTADO POR RUT ===\n");
  printf("Ingrese el RUT del imputado: ");
  fgets(rut, RUT, stdin);
  rut[strcspn(rut, "\n")] = 0;

  imputado = buscarImputadoPorRUT(fiscal->carpetas, rut);

  if (imputado == NULL) {
    printf("No se encontro un imputado con ese RUT.\n");
  } else {
    printf("\n====== IMPUTADO ENCONTRADO ======\n");
    printf("RUT: %s\n", imputado->rut);
    printf("Medidas cautelares: %s\n", imputado->medidasCautelares);
    printf("Tipo de sentencia: %d\n", imputado->tipoSentencia);
    printf("Descripcion de la sentencia: %s\n", imputado->descripcionSentencia);
  }

  esperarEnter();
}



/*---------Funcion para modificar al imputado-------------*/

int modificarImputadoInterno(struct Imputado *imputado, int opcion, int nuevoTipo, char *nuevaDescripcion) {
  int huboCambios;

  huboCambios = 0;

  if (opcion == 1) {
    imputado->tipoSentencia = nuevoTipo;
    huboCambios = 1;
  } else if (opcion == 2) {
    strcpy(imputado->descripcionSentencia, nuevaDescripcion);
    huboCambios = 1;
  }

  return huboCambios;
}

void modificarImputado(struct Fiscal *fiscal) {
  char rutBusqueda[RUT];
  struct arbolCarpetas *nodoArbol;
  struct NodoImputados *actual;
  int encontrado;
  int opcion;
  int nuevoTipo;
  char nuevaDescripcion[TEXTO];
  int resultado;

  if (fiscal->carpetas == NULL) {
    printf("No hay carpetas registradas.\n");
    return;
  }

  limpiarPantalla();
  printf("=== MODIFICAR IMPUTADO ===\n");
  printf("Ingrese el RUT del imputado: ");
  fgets(rutBusqueda, RUT, stdin);
  rutBusqueda[strcspn(rutBusqueda, "\n")] = 0;

  nodoArbol = fiscal->carpetas;
  encontrado = 0;

  while (nodoArbol != NULL) {
    actual = nodoArbol->carpetaInvestigativa->imputado;
    while (actual != NULL) {
      if (strcmp(actual->imputado->rut, rutBusqueda) == 0) {
        encontrado++;

        printf("\n====== Imputado Encontrado ======\n");
        printf("RUT: %s\n", actual->imputado->rut);
        printf("Medidas actuales: %s\n", actual->imputado->medidasCautelares);
        printf("Tipo de sentencia actual: %d\n", actual->imputado->tipoSentencia);
        printf("Descripcion sentencia actual: %s\n", actual->imputado->descripcionSentencia);

        printf("\nSeleccione que desea modificar:\n");
        printf("1. Tipo de Sentencia (0: Condenatoria, 1: Absolutoria)\n");
        printf("2. Descripcion de la Sentencia\n");
        printf("3. Cancelar\n");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
          case 1:
            printf("Ingrese nuevo tipo de sentencia (0: Condenatoria, 1: Absolutoria): ");
            scanf("%d", &nuevoTipo);
            limpiarBuffer();
            resultado = modificarImputadoInterno(actual->imputado, opcion, nuevoTipo, nuevaDescripcion);
            if (resultado == 1) {
              printf("Tipo de sentencia actualizado correctamente.\n");
            } else {
              printf("No se realizaron cambios.\n");
            }
            break;

          case 2:
            printf("Ingrese nueva descripcion de sentencia: ");
            fgets(nuevaDescripcion, TEXTO, stdin);
            nuevaDescripcion[strcspn(nuevaDescripcion, "\n")] = 0;
            resultado = modificarImputadoInterno(actual->imputado, opcion, nuevoTipo, nuevaDescripcion);
            if (resultado == 1) {
              printf("Descripcion de sentencia actualizada correctamente.\n");
            } else {
              printf("No se realizaron cambios.\n");
            }
            break;

          case 3:
            printf("Operacion cancelada.\n");
            return;

          default:
            printf("Opcion invalida.\n");
        }

        esperarEnter();
        return;
      }
      actual = actual->sig;
    }

    if (strcmp(rutBusqueda, nodoArbol->carpetaInvestigativa->ruc) < 0) {
      nodoArbol = nodoArbol->izq;
    } else {
      nodoArbol = nodoArbol->der;
    }
  }

  if (encontrado == 0) {
    printf("No se encontro un imputado con el RUT ingresado.\n");
    esperarEnter();
  }
}


/*-----------funcion para mostrar todos los imputados---------------*/


struct NodoImputados *recolectarImputados(struct arbolCarpetas *nodoArbol) {
  struct NodoImputados *lista = NULL;
  struct NodoImputados *actual;
  struct NodoImputados *nuevo;
  struct NodoImputados *nodoImputado;

  if (nodoArbol == NULL) {
    return NULL;
  }

  lista = recolectarImputados(nodoArbol->izq);

  nodoImputado = nodoArbol->carpetaInvestigativa->imputado;
  while (nodoImputado != NULL) {
    nuevo = (struct NodoImputados *)malloc(sizeof(struct NodoImputados));
    nuevo->imputado = nodoImputado->imputado;
    nuevo->sig = NULL;

    if (lista == NULL) {
      lista = nuevo;
    } else {
      actual = lista;
      while (actual->sig != NULL) {
        actual = actual->sig;
      }
      actual->sig = nuevo;
    }

    nodoImputado = nodoImputado->sig;
  }

  actual = lista;
  if (actual == NULL) {
    lista = recolectarImputados(nodoArbol->der);
  } else {
    while (actual->sig != NULL) {
      actual = actual->sig;
    }
    actual->sig = recolectarImputados(nodoArbol->der);
  }

  return lista;
}


void mostrarTodosImputados(struct Fiscal *fiscal) {
  struct NodoImputados *lista;
  struct NodoImputados *actual;
  struct NodoCausas *causa;
  int numImputado;
  int numCausa;

  if (fiscal->carpetas == NULL) {
    printf("No hay carpetas registradas.\n");
    esperarEnter();
    return;
  }

  limpiarPantalla();
  printf("=== LISTADO DE IMPUTADOS DEL FISCAL ===\n");
  printf("========================================\n");

  lista = recolectarImputados(fiscal->carpetas);
  actual = lista;
  numImputado = 1;

  while (actual != NULL) {
    printf("\n==== IMPUTADO %d ====\n", numImputado);
    printf("RUT: %s\n", actual->imputado->rut);
    printf("Medidas Cautelares: %s\n", actual->imputado->medidasCautelares);
    printf("Tipo Sentencia: %d\n", actual->imputado->tipoSentencia);
    printf("Descripcion Sentencia: %s\n", actual->imputado->descripcionSentencia);

    causa = actual->imputado->causas;
    numCausa = 1;
    while (causa != NULL) {
      printf("  Causa %d: ", numCausa);
      if (causa->causa->tipoCausa == 0) {
        printf("Crimen\n");
      } else if (causa->causa->tipoCausa == 1) {
        printf("Delito Simple\n");
      } else if (causa->causa->tipoCausa == 2) {
        printf("Falta\n");
      } else {
        printf("Desconocida\n");
      }
      printf("    Descripción: %s\n", causa->causa->descripcionCausa);
      numCausa++;
      causa = causa->sig;
    }

    numImputado++;
    actual = actual->sig;
  }

  esperarEnter();
}

/*-----------------------------------------------------------------------*/

/*--------Funciones MenuDiligencias------------------------*/

/*------funcion mostrar diligencias-------*/

void mostrarDiligencias(struct Fiscal *fiscal) { /*no cambiar xq es procedimiento*/
  char rucCarpeta[RUC];
  struct CarpetaInvestigativa *carpeta;
  struct NodoDiligencias *head;
  int numDiligencia = 1;

  limpiarBuffer();
  printf("Ingrese el RUC de la Carpeta Investigativa: ");
  fgets(rucCarpeta, RUC, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = '\0';

  carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("No se encontro la carpeta.\n");
    return;
  }

  if (carpeta->diligencias == NULL) {
    printf("La carpeta no tiene diligencias registradas.\n");
    return;
  }

  printf("\n=== DILIGENCIAS REGISTRADAS ===\n");
  head = carpeta->diligencias;
  while (head != NULL) {
    printf("====== DILIGENCIA %d ======\n", numDiligencia++);
    printf("- Urgencia: %d\n", head->diligencia->urgencia);
    printf("  Origen: ");
    switch (head->diligencia->OrigenDiligencia) {
      case 0: printf("Fiscal\n"); break;
      case 1: printf("Victima\n"); break;
      case 2: printf("Imputado\n"); break;
      case 3: printf("Juez\n");break;
      default: printf("Desconocido\n"); break;
    }
    printf("  Descripcion: %s\n", head->diligencia->descripcionDiligencia);
    printf("-----------------------------\n");
    head = head->sig;
  }
}


/*-----------mostrar y ordenar diligencias por prioridad---------*/

struct NodoDiligencias *ordenarDiligenciasPorPrioridadInterior(struct NodoDiligencias* head) {
  struct NodoDiligencias *ordenada = NULL;
  struct NodoDiligencias *actual = head;
  struct NodoDiligencias *siguiente;
  struct NodoDiligencias *temp;

  while (actual != NULL) {
    siguiente = actual->sig;
    actual->sig = NULL;

    if (ordenada == NULL || actual->diligencia->urgencia > ordenada->diligencia->urgencia) {
      actual->sig = ordenada;
      ordenada = actual;
    } else {
      temp = ordenada;
      while (temp->sig != NULL && temp->sig->diligencia->urgencia >= actual->diligencia->urgencia) {
        temp = temp->sig;
      }
      actual->sig = temp->sig;
      temp->sig = actual;
    }

    actual = siguiente;
  }

  return ordenada;
}


void mostrarDiligenciasOrdenadas(struct Fiscal *fiscal) {
  struct CarpetaInvestigativa *carpeta;
  struct NodoDiligencias *head;
  struct NodoDiligencias *ordenada;
  char rucCarpeta[RUC];
  int numDiligencia = 1;

  limpiarBuffer();
  printf("Ingrese el RUC de la Carpeta Investigativa: ");
  fgets(rucCarpeta, RUC, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = '\0';

  carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("No se encontro la carpeta.\n");
    return;
  }

  if (carpeta->diligencias == NULL) {
    printf("La carpeta no tiene diligencias registradas.\n");
    return;
  }

  ordenada = ordenarDiligenciasPorPrioridadInterior(carpeta->diligencias);

  printf("=== Lista de Diligencias Ordenadas por Prioridad ===\n");
  head = ordenada;

  while (head != NULL) {
    printf("====== DILIGENCIA %d ======\n", numDiligencia);
    printf("- Urgencia: %d\n", head->diligencia->urgencia);
    printf("  Descripcion: %s\n\n", head->diligencia->descripcionDiligencia);
    head = head->sig;
    numDiligencia++;
  }
}


/*-----------Función listarDiligencias----------------*/

void listarDiligenciasPendientes(struct Fiscal *fiscal) {
  struct CarpetaInvestigativa *carpeta;
  struct NodoDiligencias *actual;
  char rucCarpeta[RUC];
  int pendientes = 0;
  int numDiligencia = 1;

  limpiarPantalla();

  if (fiscal->carpetas == NULL) {
    printf("NO EXISTEN CARPETAS\n");
    return;
  }

  printf("Ingrese el RUC de la carpeta: ");
  fgets(rucCarpeta, RUC, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = 0;

  carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("Carpeta no encontrada.\n");
    return;
  }

  if(carpeta->diligencias == NULL) {
    printf("Esta carpeta no tiene diligencias registradas.\n");
    return;
  }

  printf("====== DILIGENCIAS PENDIENTES =======\n");

  actual = carpeta->diligencias;
  while (actual!=NULL) {
    if (actual->diligencia->aprobacion == 0) {
      pendientes++;
      printf("--------------------------------------------------\n");
      printf("====== DILIGENCIA %d ======\n", numDiligencia++);
      printf("Origen: ");
      switch (actual->diligencia->OrigenDiligencia) {
        case 0: printf("Fiscal\n"); break;
        case 1: printf("Victima\n"); break;
        case 2: printf("Imputado\n"); break;
        case 3: printf("Juez\n"); break;
        default: printf("Desconocido\n"); break;
      }

      printf("Tipo: %s\n", actual->diligencia->tipoDiligencia);
      printf("Descripcion: %s\n", actual->diligencia->descripcionDiligencia);
      printf("Fecha: %s\n", actual->diligencia->fechaDiligencia);
      printf("Urgencia: %d | Impacto: %d\n", actual->diligencia->urgencia, actual->diligencia->impacto);
      printf("Estado: Rechazada\n");
    }
    actual = actual->sig;
  }

  if (pendientes == 0) {
    printf("No hay diligencias pendientes en esta carpeta.\n");
  }
  esperarEnter();

}


/*----------------------------------------------------------------*/

/*-----------funcion listarCausas---------------*/


void ListarCausas(struct Fiscal *fiscal) {
  /*ListarCausas es un procedimiento. Lo único que hace es imprimir las Causas encontradas en denuncias.*/
  int i;
  struct NodoCausas *rec=NULL;
  struct NodoDenuncias *denuncias=NULL;
  struct NodoDenuncias *headdenuncias=NULL;
  limpiarPantalla();
  /*limpiarPantalla es un procedimiento que salta 20 líneas, para limpiar la pantalla.*/
  printf("\n--- Causas de Denuncias ---\n\n\n");
  denuncias=fiscal->denuncias;
  headdenuncias=denuncias;

  if (denuncias != NULL) {
    do {
      /*Si el head del nodo denuncias no está vacío, se recorre la lista circular hasta encontrarse a si mismo, sin contar la primera vez*/
      if (denuncias->denuncia!=NULL) {
        /*Si los datos de la denuncia en la que estamos no están vacíos, mostramos su RUC.*/
        rec=denuncias->denuncia->causas;
        i=1;
        if (denuncias->denuncia->ruc==NULL) {
          printf("RUC: NO ENCONTRADO\n\n");
        }
        else {
          printf("RUC: %s\n\n",denuncias->denuncia->ruc);
        }
        while (rec!=NULL) {
          /*Y mostramos los datos de cada una de sus causas.*/
          if (rec->causa!=NULL && rec->causa->tipoCausa==0) {
            printf("CAUSA %d: Crimen\n",i);
          }
          else if(rec->causa!=NULL && rec->causa->tipoCausa==1) {
            printf("CAUSA %d: Delito Simple\n",i);
          }
          else if(rec->causa!=NULL && rec->causa->tipoCausa==2) {
            printf("CAUSA %d: Falta\n",i);
          }
          else{
            printf("CAUSA %d: NO SE PRESENTA UNA CAUSA\n",i);
          }
          if (rec->causa!=NULL && rec->causa->descripcionCausa!=NULL) {
            printf("Descripcion de la Causa %d: %s\n\n",i,rec->causa->descripcionCausa);
          }
          else {
            printf("Descripcion de la Causa %d: NO HAY.\n\n",i);
          }
          rec=rec->sig;
          i++;
        }
      }
      denuncias=denuncias->sig;
    }while (denuncias!=NULL && denuncias!=headdenuncias);
  }

  esperarEnter();
}

void CausaBuscarRUT(struct arbolCarpetas *nodoArbol, char *rutBuscado) {
  /*Procedimiento Recursivo que Busca a un Imputado dado un RUT e imprime sus Causas*/
  struct NodoImputados *actual;
  struct NodoCausas *rec;
  int i=1;
  if (nodoArbol == NULL || nodoArbol->carpetaInvestigativa == NULL) {
    return;
  }
  /*Se va recorriendo el Árbol de carpetas de modo IN-ORDER*/
  CausaBuscarRUT(nodoArbol->izq, rutBuscado);

  actual = nodoArbol->carpetaInvestigativa->imputado;
  while (actual!=NULL) {
    /*Se recorren todos los imputados de cada nodo del árbol hasta encontrar el que buscamos.*/
    if (strcmp(actual->imputado->rut, rutBuscado) == 0) {
      /*Al encontrarlo se muestra información básica acerca del imputado y todas sus causas*/
      printf("\n--- Imputado Encontrado ---\n");
      printf("RUT: %s\n", actual->imputado->rut);
      rec=actual->imputado->causas;
      if (rec==NULL) printf("NO SE ENCONTRARON CAUSAS \n\n");
      while (rec!=NULL) {
        if (rec->causa!=NULL && rec->causa->tipoCausa==0) {
          printf("CAUSA %d: Crimen\n",i);
        }
        else if(rec->causa!=NULL && rec->causa->tipoCausa==1) {
          printf("CAUSA %d: Delito Simple\n",i);
        }
        else if(rec->causa!=NULL && rec->causa->tipoCausa==2) {
          printf("CAUSA %d: Falta\n",i);
        }
        else{
          printf("CAUSA %d: NO SE PRESENTA UNA CAUSA",i);
        }
        if (rec->causa!=NULL && rec->causa->descripcionCausa!=NULL) {
          printf("Descripcion de la Causa %d: %s\n",i,rec->causa->descripcionCausa);
        }
        else {
          printf("Descripcion de la Causa %d: NO HAY.",i);
        }
        rec=rec->sig;
        i++;
      }
      break;
    }
    actual = actual->sig;
  }
  CausaBuscarRUT(nodoArbol->der, rutBuscado);
}

void BuscarCausasPorImputado(struct Fiscal *fiscal, char *rut) {
  /*BuscarCausasPorImputado es un procedimiento que le pide al usuario un RUT y lo usa para imprimir las Causas del Imputado con ese RUT usando el procedimiento CausaBuscarRUT*/

  if(fiscal->carpetas == NULL) {
    printf("No hay carpetas registradas.\n");
    return;
  }

  CausaBuscarRUT(fiscal->carpetas, rut);
  esperarEnter();
}

void BuscarCausasDenuncia(struct Fiscal *fiscal, char *ruc) {
  /*BuscarCausasDenuncia es un procedimiento que imprime las Causas de la denuncia con un RUC*/
  int i;
  struct NodoCausas *rec=NULL;
  struct NodoDenuncias *denuncias=NULL, *headDenuncias=NULL;

  denuncias=fiscal->denuncias;
  headDenuncias=denuncias;

  do {
    if (denuncias->denuncia!=NULL && denuncias->denuncia->ruc!=NULL && strcmp(denuncias->denuncia->ruc,ruc)==0) {
      /*Se recorren las denuncias. Una vez encontrada la buscada, se imprimen sus Causas.*/
      rec=denuncias->denuncia->causas;
      i=1;
      printf("RUC: %s\n",denuncias->denuncia->ruc);
      while (rec!=NULL) {
        if (rec->causa!=NULL && rec->causa->tipoCausa==0) {
          printf("CAUSA %d: Crimen\n",i);
        }
        else if(rec->causa!=NULL && rec->causa->tipoCausa==1) {
          printf("CAUSA %d: Delito Simple\n",i);
        }
        else if(rec->causa!=NULL && rec->causa->tipoCausa==2) {
          printf("CAUSA %d: Falta\n",i);
        }
        else{
          printf("CAUSA %d: NO SE PRESENTA UNA CAUSA",i);
        }
        if (rec->causa!=NULL && rec->causa->descripcionCausa!=NULL) {
          printf("Descripcion de la Causa %d: %s\n",i,rec->causa->descripcionCausa);
        }
        else {
          printf("Descripcion de la Causa %d: NO HAY.",i);
        }
        rec=rec->sig;
        i++;
      }
      break;
    }
    denuncias=denuncias->sig;
  }while (denuncias!=headDenuncias);

  esperarEnter();
}

void agregarCausas(struct Fiscal *fiscal) {
  /*agregarCausas es un procedimiento que le pide al usuario un RUC y le deja añadir Causas en la denuncia que tenga ese RUC*/
  int opcion;
  char *rucTemp;
  char rucBusqueda[RUC];
  struct Denuncia *denunciaEncontrada;

  /*limpiarPantalla es un procedimiento que salta 20 líneas, para limpiar la pantalla.*/
  limpiarPantalla();

  if (fiscal->denuncias== NULL) {
    printf("No hay denuncias en el Sistema");
    return;
  }

  printf("Agregar Causas: \n\n");
  do {
    printf("Ingrese el RUC: ");
    rucTemp = ingresarRuc();
    if (rucTemp == NULL) {
      return; /*Si retorna NUll el usuario quiere volver al menu Principal*/
    }
    strcpy(rucBusqueda, rucTemp);
    denunciaEncontrada = BUSCARDENUNCIA(fiscal, rucBusqueda);


    if (denunciaEncontrada == NULL) {
      printError(DENUNCIA);
      ingresarOpcion(&opcion);
      if (opcion != 1) {
        return; /* Salir de la función si el usuario elige volver*/
      }
    }
  }while (denunciaEncontrada == NULL);

  AGREGARCAUSA(denunciaEncontrada);

  while (1) {

    printf("Desea Agregar otra Causa: \n");
    printf("0: Agregar otra Causa \n");
    printf("Cualquier otra numero: Volver Al Menu Principal  \n");
    ingresarOpcion(&opcion);
    if (opcion == 0) {
      AGREGARCAUSA(denunciaEncontrada);
    }else
      return;
  }
}

void MODIFICARCAUSA(struct NodoCausas *rec) {
  /*MODIFICARCAUSA es un sub-procedimiento usado en ModificarCausa*/
  printf("\nIngrese el NUEVO Tipo de Causa:\n");
  printf("0 Si es un Crimen (Infraccion grave como Homicidio)\n");
  printf("1 Si es un Delito Simple (Ejemplo: Hurto o Estafa)\n");
  printf("2 Si es una Falta (Ejemplo: Infracciones de Transito)\n");
  printf("Ingrese un numero: ");
  scanf("%d", &rec->causa->tipoCausa);
  limpiarBuffer();

  printf("Ingrese la descripcion de su Denuncia\n");
  fgets(rec->causa->descripcionCausa, TEXTO, stdin);
}

void ModificarCausa(struct Denuncia *denunciaEncontrada) {
  /*ModificarCausa es un procedimiento que le pide al usuario un RUC y le muestra al usuario todas las Causas de la denuncia con ese RUC, para que pueda modificar las que guste.*/
  struct NodoCausas *rec;
  int i=0;
  int modificar, seguir=0;

  rec=denunciaEncontrada->causas;

  while (rec!=NULL) {
    i++;
    modificar=0;
    if (rec->causa!=NULL && rec->causa->tipoCausa==0) {
      printf("\nCAUSA %d: Crimen\n",i);
    }
    else if(rec->causa!=NULL && rec->causa->tipoCausa==1) {
      printf("\nCAUSA %d: Delito Simple\n",i);
    }
    else if(rec->causa!=NULL && rec->causa->tipoCausa==2) {
      printf("\nCAUSA %d: Falta\n",i);
    }
    else{
      printf("\nCAUSA %d: NO SE PRESENTA UNA CAUSA\n",i);
    }
    if (rec->causa!=NULL && rec->causa->descripcionCausa!=NULL) {
      printf("Descripcion de la Causa %d: %s\n",i,rec->causa->descripcionCausa);
    }
    else {
      printf("Descripcion de la Causa %d: NO HAY.\n",i);
    }
    printf("\nDesea modificar esta CAUSA?\n");
    printf("Formato:\n");
    printf("1: Si\n");
    printf("2: No\n");
    printf("Ingrese un numero: ");
    scanf("%d", &modificar);
    limpiarBuffer();

    if (modificar==1) {

      MODIFICARCAUSA(rec);

      printf("Desea continuar modificando causas con este RUC?\n\n");
      printf("Formato:\n");
      printf("1: Si\n");
      printf("2: No\n");
      printf("Ingrese un numero: ");
      scanf("%d", &seguir);
      limpiarBuffer();

      if (seguir==2) break;
    }
    rec=rec->sig;
  }
  printf("\n\nSe han acabado las Causas\n");
  esperarEnter();
}


void listarSentenciasRecursivo(struct arbolCarpetas *raiz) {
  /*listarSentenciasRecursivo es un procedimiento recursivo que lista todas las Sentencias*/
  struct CarpetaInvestigativa *carpeta;
  struct NodoImputados *recImputado = NULL;
  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarSentenciasRecursivo(raiz-> izq);
  carpeta = raiz -> carpetaInvestigativa;
  printf("--------------------------------------------------\n");
  printf("RUC: %s\n", carpeta->ruc);

  /*se recorre la lista de imputados para mostrar cada imputado de la carpeta*/
  recImputado = carpeta -> imputado;
  if (recImputado != NULL) {
    while (recImputado != NULL) {
      if (recImputado->imputado!=NULL) {

        if (recImputado->imputado->rut!=NULL) {
          printf("RUT del Imputado: %s\n",recImputado->imputado->rut);
        }
        else {
          printf("RUT del Imputado: NO DISPONIBLE\n");
        }

        if (recImputado->imputado->tipoSentencia==1) {
          printf("Tipo de Sentencia: Absolutoria\n");
        }
        else if (recImputado->imputado->tipoSentencia==0) {
          printf("Tipo de Sentencia: Condenatoria\n");
        }
        else {
          printf("No existe un tipo de sentencia\n");
        }
        if (recImputado->imputado->descripcionSentencia!=NULL) {
          printf("Descripcion de la Sentencia: %s\n\n",recImputado->imputado->descripcionSentencia);
        }
        else {
          printf("No se presenta Descripcion de la Sentencia\n\n");
        }
      }
      recImputado=recImputado->sig;
    }
  }
  else{
  printf("Sin imputados asignados\n");
  }
  /* 3. Recorre subarbol derecho*/
  listarSentenciasRecursivo(raiz->der);
}


void listarSentencias(struct Fiscal *fiscal) {
  /*listarSentencias es un procedimiento que usa el procedimiento recursivo listarSentenciasRecursivo para listar todas las Sentencias*/
  limpiarPantalla();
  printf("=============== LISTADO DE SENTENCIAS =============");
  if (fiscal-> carpetas == NULL) {
    printf("NO HAY SENTENCIAS REGISTRADAS");
    return;
  }
  /*el listar Carpetas solo se puede hacer recursivo*/
  listarSentenciasRecursivo(fiscal-> carpetas);

  esperarEnter();
}

void listarSentenciasPorImputadoRecursivo(struct arbolCarpetas *raiz, char *rut) {
  /*listarSentenciasPorImputadoRecursivo es un procedimiento recursivo que lista la Sentencia de un Imputado según un RUT dado*/
  struct CarpetaInvestigativa *carpeta;
  struct NodoImputados *recImputado = NULL;
  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarSentenciasPorImputadoRecursivo(raiz-> izq, rut);
  carpeta = raiz -> carpetaInvestigativa;
  printf("--------------------------------------------------\n");
  printf("RUC: %s\n", carpeta->ruc);

  /*se recorre la lista de imputados para mostrar cada imputado de la carpeta*/
  recImputado = carpeta -> imputado;
  if (recImputado != NULL) {
    while (recImputado != NULL) {
      if (recImputado->imputado!=NULL && recImputado->imputado->rut!=NULL && strcmp(recImputado->imputado->rut,rut)==0) {
        printf("RUT del Imputado: %s\n",recImputado->imputado->rut);

        if (recImputado->imputado->tipoSentencia==1) {
          printf("Tipo de Sentencia: Absolutoria\n");
        }
        else if (recImputado->imputado->tipoSentencia==0) {
          printf("Tipo de Sentencia: Condenatoria\n");
        }
        else {
          printf("No existe un tipo de sentencia\n");
        }
        if (recImputado->imputado->descripcionSentencia!=NULL) {
          printf("Descripcion de la Sentencia: %s\n\n",recImputado->imputado->descripcionSentencia);
        }
        else {
          printf("No se presenta Descripcion de la Sentencia\n\n");
        }
        break;
      }
      recImputado=recImputado->sig;
    }
  }
  else{
  printf("Sin imputados asignados\n");
  }
  /* 3. Recorre subárbol derecho*/
  listarSentenciasPorImputadoRecursivo(raiz->der, rut);
}


void listarSentenciasPorImputado(struct Fiscal *fiscal, char *rut) {
  /*listarSentenciasPorImputado es un procedimiento que pide un RUT y usa el procedimiento recursivo listarSentenciasPorImputadoRecursivo para listar la Sentencia del Imputado con ese RUT*/
  if (fiscal-> carpetas == NULL) {
    printf("NO HAY SENTENCIAS REGISTRADAS");
    return;
  }
  /*el listar Carpetas solo se puede hacer recursivo*/
  listarSentenciasPorImputadoRecursivo(fiscal-> carpetas,rut);

  esperarEnter();
}

void listarSentenciasPorCausaRecursivo(struct arbolCarpetas *raiz,int tipoCausa) {
  /*listarSentenciasPorCausaRecursivo es un procedimiento recursivo que lista las Sentencias de los Imputados que tengan alguna Causa de tipo especificado*/
  struct CarpetaInvestigativa *carpeta;
  struct NodoImputados *recImputado = NULL;
  struct NodoCausas *rec = NULL;
  int CausaEncontrada=0;
  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarSentenciasPorCausaRecursivo(raiz-> izq, tipoCausa);
  carpeta = raiz -> carpetaInvestigativa;
  printf("--------------------------------------------------\n");
  printf("RUC: %s\n", carpeta->ruc);

  /*se recorre la lista de imputados para mostrar cada imputado de la carpeta*/
  recImputado = carpeta -> imputado;
  if (recImputado != NULL) {
    while (recImputado != NULL) {
      CausaEncontrada=0;
      rec=recImputado->imputado->causas;
      while (rec!=NULL) {
        if (rec->causa!=NULL && rec->causa->tipoCausa==tipoCausa) {
          CausaEncontrada=1;
          break;
        }
        rec=rec->sig;
      }
      if (recImputado->imputado!=NULL && CausaEncontrada==1) {

        if (recImputado->imputado->rut!=NULL) {
          printf("RUT del Imputado: %s\n",recImputado->imputado->rut);
        }
        else {
          printf("RUT del Imputado: NO DISPONIBLE\n");
        }

        if (recImputado->imputado->tipoSentencia==1) {
          printf("Tipo de Sentencia: Absolutoria\n");
        }
        else if (recImputado->imputado->tipoSentencia==0) {
          printf("Tipo de Sentencia: Condenatoria\n");
        }
        else {
          printf("No existe un tipo de sentencia\n");
        }
        if (recImputado->imputado->descripcionSentencia!=NULL) {
          printf("Descripcion de la Sentencia: %s\n\n",recImputado->imputado->descripcionSentencia);
        }
        else {
          printf("No se presenta Descripcion de la Sentencia\n\n");
        }
      }
      recImputado=recImputado->sig;
    }
  }
  else{
  printf("Sin imputados asignados\n");
  }
  /* 3. Recorre subárbol derecho*/
  listarSentenciasPorCausaRecursivo(raiz->der,tipoCausa);
}


void listarSentenciasPorCausa(struct Fiscal *fiscal, int tipoCausa) {
  /*listarSentenciasPorCausa es un procedimiento que pide un Tipo de Causa y usa el procedimiento recursivo listarSentenciasPorCausaRecursivo para listar las Sentencias de los Imputados con Causas de ese Tipo*/

  if (fiscal-> carpetas == NULL) {
    printf("NO HAY SENTENCIAS REGISTRADAS");
    return;
  }
  /*el listar Carpetas solo se puede hacer recursivo*/
  listarSentenciasPorCausaRecursivo(fiscal-> carpetas, tipoCausa);

  esperarEnter();
}


void listarResolucionesRecursivo(struct arbolCarpetas *raiz) {
  /*listarResolucionesRecursivo es un procedimiento recursivo que lista todas las Resoluciones*/
  struct CarpetaInvestigativa *carpeta;
  struct NodoResoluciones *resoluciones=NULL;

  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarResolucionesRecursivo(raiz-> izq);
  carpeta = raiz -> carpetaInvestigativa;
  printf("--------------------------------------------------\n");
  printf("RUC: %s\n", carpeta->ruc);

  /*AQUI VA EL RECORRER RESOLUCIONES*/

  resoluciones = carpeta->resoluciones;

  while (resoluciones != NULL) {
    if (resoluciones->resolucion!=NULL) {
      if (resoluciones->resolucion->tipoResolucion==0) {
        printf("Tipo Resolucion: Sentencia\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==1) {
        printf("Tipo Resolucion: Autorización para Diligencias\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==2) {
        printf("Tipo Resolucion: Medida Cautelar\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==3) {
        printf("Tipo Resolucion: Sobreseimiento\n");
      }
      else {
        printf("No hay Tipo de Resolucion Registrado.\n");
      }

      if (resoluciones->resolucion->origenResolucion==0) {
        printf("Origen: La Resolucion fue emitida por el Juez de Garantía\n");
      }
      else if (resoluciones->resolucion->origenResolucion==1) {
        printf("Origen: La Resolucion fue emitida por el tribunal de Juicio Oral\n");
      }
      else {
        printf("Origen: No ha sido especificado.\n");
      }

      if (resoluciones->resolucion->descripcion!=NULL) {
        printf("Descripcion de la Resolución: %s\n",resoluciones->resolucion->descripcion);
      }
      else {
        printf("Descripcion No ha sido especificada.\n");
      }

      if (resoluciones->resolucion->fecha!=NULL) {
        printf("Fecha: %s\n",resoluciones->resolucion->fecha);
      }
      else {
        printf("Fecha: No ha sido especificada.\n");
      }
    }
    resoluciones=resoluciones->sig;
  }

  /* 3. Recorre subarbol derecho*/
  listarResolucionesRecursivo(raiz->der);
}

void ListarResoluciones(struct Fiscal *fiscal) {
  /*listarResoluciones es un procedimiento que usa el procedimiento recursivo listarResolucionesRecursivo para listar todas las Resoluciones*/
  limpiarPantalla();
  printf("=============== LISTADO DE RESOLUCIONES =============\n\n");

  if (fiscal-> carpetas == NULL) {
    printf("NO HAY RESOLUCIONES REGISTRADAS");
    return;
  }
  /*el listar Resoluciones solo se puede hacer recursivo*/
  listarResolucionesRecursivo(fiscal-> carpetas);

  esperarEnter();
}

void listarResolucionesPorCausaRecursivo(struct arbolCarpetas *raiz, int tipoCausa) {
  /*listarResolucionesPorCausaRecursivo es un procedimiento recursivo que lista las Resoluciones que tengan alguna de las Causas, de un tipo especificado, en la denuncia de su carpeta*/
  struct CarpetaInvestigativa *carpeta;
  struct NodoResoluciones *resoluciones=NULL;
  struct NodoCausas *rec=NULL;
  int CausaEncontrada=0;

  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarResolucionesPorCausaRecursivo(raiz-> izq, tipoCausa);
  carpeta = raiz -> carpetaInvestigativa;

  if (carpeta->denuncia!=NULL) {
    rec=carpeta->denuncia->causas;
    while (rec!=NULL) {
      if (rec->causa!=NULL && rec->causa->tipoCausa==tipoCausa) {
        CausaEncontrada=1;
        break;
      }
      rec=rec->sig;
    }
  }

  if (CausaEncontrada==1) {
    printf("--------------------------------------------------\n");
    printf("RUC: %s\n", carpeta->ruc);
  }

  /*AQUÍ VA EL RECORRER RESOLUCIONES*/

  resoluciones = carpeta->resoluciones;

  while (resoluciones != NULL && CausaEncontrada==1) {
    if (resoluciones->resolucion!=NULL) {
      if (resoluciones->resolucion->tipoResolucion==0) {
        printf("Tipo Resolucion: Sentencia\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==1) {
        printf("Tipo Resolucion: Autorización para Diligencias\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==2) {
        printf("Tipo Resolucion: Medida Cautelar\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==3) {
        printf("Tipo Resolucion: Sobreseimiento\n");
      }
      else {
        printf("No hay Tipo de Resolucion Registrado.\n");
      }

      if (resoluciones->resolucion->origenResolucion==0) {
        printf("Origen: La Resolucion fue emitida por el Juez de Garantía\n");
      }
      else if (resoluciones->resolucion->origenResolucion==1) {
        printf("Origen: La Resolucion fue emitida por el tribunal de Juicio Oral\n");
      }
      else {
        printf("Origen: No ha sido especificado.\n");
      }

      if (resoluciones->resolucion->descripcion!=NULL) {
        printf("Descripcion de la Resolución: %s\n",resoluciones->resolucion->descripcion);
      }
      else {
        printf("Descripcion No ha sido especificada.\n");
      }

      if (resoluciones->resolucion->fecha!=NULL) {
        printf("Fecha: %s\n\n",resoluciones->resolucion->fecha);
      }
      else {
        printf("Fecha: No ha sido especificada.\n");
      }
    }
    resoluciones=resoluciones->sig;
  }

  /* 3. Recorre subarbol derecho*/
  listarResolucionesPorCausaRecursivo(raiz->der, tipoCausa);
}

void ListarResolucionesPorCausa(struct Fiscal *fiscal, int tipoCausa) {
  /*listarResolucionesPorCausa es un procedimiento que pide un Tipo de Causa y usa el procedimiento recursivo listarResolucionesPorCausaRecursivo para
   listar las Resoluciones de las Carpetas que contengan una Denuncia con Causas de ese Tipo*/

  if (fiscal-> carpetas == NULL) {
    printf("NO HAY RESOLUCIONES REGISTRADAS");
    return;
  }
  /*el listar Resoluciones solo se puede hacer recursivo*/
  listarResolucionesPorCausaRecursivo(fiscal-> carpetas, tipoCausa);

  esperarEnter();
}

void listarResolucionesPorImputadoRecursivo(struct arbolCarpetas *raiz, char *rut) {
  /*listarResolucionesPorImputadoRecursivo es un procedimiento recursivo que lista las Resoluciones de un Imputado según un RUT dado*/
  struct CarpetaInvestigativa *carpeta;
  struct NodoResoluciones *resoluciones=NULL;
  struct NodoImputados *rec=NULL;
  int ImputadoEncontrado=0;

  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarResolucionesPorImputadoRecursivo(raiz-> izq, rut);
  carpeta = raiz -> carpetaInvestigativa;

  if (carpeta->denuncia!=NULL) {
    rec=carpeta->imputado;
    while (rec!=NULL) {
      if (rec->imputado!=NULL && rec->imputado->rut!=NULL && strcmp(rec->imputado->rut,rut)==0) {
        ImputadoEncontrado=1;
        break;
      }
      rec=rec->sig;
    }
  }

  if (ImputadoEncontrado==1) {
    printf("--------------------------------------------------\n");
    printf("RUC: %s\n", carpeta->ruc);
  }

  /*AQUI VA EL RECORRER RESOLUCIONES*/

  resoluciones = carpeta->resoluciones;

  while (resoluciones != NULL && ImputadoEncontrado==1) {
    if (resoluciones->resolucion!=NULL) {
      if (resoluciones->resolucion->tipoResolucion==0) {
        printf("Tipo Resolucion: Sentencia\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==1) {
        printf("Tipo Resolucion: Autorización para Diligencias\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==2) {
        printf("Tipo Resolucion: Medida Cautelar\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==3) {
        printf("Tipo Resolucion: Sobreseimiento\n");
      }
      else {
        printf("No hay Tipo de Resolucion Registrado.\n");
      }

      if (resoluciones->resolucion->origenResolucion==0) {
        printf("Origen: La Resolucion fue emitida por el Juez de Garantía\n");
      }
      else if (resoluciones->resolucion->origenResolucion==1) {
        printf("Origen: La Resolucion fue emitida por el tribunal de Juicio Oral\n");
      }
      else {
        printf("Origen: No ha sido especificado.");
      }

      if (resoluciones->resolucion->descripcion!=NULL) {
        printf("Descripcion de la Resolución: %s",resoluciones->resolucion->descripcion);
      }
      else {
        printf("Descripcion No ha sido especificada.");
      }

      if (resoluciones->resolucion->fecha!=NULL) {
        printf("Fecha: %s",resoluciones->resolucion->fecha);
      }
      else {
        printf("Fecha: No ha sido especificada.");
      }
    }
    resoluciones=resoluciones->sig;
  }

  /* 3. Recorre subarbol derecho*/
  listarResolucionesPorImputadoRecursivo(raiz->der, rut);
}

void ListarResolucionesPorImputado(struct Fiscal *fiscal, char *rut) {
  /*listarResolucionesPorImputado es un procedimiento que pide un RUT y usa el procedimiento recursivo listarResolucionesPorImputadoRecursivo para listar las Resoluciones del Imputado con ese RUT*/

  if (fiscal-> carpetas == NULL) {
    printf("NO HAY RESOLUCIONES REGISTRADAS");
    return;
  }
  /*el listar Resoluciones solo se puede hacer recursivo*/
  listarResolucionesPorImputadoRecursivo(fiscal-> carpetas, rut);

  esperarEnter();
}

void listarResolucionesPorTipoRecursivo(struct arbolCarpetas *raiz, int tipo) {
  /*listarResolucionesPorTipoRecursivo es un procedimiento recursivo que lista las Resoluciones que tengan algún Tipo específico*/
  struct CarpetaInvestigativa *carpeta;
  struct NodoResoluciones *resoluciones=NULL;

  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarResolucionesRecursivo(raiz-> izq);
  carpeta = raiz -> carpetaInvestigativa;

  /*AQUI VA EL RECORRER RESOLUCIONES*/

  resoluciones = carpeta->resoluciones;

  while (resoluciones != NULL) {
    if (resoluciones->resolucion!=NULL && resoluciones->resolucion->tipoResolucion==tipo) {
      printf("--------------------------------------------------\n");
      printf("RUC: %s\n", carpeta->ruc);
      if (resoluciones->resolucion->tipoResolucion==0) {
        printf("Tipo Resolucion: Sentencia\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==1) {
        printf("Tipo Resolucion: Autorizacion para Diligencias\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==2) {
        printf("Tipo Resolucion: Medida Cautelar\n");
      }
      else if (resoluciones->resolucion->tipoResolucion==3) {
        printf("Tipo Resolucion: Sobreseimiento\n");
      }
      else {
        printf("No hay Tipo de Resolucion Registrado.\n");
      }

      if (resoluciones->resolucion->origenResolucion==0) {
        printf("Origen: La Resolucion fue emitida por el Juez de Garantia\n");
      }
      else if (resoluciones->resolucion->origenResolucion==1) {
        printf("Origen: La Resolucion fue emitida por el tribunal de Juicio Oral\n");
      }
      else {
        printf("Origen: No ha sido especificado.\n");
      }

      if (resoluciones->resolucion->descripcion!=NULL) {
        printf("Descripcion de la Resolucion: %s\n",resoluciones->resolucion->descripcion);
      }
      else {
        printf("Descripcion No ha sido especificada.\n");
      }

      if (resoluciones->resolucion->fecha!=NULL) {
        printf("Fecha: %s\n",resoluciones->resolucion->fecha);
      }
      else {
        printf("Fecha: No ha sido especificada.\n");
      }
    }
    resoluciones=resoluciones->sig;
  }

  /* 3. Recorre subarbol derecho*/
  listarResolucionesRecursivo(raiz->der);
}

void ListarResolucionesPorTipo(struct Fiscal *fiscal, int tipo) {
  /*listarResolucionesPorTipo es un procedimiento que pide un Tipo de Resolución y usa el procedimiento recursivo listarResolucionesPorTipoRecursivo para listar
    las Resoluciones de ese Tipo*/

  if (fiscal-> carpetas == NULL) {
    printf("NO HAY RESOLUCIONES REGISTRADAS");
    return;
  }
  /*el listar Resoluciones solo se puede hacer recursivo*/
  listarResolucionesPorTipoRecursivo(fiscal-> carpetas, tipo);

  esperarEnter();
}



void AgregarResolucion(struct Fiscal *fiscal) {
  /*AgregarResolucion es un procedimiento que le pide al usuario un RUC y le deja añadir una Resolución en la denuncia que tenga ese RUC*/
  char rucBusqueda[RUC];
  int opcion;
  struct CarpetaInvestigativa *carpetaEncontrada=NULL;
  struct NodoResoluciones *nodo=NULL;
  struct NodoResoluciones *rec=NULL;
  struct Resolucion *nuevo=NULL;

  do {
    limpiarPantalla();
    printf("---------------AGREGAR RESOLUCION-------------------\n");
    printf("Ingrese el RUC de la denuncia asociada (formato: 123456789-2025): ");
    fgets(rucBusqueda, RUC, stdin);
    rucBusqueda[strcspn(rucBusqueda, "\n")] = 0;

    if (fiscal -> carpetas == NULL) {
      printf("No hay carpetas a las que pueda agregarle una Resolucion");
      esperarEnter();
      return;
    }

    carpetaEncontrada = BUSCARCARPETA(fiscal->carpetas, rucBusqueda);

    if (carpetaEncontrada == NULL) {
      printf("\nNo se encontro ninguna carpeta con el RUC %s\n", rucBusqueda);
      printf("1. Intentar nuevamente\n");
      printf("2. Volver al menu anterior\n");
      printf("Seleccione una opcion: ");


      scanf("%d", &opcion);
      limpiarBuffer();


      if (opcion == 2) {
        return; /* Salir de la funcion si el usuario elige volver*/
      }
    }
  } while (carpetaEncontrada == NULL);

  nuevo=(struct Resolucion *)malloc(sizeof(struct Resolucion));
  nodo=(struct NodoResoluciones *)malloc(sizeof(struct NodoResoluciones));

  printf("Ingrese el Tipo de Resolucion\n\n");
  printf("Formato:\n");
  printf("0: Sentencia\n");
  printf("1: Autorizacion para Diligencias\n");
  printf("2: Medida Cautelar\n");
  printf("3: Sobreseimiento\n");
  printf("Ingrese un numero: ");
  scanf("%d", &nuevo->tipoResolucion);
  limpiarBuffer();

  printf("\n\nIngrese el Origen de la Resolucion\n\n");
  printf("Formato:\n");
  printf("0: Emitida por el Juez de Garantia\n");
  printf("1: Emitida por el Tribunal de Juicio Oral\n");
  printf("Ingrese un numero: ");
  scanf("%d", &nuevo->origenResolucion);
  limpiarBuffer();

  printf("\n\nIngrese la descripción de la Resolucion:");
  fgets(nuevo->descripcion, TEXTO, stdin);
  nuevo->descripcion[strcspn(nuevo->descripcion, "\n")] = 0;

  printf("\n\nIngrese la fecha de la Resolucion:");
  fgets(nuevo->fecha, FECHA, stdin);
  nuevo->fecha[strcspn(nuevo->fecha, "\n")] = 0;

  nodo->resolucion=nuevo;
  nodo->sig=NULL;

  if (carpetaEncontrada->resoluciones == NULL) {
    carpetaEncontrada->resoluciones = nodo;
  } else {
    rec = carpetaEncontrada->resoluciones;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nodo;
  }

  printf("La Resolucion se asigno correctamente\n\n");
  esperarEnter();

}


/*-----------------------------------------------------------------------*/
void menuDenuncias(struct Fiscal *fiscal) {
  int opcion;
  do {
    limpiarPantalla();
    printf("\n--- Gestión de Denuncias ---\n");
    printf("1. Agregar Denuncia\n");
    printf("2. Buscar Denuncia por RUC\n");
    printf("3. Buscar Denuncia por ESTADO\n");
    printf("4. Modificar Estado Denuncia\n");
    printf("5. Listar Todas las Denuncias\n");
    printf("0. Volver al Menu Principal\n");

    ingresarOpcion(&opcion);


    switch(opcion) {
      case 1: agregarDenuncia(fiscal); break;
      case 2: buscarDenunciaRUC(fiscal); break;
      case 3: buscarDenunciaEstado(fiscal); break;
      case 4: modificarEstadoDenuncia(fiscal); break;
      case 5: listarDenuncias(fiscal); break;
      case 0: break;
      default: printf("Opcion invalida.\n");
    }
  } while(opcion != 0);
}

void menuCarpetas(struct Fiscal *fiscal) {
  int opcion;
  char* rucIngresado;
  int resultado;
  int nuevoEstado;
  int opcionValida;
  struct Declaracion* nuevaDecl;
  char* fechaTemporal;
  struct Diligencia* nuevaDil;
  struct Prueba* nuevaPrueba;

  do {
    limpiarPantalla();
    printf("\n === Gestion de Carpetas investigativas ===\n");
    printf("1. Crear nueva Carpeta Investigativa.\n");
    printf("2. Buscar Carpeta Investigativa por RUC.\n");
    printf("3. Modificar Estado de Carpeta.\n");
    printf("4. Agregar declaracion a Carpeta.\n");
    printf("5. Agregar diligencia a Carpeta.\n");
    printf("6. Agregar resolucion a Carpeta.\n");
    printf("7. Agregar imputado a Carpeta.\n");
    printf("8. Agregar Pruebas a Carpeta.\n");
    printf("9. Listar todas las Carpetas.\n");
    printf("0. Volver al Menu Principal.\n");

    ingresarOpcion(&opcion);

    switch(opcion) {
        case 1: { /* CREAR CARPETA */
            limpiarPantalla();
            printf("--- Crear Nueva Carpeta Investigativa ---\n");
            printf("Ingrese el RUC de la denuncia asociada:\n");
            rucIngresado = ingresarRuc();

            if (rucIngresado != NULL) {
              resultado = CrearCarpeta(fiscal, rucIngresado);
              if (resultado == 0) {
                printf("\n¡Carpeta investigativa creada con éxito!\n");
              } else {
                printf("\nError: No se pudo crear la carpeta.\n");
                printError(resultado);
              }
            } else {
              printf("\nOperación cancelada por el usuario.\n");
            }
            esperarEnter();
            break;
        }
        case 2: { /* BUSCAR CARPETA */
            limpiarPantalla();
            printf("--- Buscar Carpeta Investigativa por RUC ---\n");
            printf("Ingrese el RUC de la CARPETA INVESTIGATIVA:\n");
            rucIngresado = ingresarRuc();
            if (rucIngresado != NULL) {
              resultado = buscarCarpetaRuc(fiscal, rucIngresado);
              if (resultado != 0) {
                  printError(resultado);
                  esperarEnter();
              }
            } else {
              printf("\nOperación cancelada.\n");
              esperarEnter();
            }
            break;
        }
        case 3: { /* MODIFICAR ESTADO */
            limpiarPantalla();
            printf("--- Modificar Estado de Carpeta Investigativa ---\n");
            printf("Ingrese el RUC de la carpeta a modificar:\n");
            rucIngresado = ingresarRuc();

            if (rucIngresado != NULL) {
              nuevoEstado = 0;
              opcionValida = 0;
              do {
                printf("\nSeleccione el nuevo estado para la carpeta:\n");
                printf("0. En investigacion\n1. Juicio Oral\n2. Archivada\n3. Cerrada\n");
                ingresarOpcion(&nuevoEstado);
                if (nuevoEstado >= 0 && nuevoEstado <= 3) {
                  opcionValida = 1;
                } else {
                  printf("Error: Opción no válida.\n");
                }
              } while (!opcionValida);

              resultado = modificarEstadoCarpeta(fiscal, rucIngresado, nuevoEstado);

              if (resultado == 0) {
                printf("\n¡Estado de la carpeta actualizado con éxito!\n");
              } else {
                printf("\nError: No se pudo actualizar el estado.\n");
                printError(resultado);
              }
            } else {
              printf("\nOperación cancelada.\n");
            }
            esperarEnter();
            break;
        }
        case 4: { /* AGREGAR DECLARACIÓN */
            limpiarPantalla();
            printf("--- Agregar Declaración a Carpeta ---\n");
            printf("Ingrese el RUC de la carpeta:\n");
            rucIngresado = ingresarRuc();
            if (rucIngresado == NULL) { break; }

            if (BUSCARCARPETA(fiscal->carpetas, rucIngresado) == NULL) {
                printError(CARPETA);
                esperarEnter();
                break;
            }

            printf("\n--- Ingresando datos de la nueva declaración ---\n");
            nuevaDecl = (struct Declaracion*)malloc(sizeof(struct Declaracion));
            if (nuevaDecl == NULL) { break; }

            limpiarBuffer();
            printf("Ingrese RUT del declarante: \n");
            fgets(nuevaDecl->rut, RUT, stdin);
            nuevaDecl->rut[strcspn(nuevaDecl->rut, "\n")] = 0;

            printf("Ingrese origen (0: Víctima, 1: Testigo, 2: Imputado): \n");
            ingresarOpcion(&nuevaDecl->origenDeclaracion);

            printf("Ingrese el texto de la declaración (MAX 1000 caracteres): \n");
            fgets(nuevaDecl->declaracion, TEXTO, stdin);
            nuevaDecl->declaracion[strcspn(nuevaDecl->declaracion, "\n")] = 0;

            printf("Ingrese la fecha (dd/mm/aaaa):\n");
            fechaTemporal = ingresarFecha();
            if (fechaTemporal != NULL) {
                strcpy(nuevaDecl->fecha, fechaTemporal);
            } else {
                break;
            }
            resultado = agregarDeclaracion(fiscal, rucIngresado, nuevaDecl);
            if (resultado == 0) {
                printf("\n¡Declaración agregada con éxito!\n");
            } else {
                printf("\nError: No se pudo agregar la declaración.\n");
                printError(resultado);
            }
            esperarEnter();
            break;
        }
        case 5: { /* AGREGAR DILIGENCIA */
            limpiarPantalla();
            printf("--- Agregar Diligencia a Carpeta ---\n");

            printf("Ingrese el RUC de la carpeta:\n");
            rucIngresado = ingresarRuc();
            if (rucIngresado == NULL) { break; }

            if (BUSCARCARPETA(fiscal->carpetas, rucIngresado) == NULL) {
                printError(CARPETA);
                esperarEnter();
                break;
            }

            printf("\n--- Rellenando datos de la nueva diligencia ---\n");
            nuevaDil = (struct Diligencia*)malloc(sizeof(struct Diligencia));
            if(nuevaDil == NULL) { break; }

            printf("Ingrese origen (0: Fiscal, 1: Victima, 2: Imputado, 3: Juez): \n");
            ingresarOpcion(&nuevaDil->OrigenDiligencia);
            limpiarBuffer();

            printf("Ingrese tipo de diligencia (ej. Allanamiento): \n");
            fgets(nuevaDil->tipoDiligencia, TEXTO, stdin);
            nuevaDil->tipoDiligencia[strcspn(nuevaDil->tipoDiligencia, "\n")] = 0;

            printf("Ingrese descripcion: \n");
            fgets(nuevaDil->descripcionDiligencia, TEXTO, stdin);
            nuevaDil->descripcionDiligencia[strcspn(nuevaDil->descripcionDiligencia, "\n")] = 0;

            printf("Ingrese fecha (dd/mm/aaaa): \n");
            fechaTemporal = ingresarFecha();
            if (fechaTemporal == NULL) { break; }
            strcpy(nuevaDil->fechaDiligencia, fechaTemporal);

            printf("Ingrese aprobacion (1: Aprobada, 0: Rechazada, -1: En proceso): \n");
            ingresarOpcion(&nuevaDil->aprobacion);

            printf("Ingrese urgencia (1: Baja, 2: Media, 3: Alta): \n");
            ingresarOpcion(&nuevaDil->urgencia);

            printf("Ingrese impacto (1: Bajo, 2: Medio, 3: Alto): \n");
            ingresarOpcion(&nuevaDil->impacto);

            resultado = agregarDiligencia(fiscal, rucIngresado, nuevaDil);

            if (resultado == 0) {
                printf("\n¡Diligencia agregada con éxito!\n");
            } else {
                printf("\nError: No se pudo agregar la diligencia.\n");
            }

            esperarEnter();
            break;
        }
        case 6: { /* AGREGAR RESOLUCION (ORIGINAL) */
            agregarResolucion(fiscal);
            break;
        }
        case 7: { /* AGREGAR IMPUTADO (ORIGINAL) */
            agregarImputado(fiscal);
            break;
        }
        case 8: { /* AGREGAR PRUEBA */
            limpiarPantalla();
            printf("--- Agregar Prueba a Carpeta ---\n");
            printf("Ingrese el RUC de la carpeta:\n");
            rucIngresado = ingresarRuc();
            if (rucIngresado == NULL) { break; }

            if (BUSCARCARPETA(fiscal->carpetas, rucIngresado) == NULL) {
                printError(CARPETA);
                esperarEnter();
                break;
            }

            printf("\n--- Rellenando datos de la nueva prueba ---\n");
            nuevaPrueba = (struct Prueba*)malloc(sizeof(struct Prueba));
            if(nuevaPrueba == NULL) { break; }

            printf("Ingrese tipo de prueba (0: Informe, 1: Grabación, 2: Documento, 3: Física):\n");
            ingresarOpcion(&nuevaPrueba->tipoDePrueba);
            limpiarBuffer();

            printf("Ingrese descripción de la prueba:\n");
            fgets(nuevaPrueba->descripcionPrueba, TEXTO, stdin);
            nuevaPrueba->descripcionPrueba[strcspn(nuevaPrueba->descripcionPrueba, "\n")] = 0;

            printf("Ingrese fecha de la prueba (dd/mm/aaaa):\n");
            fechaTemporal = ingresarFecha();
            if (fechaTemporal == NULL) { break; }
            strcpy(nuevaPrueba->fecha, fechaTemporal);

            resultado = agregarPrueba(fiscal, rucIngresado, nuevaPrueba);

            if (resultado == 0) {
                printf("\n¡Prueba agregada con éxito!\n");
            } else {
                printf("\nError: No se pudo agregar la prueba.\n");
            }

            esperarEnter();
            break;
        }
        case 9:
            listarCarpetas(fiscal);
            break;
        case 0:
            break;
        default:
            printf("Opcion Invalida. Intente Denuevo.\n");
            break;
    }
  }while (opcion != 0);
}

void menuImputados(struct Fiscal *fiscal){
  int opcion;
  char* rucIngresado;
  int resultado;
  struct Declaracion* nuevaDecl;
  char* fechaTemporal;

  do {
    limpiarPantalla();
    printf("\n--- Gestion de Imputados---\n");
    printf("1. Agregar Imputado a una Carpeta Investigativa\n");
    printf("2. Modificar Imputado\n");
    printf("3. Agregar Declaraciones\n");
    printf("4. Buscar Imputado por RUT o Causa\n");
    printf("5. Listar Todos los imputados del Fiscal\n");
    printf("0. Volver al Menu Principal\n");

    ingresarOpcion(&opcion);

    switch(opcion) {
      case 1: agregarImputado(fiscal); break;
      case 2: modificarImputado(fiscal); break;
      case 3: { /* AGREGAR DECLARACIÓN */
        limpiarPantalla();
        printf("--- Agregar Declaración a Carpeta ---\n");
        printf("Ingrese el RUC de la carpeta:\n");
        rucIngresado = ingresarRuc();
        if (rucIngresado == NULL) { break; }

        if (BUSCARCARPETA(fiscal->carpetas, rucIngresado) == NULL) {
          printError(CARPETA);
          esperarEnter();
          break;
        }

        printf("\n--- Ingresando datos de la nueva declaración ---\n");
        nuevaDecl = (struct Declaracion *) malloc(sizeof(struct Declaracion));
        if (nuevaDecl == NULL) { break; }

        limpiarBuffer();
        printf("Ingrese RUT del declarante: \n");
        fgets(nuevaDecl->rut, RUT, stdin);
        nuevaDecl->rut[strcspn(nuevaDecl->rut, "\n")] = 0;

        printf("Ingrese origen (0: Víctima, 1: Testigo, 2: Imputado): \n");
        ingresarOpcion(&nuevaDecl->origenDeclaracion);

        printf("Ingrese el texto de la declaración (MAX 1000 caracteres): \n");
        fgets(nuevaDecl->declaracion, TEXTO, stdin);
        nuevaDecl->declaracion[strcspn(nuevaDecl->declaracion, "\n")] = 0;

        printf("Ingrese la fecha (dd/mm/aaaa):\n");
        fechaTemporal = ingresarFecha();
        if (fechaTemporal != NULL) {
          strcpy(nuevaDecl->fecha, fechaTemporal);
        } else {
          break;
        }
        resultado = agregarDeclaracion(fiscal, rucIngresado, nuevaDecl);
        if (resultado == 0) {
          printf("\n¡Declaración agregada con éxito!\n");
        } else {
          printf("\nError: No se pudo agregar la declaración.\n");
          printError(resultado);
        }
        esperarEnter();
        break;
    };
  case 4: buscarImputadoPorRut(fiscal);
    break;
  case 5: mostrarTodosImputados(fiscal);
    break;
  case 0: break;
  default: printf("Opcion invalida.\n");
  }
}

while(opcion!=0);
}

void menuDiligencias(struct Fiscal *fiscal) {
  int opcion;
  char* rucIngresado;
  int resultado;
  char* fechaTemporal;
  struct Diligencia* nuevaDil;
  do {
    limpiarPantalla();
    printf("--- Gestion de Diligencias ---\n");
    printf("1. Agregar diligencias\n");
    printf("2. Mostrar diligencias\n");
    printf("3. Asignar prioridad a Diligencia y mostrar la lista\n");
    printf("4. Ver diligencias pendientes por carpeta\n");
    printf("0. Volver al Menu Principal\n");

    ingresarOpcion(&opcion);

    switch(opcion) {
      case 1: { /* AGREGAR DILIGENCIA */
            limpiarPantalla();
            printf("--- Agregar Diligencia a Carpeta ---\n");

            printf("Ingrese el RUC de la carpeta:\n");
            rucIngresado = ingresarRuc();
            if (rucIngresado == NULL) { break; }

            if (BUSCARCARPETA(fiscal->carpetas, rucIngresado) == NULL) {
                printError(CARPETA);
                esperarEnter();
                break;
            }

            printf("\n--- Rellenando datos de la nueva diligencia ---\n");
            nuevaDil = (struct Diligencia*)malloc(sizeof(struct Diligencia));
            if(nuevaDil == NULL) { break; }

            printf("Ingrese origen (0: Fiscal, 1: Victima, 2: Imputado, 3: Juez): \n");
            ingresarOpcion(&nuevaDil->OrigenDiligencia);
            limpiarBuffer();

            printf("Ingrese tipo de diligencia (ej. Allanamiento): \n");
            fgets(nuevaDil->tipoDiligencia, TEXTO, stdin);
            nuevaDil->tipoDiligencia[strcspn(nuevaDil->tipoDiligencia, "\n")] = 0;

            printf("Ingrese descripcion: \n");
            fgets(nuevaDil->descripcionDiligencia, TEXTO, stdin);
            nuevaDil->descripcionDiligencia[strcspn(nuevaDil->descripcionDiligencia, "\n")] = 0;

            printf("Ingrese fecha (dd/mm/aaaa): \n");
            fechaTemporal = ingresarFecha();
            if (fechaTemporal == NULL) { break; }
            strcpy(nuevaDil->fechaDiligencia, fechaTemporal);

            printf("Ingrese aprobacion (1: Aprobada, 0: Rechazada, -1: En proceso): \n");
            ingresarOpcion(&nuevaDil->aprobacion);

            printf("Ingrese urgencia (1: Baja, 2: Media, 3: Alta): \n");
            ingresarOpcion(&nuevaDil->urgencia);

            printf("Ingrese impacto (1: Bajo, 2: Medio, 3: Alto): \n");
            ingresarOpcion(&nuevaDil->impacto);

            resultado = agregarDiligencia(fiscal, rucIngresado, nuevaDil);

            if (resultado == 0) {
                printf("\n¡Diligencia agregada con éxito!\n");
            } else {
                printf("\nError: No se pudo agregar la diligencia.\n");
            }

            esperarEnter();
            break;
        }
      case 2 : mostrarDiligencias(fiscal); break;
      case 3: mostrarDiligenciasOrdenadas(fiscal); break;
      case 4: listarDiligenciasPendientes(fiscal); break;
      case 0: break;
      default: printf("Opcion invalida.\n");
    }
  }while(opcion != 0);
}

void menuCausas(struct Fiscal *fiscal) {
  int opcion;
  int eleccion;
  char rut[RUT];
  char ruc [RUC];
  char *rucTemp;
  struct Denuncia *denunciaEncontrada;

  do {
    limpiarPantalla();
    printf("\n--- Gestion de Causas ---\n");
    printf("1. Agregar Causa\n");
    printf("2. Buscar Causa por Imputado\n");
    printf("3. Buscar Causa por Denuncia\n");
    printf("4. Modificar Estado de la Causa\n");
    printf("5. Listar Todas las Causas\n");
    printf("0. Volver al Menu Principal\n");

    ingresarOpcion(&opcion);

    switch(opcion) {
      case 1: agregarCausas(fiscal); break;
      case 2: {
        limpiarPantalla();

        printf("=== BUSCAR CAUSA POR IMPUTADO ===\n");
        printf("Ingrese el RUT del Imputado: ");

        fgets(rut, RUT, stdin);
        rut[strcspn(rut, "\n")]= 0;
        printf("\nese %s\n",rut);

        BuscarCausasPorImputado(fiscal,rut);

        break;
      }
      case 3: {
        /*limpiarPantalla es un procedimiento que salta 20 líneas, para limpiar la pantalla.*/
        limpiarPantalla();
        printf("=== BUSCAR CAUSA POR DENUNCIA ===\n");
        printf("Ingrese el RUC de la Denuncia: ");

        /*Se pide el RUC*/
        rucTemp=ingresarRuc();

        printf("\n\n--- Causas de Denuncias ---\n\n\n");
        BuscarCausasDenuncia(fiscal,rucTemp);
        break;
      }
      case 4: {
        limpiarPantalla();

        if (fiscal->denuncias== NULL) {
          printf("No hay denuncias en el Sistema");
          return;
        }

        printf("Modificar Causas: \n\n");
        do {
          printf("Ingrese el RUC de la Denuncia: ");
          rucTemp = ingresarRuc();
          if (rucTemp == NULL) {
            return; /*Si retorna NUll el usuario quiere volver al menu Principal*/
          }
          strcpy(ruc, rucTemp);
          denunciaEncontrada = BUSCARDENUNCIA(fiscal, ruc);


          if (denunciaEncontrada == NULL) {
            printf("\nNo se encontró ninguna denuncia con el RUC %s\n", ruc);
            printf("1. Intentar nuevamente\n");
            printf("2. Volver al menú anterior\n");
            printf("Seleccione una opción: ");

            scanf("%d", &eleccion);

            if (eleccion == 2) {
              return; /* Salir de la función si el usuario elige volver*/
            }
          }
        }while (denunciaEncontrada == NULL);

        ModificarCausa(denunciaEncontrada);
        break;
      }
      case 5: ListarCausas(fiscal); break;
      case 0: break;
      default: printf("Opcion invalida.\n");
    }
  } while(opcion != 0);
}

void menuSentenciasResoluciones(struct Fiscal *fiscal) {
  int opcion;
  int tipo;
  char ruc[RUC];
  char rut[RUT];
  do {
    limpiarPantalla();
    printf("\n--- Gestion de Sentencias y Resoluciones ---\n");
    printf("1. Agregar Resolucion\n");
    printf("2. Buscar Resolucion por Causa\n");
    printf("3. Buscar Resolucion por Imputado\n");
    printf("4. Buscar Resolucion por Tipo de Resolucion\n");
    printf("5. Buscar Sentencia por Causa\n");
    printf("6. Buscar Sentencia por Imputado\n");
    printf("7. Listar Todas las Sentencias\n");
    printf("8. Listar Todas las Resoluciones\n");
    printf("0. Volver al Menu Principal\n");

    ingresarOpcion(&opcion);

    switch(opcion) {
      case 1: agregarResolucion(fiscal); break;
      case 2: {
        limpiarPantalla();

        printf("Ingrese el Tipo de Causa por el cual desea Filtrar las Resoluciones:\n\n");
        printf("Formato:\n");
        printf("0 Si es un Crimen (Infraccion grave como Homicidio)\n");
        printf("1 Si es un Delito Simple (Ejemplo: Hurto o Estafa)\n");
        printf("2 Si es una Falta (Ejemplo: Infracciones de Transito)\n");
        printf("Ingrese un número:");

        scanf("%d", &tipo);
        limpiarBuffer();

        printf("\n\n=============== LISTADO DE RESOLUCIONES =============\n\n");

        ListarResolucionesPorCausa(fiscal, tipo);

        break;
      }
      case 3: {
        limpiarPantalla();

        printf("Ingrese el RUT del Imputado por el cual desea Filtrar las Resoluciones: ");

        fgets(rut, RUT, stdin);
        rut[strcspn(rut, "\n")]= 0;

        printf("\n\n=============== LISTADO DE RESOLUCIONES =============\n\n");

        ListarResolucionesPorImputado(fiscal,rut);

        break;
      }
      case 4: {
        limpiarPantalla();

        printf("Ingrese el Tipo por el cual desea Filtrar las Resoluciones:\n\n");
        printf("Formato:\n");
        printf("0 Si es Sentencia o Fallo\n");
        printf("1 Si es Autorizacion para diligencias\n");
        printf("2 Si es una medida Cautelar\n");
        printf("3 Si es un sobreseimiento\n");
        printf("Ingrese un numero:");

        scanf("%d", &tipo);
        limpiarBuffer();

        printf("\n\n=============== LISTADO DE RESOLUCIONES =============\n\n");

        ListarResolucionesPorTipo(fiscal,tipo);

        break;
      }
      case 5: {
        limpiarPantalla();

        printf("Ingrese el Tipo de Causa por el cual desea Filtrar las Resoluciones:\n\n");
        printf("Formato:\n");
        printf("0 Si es un Crimen (Infraccion grave como Homicidio)\n");
        printf("1 Si es un Delito Simple (Ejemplo: Hurto o Estafa)\n");
        printf("2 Si es una Falta (Ejemplo: Infracciones de Transito)\n");
        printf("Ingrese un numero:");

        scanf("%d", &tipo);
        limpiarBuffer();

        printf("=============== LISTADO DE SENTENCIAS =============");

        listarSentenciasPorCausa(fiscal,tipo);

        break;
      }
      case 6: {
        limpiarPantalla();

        printf("Ingrese el RUT del Imputado por el cual desea Filtrar las Sentencias: ");
        fgets(rut, RUT, stdin);
        rut[strcspn(rut, "\n")]= 0;

        printf("\n\n=============== LISTADO DE SENTENCIAS =============\n\n");

        listarSentenciasPorImputado(fiscal,rut);

        break;
      }
      case 7: listarSentencias(fiscal); break;
      case 8: ListarResoluciones(fiscal); break;
      case 0: break;;
      default: printf("Opcion invalida.\n");
    }
  } while(opcion != 0);
}
void menuReportes(struct Fiscal *fiscal) {
  int opcion;

  do {
    limpiarPantalla();
    printf("========= MENU DE REPORTES =========\n");
    printf("1. Listar todas las denuncias\n");
    printf("2. Buscar denuncia por RUC\n");
    printf("3. Buscar denuncias por estado\n");
    printf("4. Listar todas las carpetas investigativas\n");
    printf("5. Buscar carpeta por RUC\n");
    printf("6. Mostrar todos los imputados\n");
    printf("7. Buscar imputado por RUT\n");
    printf("8. Listar causas de denuncias\n");
    printf("9. Mostrar diligencias de carpeta\n");
    printf("10. Mostrar diligencias ordenadas por urgencia\n");
    printf("11. Listar diligencias pendientes\n");
    printf("0. Volver al menu principal\n");

    ingresarOpcion(&opcion);

    switch(opcion) {
      case 1: listarDenuncias(fiscal); break;
      case 2: buscarDenunciaRUC(fiscal); break;
      case 3: buscarDenunciaEstado(fiscal); break;
      case 4: listarCarpetas(fiscal); break;
      case 6: mostrarTodosImputados(fiscal); break;
      case 7: buscarImputadoPorRut(fiscal); break;
      case 8: ListarCausas(fiscal); break;
      case 9: mostrarDiligencias(fiscal); break;
      case 10: mostrarDiligenciasOrdenadas(fiscal); break;
      case 11: listarDiligenciasPendientes(fiscal); break;
      case 0: printf("Volviendo al menu principal...\n"); break;
      default: printf("Opcion no valida.\n"); esperarEnter(); break;
    }

  } while(opcion != 0);
}


void mostrarMenuPrincipal(struct Fiscal *fiscal) {
  int opcion;
  do {

    limpiarPantalla();
    printf("\n=== SISTEMA DE GESTION PENAL - MINISTERIO PUBLICO ===\n");
    printf("1. Registrar / Consultar Denuncias\n");
    printf("2. Gestionar Carpetas Investigativas\n");
    printf("3. Administrar Imputados\n");
    printf("4. Seguimiento de Diligencias\n");
    printf("5. Controlar Estado de Causas\n");
    printf("6. Gestionar Sentencias y Resoluciones\n");
    printf("7. Generar Reportes\n");
    printf("0. Salir\n");

    ingresarOpcion(&opcion);

    switch(opcion) {
      case 1: menuDenuncias(fiscal); break;
      case 2: menuCarpetas(fiscal); break;
      case 3: menuImputados(fiscal); break;
      case 4: menuDiligencias(fiscal); break;
      case 5: menuCausas(fiscal); break;
      case 6: menuSentenciasResoluciones(fiscal); break;
      case 7: menuReportes(fiscal); break;
      case 0: return;
      default: printf("Opcion invalida. Intente nuevamente.\n");
    }
  } while(opcion != 0);
}

/*PARA DATOS DE PRUEBA*/

void inicializarDatosPrueba(struct MinisterioPublico **mp) {
    struct Fiscal* fiscal;
    struct Denuncia* denuncia;
    struct NodoDenuncias* nodoDenuncia;
    struct CarpetaInvestigativa* carpeta;
    struct Imputado* imputado;
    struct NodoImputados* nodoImputado;
    struct Declaracion* decl;
    struct NodoDeclaraciones* nodoDecl;
    struct Diligencia* dil;
    struct NodoDiligencias* nodoDil;
    struct Resolucion* res;
    struct NodoResoluciones* nodoRes;
    struct arbolCarpetas* arbol;
    int i;
    /* Inicializar Ministerio Público */
    (*mp)->tamFiscal = 103;
    (*mp)->fiscales = (struct Fiscal**)malloc(sizeof(struct Fiscal*) * 103);
    for (i = 0; i < 103; i++) {
      (*mp)->fiscales[i] = NULL;
    }
    /* Crear fiscal */
    fiscal = (struct Fiscal*)malloc(sizeof(struct Fiscal));
    strcpy(fiscal->rut, "12345678-9");
    strcpy(fiscal->contrasenia, "pass123");
    fiscal->denuncias = NULL;
    fiscal->carpetas = NULL;

    /* Crear denuncia */
    denuncia = (struct Denuncia*)malloc(sizeof(struct Denuncia));
    strcpy(denuncia->ruc, "123456789-2024");
    strcpy(denuncia->rutDenunciante, "98765432-1");
    denuncia->origenDenunciante = 0;
    strcpy(denuncia->fecha, "01/01/2024");
    denuncia->estadoDenuncia = 0;
    denuncia->causas = NULL;
    denuncia->rutVictimas = NULL;
    denuncia -> rutVictimas = (struct RutVictima **)malloc(40 * sizeof(struct RutVictima*));
    for (i = 0; i < 40; i++) {
      denuncia -> rutVictimas[i] = NULL;
    }
    denuncia -> pLibreRutVictimas = -1;

    /* Nodo de denuncia */
    nodoDenuncia = (struct NodoDenuncias*)malloc(sizeof(struct NodoDenuncias));
    nodoDenuncia->denuncia = denuncia;
    nodoDenuncia->sig = nodoDenuncia;
    nodoDenuncia->ant = nodoDenuncia;
    fiscal->denuncias = nodoDenuncia;

    /* Crear carpeta */
    carpeta = (struct CarpetaInvestigativa*)malloc(sizeof(struct CarpetaInvestigativa));
    strcpy(carpeta->ruc, "123456789-2024");
    carpeta->estadoCarpeta = 0;
    carpeta->tipoDeJuicio = 0;
    carpeta->denuncia = denuncia;
    carpeta->declaraciones = NULL;
    carpeta->pruebas = NULL;
    carpeta->diligencias = NULL;
    carpeta->resoluciones = NULL;
    carpeta->imputado = NULL;

    /* Crear imputado y nodo */
    imputado = (struct Imputado*)malloc(sizeof(struct Imputado));
    strcpy(imputado->rut, "19283746-5");
    imputado->tipoSentencia = -1;  /* aun no tiene sentencia*/
    strcpy(imputado->medidasCautelares, "Arraigo nacional");
    strcpy(imputado->descripcionSentencia, "");
    imputado->causas = NULL;

    nodoImputado = (struct NodoImputados*)malloc(sizeof(struct NodoImputados));
    nodoImputado->imputado = imputado;
    nodoImputado->sig = NULL;
    carpeta->imputado = nodoImputado;

    /* Declaración */
    decl = (struct Declaracion*)malloc(sizeof(struct Declaracion));
    strcpy(decl->rut, "11223344-5");
    decl->origenDeclaracion = 1;
    strcpy(decl->declaracion, "Vi al sospechoso en el lugar de los hechos");
    strcpy(decl->fecha, "02/01/2024");

    nodoDecl = (struct NodoDeclaraciones*)malloc(sizeof(struct NodoDeclaraciones));
    nodoDecl->declaracion = decl;
    nodoDecl->sig = NULL;
    carpeta->declaraciones = nodoDecl;

    /* Diligencia */
    dil = (struct Diligencia*)malloc(sizeof(struct Diligencia));
    dil->OrigenDiligencia = 0;
    strcpy(dil->tipoDiligencia, "Allanamiento");
    strcpy(dil->descripcionDiligencia, "Allanamiento domicilio sospechoso");
    strcpy(dil->fechaDiligencia, "03/01/2024");
    dil->aprobacion = 1;
    dil->urgencia = 3;
    dil->impacto = 3;

    nodoDil = (struct NodoDiligencias*)malloc(sizeof(struct NodoDiligencias));
    nodoDil->diligencia = dil;
    nodoDil->sig = NULL;
    carpeta->diligencias = nodoDil;

    /* Resolución */
    res = (struct Resolucion*)malloc(sizeof(struct Resolucion));
    strcpy(res->rutJuez, "44556677-0");
    res->tipoResolucion = 1;
    res->origenResolucion = 0;
    strcpy(res->descripcion, "Autorización para allanamiento");
    strcpy(res->fecha, "02/01/2024");

    nodoRes = (struct NodoResoluciones*)malloc(sizeof(struct NodoResoluciones));
    nodoRes->resolucion = res;
    nodoRes->sig = NULL;
    carpeta->resoluciones = nodoRes;

    /* Insertar carpeta en árbol */
    arbol = (struct arbolCarpetas*)malloc(sizeof(struct arbolCarpetas));
    arbol->carpetaInvestigativa = carpeta;
    arbol->izq = NULL;
    arbol->der = NULL;
    fiscal->carpetas = arbol;

    (*mp)->fiscales[0] = fiscal;
}

int main(){
  struct MinisterioPublico *ministerioPublico = NULL;
  int i;
  char rut[RUT];
  char contrasenia[TEXTO];
  int flag;
  int opcion;

  ministerioPublico = (struct MinisterioPublico*)malloc(sizeof(struct MinisterioPublico));

  inicializarDatosPrueba(&ministerioPublico);
  do {
    flag = 0;
    printf("Ingrese su RUT:\n");
    fgets(rut, RUT, stdin);
    rut[strcspn(rut, "\n")] = 0;
    limpiarBuffer();
    printf("Ingrese su contraseña:\n");
    fgets(contrasenia, TEXTO, stdin);
    contrasenia[strcspn(contrasenia, "\n")] = 0;

    for (i = 0; i < ministerioPublico -> tamFiscal; i++) {
      if (ministerioPublico->fiscales[i] != NULL) {
        if ((strcmp(ministerioPublico->fiscales[i]-> rut, rut) == 0) && (strcmp(ministerioPublico->fiscales[i]-> contrasenia, contrasenia) == 0)) {
          printf("Se a iniciado sesion correctamente\n");
          esperarEnter();
          mostrarMenuPrincipal(ministerioPublico->fiscales[i]);
          flag = 1;
          return 0;
        }
      }
    }
    if (flag == 0) {
      printf("Contraseña o RUT equivocados\n");
    }

    printf("Que es lo que desea hacer: \n");
    printf("0. terminar la ejecucion del programa\n");
    printf("NUMERO CUALQUIERA. volver a intentar\n");
    ingresarOpcion(&opcion);

  }while (opcion != 0);


  return 0;
}
